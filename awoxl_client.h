#ifndef AWOXL_CLIENT_H_
#define AWOXL_CLIENT_H_

#include <bluetooth/bluetooth.h> /* bdaddr_t */

int awoxl_connect(bdaddr_t dst);
int awoxl_disconnect(int sock);

int awoxl_send_command(int sock, unsigned char* buffer, int len);

int awoxl_on(int sock);
int awoxl_off(int sock);
int awoxl_onoff(int sock, int on);
int awoxl_rgb(int sock, unsigned char r, unsigned char g, unsigned char b);

#endif /* AWOXL_CLIENT_H_ */

