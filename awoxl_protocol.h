#ifndef AWOXL_PROTOCOL_H_
#define AWOXL_PROTOCOL_H_

unsigned int awoxl_protocol_on(unsigned char** buffer);
unsigned int awoxl_protocol_off(unsigned char** buffer);

unsigned int awoxl_protocol_rgb(unsigned char** buffer,
        unsigned char r, unsigned char g, unsigned char b);

#endif /* AWOXL_PROTOCOL_H_ */

