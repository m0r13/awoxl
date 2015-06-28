#ifndef AWOXL_PROTOCOL_H_
#define AWOXL_PROTOCOL_H_

#define AWOXL_BRIGHTNESS_DECREASE 0
#define AWOXL_BRIGHTNESS_INCREASE 1
#define AWOXL_BRIGHTNESS_MIN 2
#define AWOXL_BRIGHTNESS_MAX 11

#define AWOXL_TEMPERATURE_DECREASE 0
#define AWOXL_TEMPERATURE_INCREASE 1
#define AWOXL_TEMPERATURE_MIN 2
#define AWOXL_TEMPERATURE_MAX 11

unsigned int awoxl_protocol_on(unsigned char** buffer);
unsigned int awoxl_protocol_off(unsigned char** buffer);

unsigned int awoxl_protocol_brightness(unsigned char** buffer,
        unsigned char brightness);
unsigned int awoxl_protocol_white(unsigned char** buffer,
        unsigned char temperature);
unsigned int awoxl_protocol_rgb(unsigned char** buffer,
        unsigned char r, unsigned char g, unsigned char b, int special);

#endif /* AWOXL_PROTOCOL_H_ */

