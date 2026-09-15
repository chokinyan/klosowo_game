#include "network/server.h"
#include "log/log.h"
#include "network/network.h"
#include "types/types.h"
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

char *opposent_ip = NULL;

bool init_server( struct sockaddr_in addr )
{
    log_debug( "Serveur: démarrage sur le port réseau %u", ntohs( addr.sin_port ) );

    int listen_fd = socket( AF_INET, SOCK_STREAM, 0 );
    if ( listen_fd < 0 )
    {
        log_error( "Serveur: socket() a échoué: %s", strerror( errno ) );
        return 0;
    }

    log_debug( "Serveur: socket d'écoute créée (fd=%d)", listen_fd );

    // Option pour pouvoir reutiliser le port sans
    // attendre si on relance le programme
    int opt = 1;
    if ( setsockopt( listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof( opt ) ) < 0 )
        log_warn( "Serveur: setsockopt(SO_REUSEADDR) a échoué: %s", strerror( errno ) );
    else
        log_debug( "Serveur: réutilisation d'adresse activée" );

    // 2. On attache la socket au port voulu (bind)
    addr.sin_addr.s_addr = INADDR_ANY;
    if ( bind( listen_fd, (struct sockaddr *)&addr, sizeof( addr ) ) < 0 )
    {
        log_error( "Serveur: bind() a échoué sur le port %u: %s", ntohs( addr.sin_port ), strerror( errno ) );
        close( listen_fd );
        return 0;
    }

    log_debug( "Serveur: socket attachée au port %u", ntohs( addr.sin_port ) );

    // 3. On met le serveur en attente (listen)
    if ( listen( listen_fd, 1 ) < 0 )
    {
        log_error( "Serveur: listen() a échoué: %s", strerror( errno ) );
        close( listen_fd );
        return 0;
    }

    log_info( "Serveur: en attente d'une connexion cliente" );

    // 4. On accepte le joueur client qui se connecte
    sock_fd = accept( listen_fd, NULL, NULL );
    if ( opposent_ip == NULL )
        opposent_ip = inet_ntoa( addr.sin_addr );

    if ( sock_fd < 0 )
    {
        log_error( "Serveur: accept() a échoué: %s", strerror( errno ) );
        return 0;
    }

    log_info( "Serveur: client connecté (fd=%d, adresse=%s)", sock_fd, opposent_ip );
    return 1;
}

int network_receive( char *buffer, int max_len )
{
    log_debug( "Serveur: réception demandée (fd=%d, capacité=%d, connecté=%s)", sock_fd, max_len,
               is_connected ? "oui" : "non" );

    if ( buffer == NULL || max_len <= 0 )
    {
        log_error( "Serveur: buffer de réception invalide (buffer=%p, capacité=%d)", (void *)buffer, max_len );
        return 0;
    }

    if ( sock_fd < 0 )
    {
        log_warn( "Serveur: réception ignorée, aucune socket active" );
        return 0;
    }

    if ( !is_connected )
    {
        log_warn( "Serveur: réception ignorée, connexion marquée inactive" );
        return 0;
    }

    if ( opposent_ip == NULL )
    {
        log_warn( "Serveur: réception ignorée, adresse du client inconnue" );
        return 0;
    }

    // On vide le tableau avant de lire
    memset( buffer, 0, max_len );

    // On attend de recevoir des octets venant du reseau
    int bytes = recv( sock_fd, buffer, max_len - 1, 0 );
    if ( bytes <= 0 )
    {
        if ( bytes == 0 )
            log_warn( "Serveur: le client a fermé la connexion" );
        else
            log_error( "Serveur: recv() a échoué: %s", strerror( errno ) );
        return 0; // Erreur ou deconnexion
    }

    buffer[bytes] = '\0'; // On rajoute la fin de chaine

    log_debug( "Serveur: message reçu (%d octets): \"%s\"", bytes, buffer );

    return bytes;
}