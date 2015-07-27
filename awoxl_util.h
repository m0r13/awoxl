#ifndef AWOXL_UTIL_H_
#define AWOXL_UTIL_H_

#include <bluetooth/bluetooth.h> /* bdaddr_t */

int parse_mac(const char* macstr, bdaddr_t* mac);
int parse_rgb(char** args, int args_count,
        unsigned char* r, unsigned char* g, unsigned char* b);

int read_default_mac(bdaddr_t* mac);

void srand_milliseconds();

#endif

