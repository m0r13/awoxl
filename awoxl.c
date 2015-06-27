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

    srand(time(NULL));
    awoxl_on(sock);
    awoxl_rgb(sock, rand() % 255, rand() % 255, rand() % 255);
    
    awoxl_disconnect(sock);
}

