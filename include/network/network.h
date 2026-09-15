#ifndef KLOSOWO_NETWORK_H
#define KLOSOWO_NETWORK_H

#include <stdbool.h>

int network_init( int is_server, const char *ip, int port );

int network_send( const char *msg );

int network_receive( char *buffer, int max_len );

int network_send_move( int x1, int y1, int x2, int y2 );

void network_close( void );

bool check_good_format( int max_len );

#endif // KLOSOWO_NETWORK_H
