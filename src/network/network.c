#include "network/network.h"
#include "log/log.h"
#include "network/client.h"
#include "network/server.h"

#include "types/types.h"
#include <arpa/inet.h>
#include <errno.h>
#include <regex.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// Variable globale pour garder en memoire le tuyau de
// connexion (la socket)
short sock_fd = -1;
bool is_connected = false;

int network_init( int is_server, const char *ip, int port )
{
    log_debug( "Réseau: initialisation en mode %s, adresse=%s, port=%d", is_server ? "serveur" : "client",
               ip != NULL ? ip : "(aucune)", port );

    if ( port < 1 || port > 65535 )
    {
        log_error( "Réseau: port invalide: %d", port );
        is_connected = false;
        return 0;
    }

    // On prepare la structure de l'adresse avec le port
    struct sockaddr_in addr;
    memset( &addr, 0, sizeof( addr ) );
    addr.sin_family = AF_INET;
    addr.sin_port = htons( (unsigned short)port );

    bool initialized = is_server ? init_server( addr ) : init_client( ip, addr );
    is_connected = initialized;

    if ( !initialized )
    {
        log_error( "Réseau: initialisation échouée (errno=%d: %s)", errno, strerror( errno ) );
        return 0;
    }

    log_info( "Réseau: connexion établie (fd=%d)", sock_fd );
    return 1;
}

void network_close( void )
{
    log_debug( "Réseau: fermeture demandée (fd=%d, connecté=%s)", sock_fd, is_connected ? "oui" : "non" );

    // Si la socket est ouverte, on la ferme proprement
    if ( sock_fd >= 0 )
    {
        close( sock_fd );
        sock_fd = -1;
    }

    is_connected = false;
}

bool check_good_format( char *recvbuffer )
{

    // Vérification du format avec une expression régulière
    regex_t regex;
    const char *pattern_barricade = "^(0\\.0|6\\.10),[0-6]\\.(10|[0-9])"; // Format attendu pour les barricades
    int verf_bar = regcomp( &regex, pattern_barricade, REG_EXTENDED );
    verf_bar = regexec( &regex, recvbuffer, 0, NULL, 0 );
    if ( verf_bar == 0 )
    {
        return true; // Format correct pour les barricades
    }

    const char *pattern_move = "^(10|[0-9])\\.[0-6]\\,(10|[0-9])\\.(10|[0-9])"; // Format attendu pour les mouvements
    int verf_move = regcomp( &regex, pattern_move, REG_EXTENDED );
    verf_move = regexec( &regex, recvbuffer, 0, NULL, 0 );
    if ( verf_move == 0 )
    {
        return true; // Format correct pour les mouvements
    }

    return false; // Retourne true si le format est correct
}