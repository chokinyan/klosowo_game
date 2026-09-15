#include "network/network.h"
#include "network/client.h"
#include "network/server.h"

#include "types/types.h"
#include <arpa/inet.h>
#include <regex.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// Variable globale pour garder en memoire le tuyau de
// connexion (la socket)
short sock_fd = -1;

int network_init( int is_server, const char *ip, int port )
{
    // On prepare la structure de l'adresse avec le port
    struct sockaddr_in addr;
    memset( &addr, 0, sizeof( addr ) );
    addr.sin_family = AF_INET;
    addr.sin_port = htons( (unsigned short)port );

    if ( is_server )
    {

        init_server( addr );
    }
    else
    {

        init_client( ip, addr );
    }

    return 1; // La connexion est reussie !
}

void network_close( void )
{
    // Si la socket est ouverte, on la ferme proprement
    if ( sock_fd >= 0 )
    {
        close( sock_fd );
        sock_fd = -1;
    }
}

bool check_good_format( char *recvbuffer )
{

    // Vérification du format avec une expression régulière
    regex_t regex;
    const char *pattern_barricade = "^(0\\.0|6\\.10),[0-6]\\.(10|[0-9])"; // Format attendu pour les barricades
    int verf_bar = regcomp( &regex, pattern_barricade, 0 );
    verf_bar = regexec( &regex, recvbuffer, 0, NULL, 0 );
    if ( verf_bar == 0 )
    {
        return true; // Format correct pour les barricades
    }

    const char *pattern_move = "^(10|[0-9])\\.[0-6]\\,(10|[0-9])\\.(10|[0-9])"; // Format attendu pour les mouvements
    int verf_move = regcomp( &regex, pattern_move, 0 );
    verf_move = regexec( &regex, recvbuffer, 0, NULL, 0 );
    if ( verf_move == 0 )
    {
        return true; // Format correct pour les mouvements
    }

    return false; // Retourne true si le format est correct
}