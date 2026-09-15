#ifndef KLOSOWO_NETWORK_CLIENT_H
#define KLOSOWO_NETWORK_CLIENT_H

#include "types/types.h"
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>

bool init_client( const char *ip, struct sockaddr_in addr );

int network_send( const char *msg );

int network_send_move( Position start, Position end );

#endif // KLOSOWO_NETWORK_CLIENT_H
