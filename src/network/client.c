#include "network/client.h"
#include "log/log.h"
#include "types/types.h"
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

bool init_client( const char *ip, struct sockaddr_in addr )
{
    if ( ip == NULL )
    {
        log_error( "Client: aucune adresse serveur fournie" );
        return false;
    }

    log_debug( "Client: création de la socket vers %s:%u", ip, ntohs( addr.sin_port ) );

    // 1. On cree la socket du client
    sock_fd = socket( AF_INET, SOCK_STREAM, 0 );
    if ( sock_fd < 0 )
    {
        log_error( "Client: socket() a échoué: %s", strerror( errno ) );
        return 0;
    }

    // 2. On convertit l'adresse IP en texte vers le
    // format reseau
    if ( inet_pton( AF_INET, ip, &addr.sin_addr ) != 1 )
    {
        log_error( "Client: adresse IPv4 invalide: %s", ip );
        close( sock_fd );
        sock_fd = -1;
        return 0;
    }

    // 3. On se connecte directement au serveur
    if ( connect( sock_fd, (struct sockaddr *)&addr, sizeof( addr ) ) < 0 )
    {
        log_error( "Client: connexion à %s:%u impossible: %s", ip, ntohs( addr.sin_port ), strerror( errno ) );
        close( sock_fd );
        sock_fd = -1;
        return 0;
    }

    log_info( "Client: connecté au serveur %s:%u (fd=%d)", ip, ntohs( addr.sin_port ), sock_fd );
    return 1;
}

int network_send( const char *msg )
{
    if ( sock_fd < 0 || !is_connected )
    {
        log_warn( "Client: envoi impossible, connexion inactive (fd=%d)", sock_fd );
        return 0;
    }

    if ( msg == NULL )
    {
        log_error( "Client: message nul" );
        return 0;
    }

    // On calcule la taille du message et on l'envoie sur le
    // reseau
    size_t len = strlen( msg );
    size_t sent = 0;
    while ( sent < len )
    {
        ssize_t result = send( sock_fd, msg + sent, len - sent, 0 );
        if ( result <= 0 )
        {
            log_error( "Client: send() a échoué après %zu/%zu octets: %s", sent, len, strerror( errno ) );
            is_connected = false;
            return 0;
        }
        sent += (size_t)result;
    }

    log_debug( "Client: message envoyé (%zu octets): \"%s\"", sent, msg );
    return 1; // Envoi reussi
}

int network_send_move( Position start, Position end )
{
    char message[30];
    // On transforme les 4 coordonnees en texte du style
    // "X1,Y1,X2,Y2"
    sprintf( message, "%d.%d,%d.%d", start.x, start.y, end.x, end.y );
    log_debug( "Client: position envoyée (%d,%d) -> (%d,%d): \"%s\"", start.x, start.y, end.x, end.y, message );
    return network_send( message );
}