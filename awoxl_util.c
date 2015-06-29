#include "awoxl_util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

