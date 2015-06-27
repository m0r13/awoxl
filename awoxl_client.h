#ifndef AWOXL_CLIENT_H_
#define AWOXL_CLIENT_H_

#include <bluetooth/bluetooth.h> /* bdaddr_t */

int awoxl_connect(bdaddr_t dst);
int awoxl_send_command(int sock, unsigned char* buffer, int len);
int awoxl_disconnect(int sock);

#endif /* AWOXL_CLIENT_H_ */

