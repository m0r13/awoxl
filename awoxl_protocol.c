#include "awoxl_protocol.h"

#include <stdlib.h>
#include <string.h>

static unsigned char SEQUENCE_ON[12] = {0xAA, 0x0A, 0xFC, 0x3A, 0x86, 0x01, 0x0A, 0x01, 0x01, 0x00, 0x28, 0x0D};
static unsigned char SEQUENCE_OFF[12] = {0xAA, 0x0A, 0xFC, 0x3A, 0x86, 0x01, 0x0A, 0x01, 0x00, 0x01, 0x28, 0x0D};
static unsigned char SEQUENCE_BRIGHNTESS[12] = {0xAA, 0x0A, 0xFC, 0x3A, 0x86, 0x01, 0x0C, 0x01, 0x00, 0xEC, 0x15, 0x0D};
static unsigned char SEQUENCE_WHITE[12] = {0xAA, 0x0A, 0xFC, 0x3A, 0x86, 0x01, 0x0E, 0x01, 0x00, 0x14, 0x3F, 0x0D};
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

unsigned int awoxl_protocol_brightness(unsigned char** buffer,
        unsigned char brightness) {
    *buffer = (unsigned char*) malloc(12);
    memcpy(*buffer, SEQUENCE_BRIGHNTESS, 12);
    (*buffer)[8] = brightness;
    (*buffer)[9] = rand() % 256;
    (*buffer)[10] = checksum(*buffer, 12);
    return 12;
}

unsigned int awoxl_protocol_white(unsigned char** buffer,
        unsigned char temperature) {
    *buffer = (unsigned char*) malloc(12);
    memcpy(*buffer, SEQUENCE_WHITE, 12);
    (*buffer)[8] = temperature;
    (*buffer)[9] = rand() % 256;
    (*buffer)[10] = checksum(*buffer, 12);
    return 12;
}

unsigned int awoxl_protocol_rgb(unsigned char** buffer,
        unsigned char r, unsigned char g, unsigned char b, int special) {
    *buffer = (unsigned char*) malloc(17);
    memcpy(*buffer, SEQUENCE_RGB, 17);
    (*buffer)[8] = special ? 0x02 : 0x01;
    (*buffer)[9] = r;
    (*buffer)[10] = g;
    (*buffer)[11] = b;
    (*buffer)[14] = rand() % 256;
    (*buffer)[15] = checksum(*buffer, 17);
    return 17;
}

