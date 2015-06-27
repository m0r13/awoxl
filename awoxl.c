#include "awoxl_client.h"
#include "awoxl_protocol.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
    bdaddr_t dst;
    unsigned char dstm[6] = {0xd0, 0x39, 0x72, 0xb8, 0x35, 0xfd};
    for (int i = 0; i < 6; i++)
        dst.b[i] = dstm[5-i];

    int sock = awoxl_connect(dst);
    if (sock < 0) {
        printf("Error: %d\n", errno);
        return 1;
    }
    

    int len;
    unsigned char* buffer;
    
    len = awoxl_protocol_on(&buffer);
    awoxl_send_command(sock, buffer, len);
    free(buffer);

    srand(time(NULL));
    len = awoxl_protocol_rgb(&buffer, rand() % 255, rand() % 255, rand() % 255);
    awoxl_send_command(sock, buffer, len);
    free(buffer);
    
    awoxl_disconnect(sock);
}

