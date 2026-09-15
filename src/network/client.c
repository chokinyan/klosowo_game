#include "network/client.h"
#include "network/network.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

bool init_client( const char *ip, struct sockaddr_in addr )
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

int network_send( const char *msg )
{
    if ( sock_fd < 0 )
        return 0;

    // On calcule la taille du message et on l'envoie sur le
    // reseau
    int len = strlen( msg );
    if ( send( sock_fd, msg, len, 0 ) <= 0 )
    {
        return 0; // Erreur pendant l'envoi
    }
    return 1; // Envoi reussi
}

int network_send_move( Position start, Position end )
{
    char message[30];
    // On transforme les 4 coordonnees en texte du style
    // "X1,Y1,X2,Y2"
    sprintf( message, "%d.%d,%d.%d", start.x, start.y, end.x, end.y );
    return network_send( message );
}