#include "awoxl_client.h"

#include <bluetooth/l2cap.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h> /* close */

// from bluez
static int l2cap_bind(int sock, const bdaddr_t *src, uint8_t src_type,
                uint16_t psm, uint16_t cid/*, GError **err*/)
{
    struct sockaddr_l2 addr;

    memset(&addr, 0, sizeof(addr));
    addr.l2_family = AF_BLUETOOTH;
    bacpy(&addr.l2_bdaddr, src);

    if (cid)
        addr.l2_cid = htobs(cid);
    else
        addr.l2_psm = htobs(psm);

    addr.l2_bdaddr_type = src_type;

    if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        int error = -errno;
        // ERROR_FAILED(err, "l2cap_bind", errno);
        return error;
    }

    return 0;
}

// from bluez
static int l2cap_connect(int sock, const bdaddr_t *dst, uint8_t dst_type,
                        uint16_t psm, uint16_t cid)
{
    int err;
    struct sockaddr_l2 addr;

    memset(&addr, 0, sizeof(addr));
    addr.l2_family = AF_BLUETOOTH;
    bacpy(&addr.l2_bdaddr, dst);
    if (cid)
        addr.l2_cid = htobs(cid);
    else
        addr.l2_psm = htobs(psm);

    addr.l2_bdaddr_type = dst_type;

    err = connect(sock, (struct sockaddr *) &addr, sizeof(addr));
    if (err < 0 && !(errno == EAGAIN || errno == EINPROGRESS))
        return -errno;

    return 0;
}

int awoxl_connect(bdaddr_t dst) {
    int cid = 4, psm = 0;
    bdaddr_t src;
    for (int i = 0; i < 6; i++)
        src.b[i] = 0;

    int sock = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);
    int err = l2cap_bind(sock, &src, BDADDR_LE_PUBLIC, psm, cid);
    if (err)
        return -1;
    err = l2cap_connect(sock, &dst, BDADDR_LE_PUBLIC, psm, cid);
    if (err)
        return -1;
    return sock;
}

int awoxl_send_command(int sock, unsigned char* command, int len) {
    unsigned char* buffer = (unsigned char*) malloc(len + 3);
    buffer[0] = 0x12;
    buffer[1] = 0x1D;
    buffer[2] = 0x00;
    memcpy(buffer + 3, command, len);
    int sent = send(sock, buffer, len + 3, 0);
    free(buffer);
    return sent == len + 3 ? 0 : -1;
}

int awoxl_disconnect(int sock) {
    return close(sock);
}

