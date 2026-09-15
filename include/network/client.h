#ifndef KLOSOWO_NETWORK_CLIENT_H
#define KLOSOWO_NETWORK_CLIENT_H

#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>

bool init_client( short sock_fd, const char *ip, struct sockaddr_in addr );

#endif // KLOSOWO_NETWORK_CLIENT_H
