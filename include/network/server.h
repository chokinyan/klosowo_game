#ifndef KLOSOWO_NETWORK_SERVER_H
#define KLOSOWO_NETWORK_SERVER_H

#include <netinet/in.h>
#include <stdbool.h>

bool init_server( struct sockaddr_in addr );

bool network_receive( char *buffer, int max_len );


#endif // KLOSOWO_NETWORK_SERVER_H
