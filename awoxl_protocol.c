#include "awoxl_protocol.h"

#include <stdlib.h>
#include <string.h>

static unsigned char SEQUENCE_ON[12] = {0xAA, 0x0A, 0xFC, 0x3A, 0x86, 0x01, 0x0A, 0x01, 0x01, 0x00, 0x28, 0x0D};
static unsigned char SEQUENCE_OFF[12] = {0xAA, 0x0A, 0xFC, 0x3A, 0x86, 0x01, 0x0A, 0x01, 0x00, 0x01, 0x28, 0x0D};
static unsigned char SEQUENCE_RGB[17] = {0xAA, 0x0A, 0xFC, 0x3A, 0x86, 0x01, 0x0D, 0x06, 0x01, 0x00, 0x00, 0x00, 0x20, 0x30, 0xF8, 0x78, 0x0D};

static unsigned char checksum(unsigned char* buffer, unsigned int len) {
    unsigned char sum = 0;
    for (unsigned int i = 1; i+2 < len; i++)
        sum += buffer[i];
    return sum + 85;
}

unsigned int awoxl_protocol_on(unsigned char** buffer) {
    *buffer = (unsigned char*) malloc(12);
    memcpy(*buffer, SEQUENCE_ON, 12);
    return 12;
}

unsigned int awoxl_protocol_off(unsigned char** buffer) {
    *buffer = (unsigned char*) malloc(12);
    memcpy(*buffer, SEQUENCE_OFF, 12);
    return 12;
}

unsigned int awoxl_protocol_rgb(unsigned char** buffer,
        unsigned char r, unsigned char g, unsigned char b) {
    *buffer = (unsigned char*) malloc(17);
    memcpy(*buffer, SEQUENCE_RGB, 17);
    (*buffer)[9] = r;
    (*buffer)[10] = g;
    (*buffer)[11] = b;
    (*buffer)[14] = rand() % 255;
    (*buffer)[15] = checksum(*buffer, 17);
    return 17;
}

