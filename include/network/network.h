#ifndef KLOSOWO_NETWORK_H
#define KLOSOWO_NETWORK_H

#include <stdbool.h>

extern short sock_fd;

int network_init( int is_server, const char *ip, int port );

void network_close( void );

bool check_good_format(  char* recvbuffer );

#endif // KLOSOWO_NETWORK_H
