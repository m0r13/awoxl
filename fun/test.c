#include "../awoxl_client.h"
#include "../awoxl_protocol.h"
#include "../awoxl_util.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    srand_milliseconds();

    char* mac = NULL;
    char* command = NULL;
    char** arguments = NULL;
    int arguments_count = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-b") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: -b option: You have to specify a valid mac adress!\n");
                return 1;
            }
            i++;
            mac = argv[i];
        } else {
            fprintf(stderr, "Error: Unknown option '%s'!\n", argv[i]);
            fprintf(stderr, "Usage: %s [-b mac-adress]\n", argv[0]);
            return 1;
        }
    }

    bdaddr_t dst;
    if (mac != NULL && parse_mac(mac, &dst) != 0) {
        fprintf(stderr, "Error: -b option: You have to specify a valid mac adress!\n");
        return 1;
    } else if (read_default_mac(&dst) != 0) {
        fprintf(stderr, "Error: Unable to read valid mac adress from ~/.awoxlrc file!\n");
        return 1;
    }

    int sock = awoxl_connect(dst);
    if (sock < 0) {
        fprintf(stderr, "Error: Unable to connect! Errno: %d\n", errno);
        return 1;
    }

    // GO CRAZY!
    // do whatever you want in here

    awoxl_disconnect(sock);
}

