#include "network/network.h"
#include <regex.h>

#include "network/client.h"
#include "network/server.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// Variable globale pour garder en memoire le tuyau de
// connexion (la socket)
static short sock_fd = -1;

int network_init( int is_server, const char *ip, int port )
{
    // On prepare la structure de l'adresse avec le port
    struct sockaddr_in addr;
    memset( &addr, 0, sizeof( addr ) );
    addr.sin_family = AF_INET;
    addr.sin_port = htons( (unsigned short)port );

    if ( is_server )
    {
        // --- ETAPE SERVEUR ---

        init_server( sock_fd, addr );
    }
    else
    {
        // --- ETAPE CLIENT ---

        init_client( sock_fd, ip, addr );
    }
    return 1; // La connexion est reussie !
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

int network_receive( char *buffer, int max_len )
{
    if ( sock_fd < 0 )
        return 0;

    // On vide le tableau avant de lire
    memset( buffer, 0, max_len );

    // On attend de recevoir des octets venant du reseau
    int bytes = recv( sock_fd, buffer, max_len - 1, 0 );
    if ( bytes <= 0 )
    {
        return 0; // Erreur ou deconnexion
    }

    buffer[bytes] = '\0'; // On rajoute la fin de chaine
    return bytes;
}

int network_send_move( int x1, int y1, int x2, int y2 )
{
    char message[30];
    // On transforme les 4 coordonnees en texte du style
    // "X1,Y1,X2,Y2"
    sprintf( message, "%d,%d,%d,%d", x1, y1, x2, y2 );
    return network_send( message );
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

bool check_good_format( int max_len )
{
    char recvbuffer[30];
    int bytes = recv( sock_fd, recvbuffer, max_len - 1, 0 );
    if ( bytes <= 0 )
    {
        return false; // Erreur ou deconnexion
    }

    // Vérification du format avec une expression régulière
    regex_t regex;
    const char *pattern_barricade = "^(0\\.0|6\\.10),[0-6]\\.[0-10]"; // Format attendu pour les barricades
    int verf_bar = regcomp( &regex, pattern_barricade, 0 );
    verf_bar = regexec( &regex, recvbuffer, 0, NULL, 0 );
    if ( verf_bar == 0 )
    {
        return true; // Format correct pour les barricades
    }

    const char *pattern_move =
        "^(0\\.0|6\\.10),[0-6]\\.[0-10],[0-6]\\.[0-10],[0-6]\\.[0-10]"; // Format attendu pour les mouvements
    int verf_move = regcomp( &regex, pattern_move, 0 );
    verf_move = regexec( &regex, recvbuffer, 0, NULL, 0 );
    if ( verf_move == 0 )
    {
        return true; // Format correct pour les mouvements
    }

    return false; // Retourne true si le format est correct
}