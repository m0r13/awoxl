#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/l2cap.h>

#include <stdio.h>

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
	printf("bind addr.dst = %02x:%02x:%02x:%02x:%02x:%02x\n", src->b[5], src->b[4], src->b[3], src->b[2], src->b[1], src->b[0]);
	printf("bind addr.l2_cid = %d\n", addr.l2_cid);
	printf("bind addr.l2_psm = %d\n", addr.l2_psm);

	addr.l2_bdaddr_type = src_type;

	if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
		int error = -errno;
		// ERROR_FAILED(err, "l2cap_bind", errno);
		return error;
	}

	return 0;
}

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

	printf("connect addr.dst = %02x:%02x:%02x:%02x:%02x:%02x\n", dst->b[5], dst->b[4], dst->b[3], dst->b[2], dst->b[1], dst->b[0]);
	printf("connect addr.l2_cid = %d\n", addr.l2_cid);
	printf("connect addr.l2_psm = %d\n", addr.l2_psm);
	printf("connect addr.l2_bdaddr_type = %d\n", addr.l2_bdaddr_type);

	err = connect(sock, (struct sockaddr *) &addr, sizeof(addr));
	if (err < 0 && !(errno == EAGAIN || errno == EINPROGRESS))
		return -errno;

	return 0;
}

int main(int argc, char** argv) {
    int cid = 4;
    int psm = 0;

	bdaddr_t src, dst;
    unsigned char dstm[6] = {0xd0, 0x39, 0x72, 0xb8, 0x35, 0xfd};
	unsigned char srcm[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    for (int i = 0; i < 6; i++) {
        dst.b[i] = dstm[5-i];
		src.b[i] = srcm[5-i];
	}

    int sock = socket(AF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);
	int err = l2cap_bind(sock, &src, BDADDR_LE_PUBLIC, psm, cid);
	if (err) {
		printf("error bind: %d\n", errno);
		return 1;
	}
	err = l2cap_connect(sock, &dst, BDADDR_LE_PUBLIC, psm, cid);
    if (err) {
        printf("error connect: %d\n", errno);
		return 1;
    }

	unsigned char buf_on[15] = {0x12, 0x1d, 0x00, 0xaa, 0xa, 0xfc, 0x3a, 0x86, 0x1, 0xa, 0x1, 0x1, 0x0, 0x28, 0xd};
	unsigned char buf_off[15] = {0x12, 0x1d, 0x00, 0xaa, 0xa, 0xfc, 0x3a, 0x86, 0x1, 0xa, 0x1, 0x0, 0x1, 0x28, 0xd};
	unsigned char* buf = argv[1][1] == 'n' ? buf_on : buf_off;
	int size = send(sock, buf, 15, 0);
	printf("sent: %d\n", size);
	
	return 0;
}

