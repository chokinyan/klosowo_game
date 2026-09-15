#ifndef KLOSOWO_NETWORK_SERVER_H
#define KLOSOWO_NETWORK_SERVER_H

#include <netinet/in.h>
#include <stdbool.h>

bool init_server( short sock_fd, struct sockaddr_in addr );

#endif // KLOSOWO_NETWORK_SERVER_H
