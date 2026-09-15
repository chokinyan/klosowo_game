#include "network/client.h"
#include "log/log.h"
#include "network/network.h"
#include <arpa/inet.h>
#include <unistd.h>

bool init_client( short sock_fd, const char *ip, struct sockaddr_in addr )
{
    // 1. On cree la socket du client
    sock_fd = socket( AF_INET, SOCK_STREAM, 0 );
    if ( sock_fd < 0 )
        return 0;

    // 2. On convertit l'adresse IP en texte vers le
    // format reseau
    inet_pton( AF_INET, ip, &addr.sin_addr );

    // 3. On se connecte directement au serveur
    if ( connect( sock_fd, (struct sockaddr *)&addr, sizeof( addr ) ) < 0 )
    {
        close( sock_fd );
        sock_fd = -1;
        return 0;
    }
    return 1;
}

int network_send_barricade( int x, int y )
{
    char message[20];
    // On transforme les nombres X et Y en texte du style
    // "X,Y"
    log_debug( message, "%d,%d", x, y );
    return network_send( message );
}