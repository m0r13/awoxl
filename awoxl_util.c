#include "awoxl_util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_mac(const char* macstr, bdaddr_t* mac) {
    unsigned int m[6];
    int scanned = sscanf(macstr, "%02x:%02x:%02x:%02x:%02x:%02x",
            &m[5], &m[4], &m[3], &m[2], &m[1], &m[0]);
    if (scanned != 6)
        return -1;
    for (int i = 0; i < 6; i++)
        mac->b[i] = m[i];
    return 0;
}

int parse_rgb(char** args, int args_count,
        unsigned char* r, unsigned char* g, unsigned char* b) {
    const char* arg = args_count >= 1 ? args[0] : "";
    int rr, gg, bb;
    if (strcmp(arg, "random") == 0) {
        rr = rand() % 255;
        gg = rand() % 255;
        bb = rand() % 255;
    } else if (sscanf(arg, "%d,%d,%d", &rr, &gg, &bb) != 3) {
        return -1;
    }
    if (rr < 0 || rr >= 256
            || gg < 0 || gg >= 256
            || bb < 0 || bb >= 256)
        return -2;
    *r = rr;
    *g = gg;
    *b = bb;
    return 0;
}

int read_default_mac(bdaddr_t* mac) {
    const char* home = getenv("HOME");
    if (home == NULL)
        return -2;
    char* filename = (char*) malloc(sizeof(char) * (strlen(home) + strlen("/.awoxlrc") + 1));
    strcpy(filename, home);
    strcpy(filename + strlen(home), "/.awoxlrc");
    FILE* f = fopen(filename, "r");
    free(filename);
    if (f == NULL)
        return -3;
    char buf[100];
    if (!fgets(buf, 100, f)) {
        return -4;
        fclose(f);
    }
    fclose(f);
    return parse_mac(buf, mac);
}

