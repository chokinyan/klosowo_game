#include "network/server.h"
#include "network/network.h"
#include <string.h>
#include <unistd.h>

bool init_server( struct sockaddr_in addr )
{
    int listen_fd = socket( AF_INET, SOCK_STREAM, 0 );
    if ( listen_fd < 0 )
        return 0;

    // Option pour pouvoir reutiliser le port sans
    // attendre si on relance le programme
    int opt = 1;
    setsockopt( listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof( opt ) );

    // 2. On attache la socket au port voulu (bind)
    addr.sin_addr.s_addr = INADDR_ANY;
    if ( bind( listen_fd, (struct sockaddr *)&addr, sizeof( addr ) ) < 0 )
    {
        close( listen_fd );
        return 0;
    }

    // 3. On met le serveur en attente (listen)
    if ( listen( listen_fd, 1 ) < 0 )
    {
        close( listen_fd );
        return 0;
    }

    // 4. On accepte le joueur client qui se connecte
    sock_fd = accept( listen_fd, NULL, NULL );
    close( listen_fd ); // On ferme la socket d'ecoute
                        // car on a notre joueur
    if ( sock_fd < 0 )
        return 0;
    return 1;
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



    if ( !check_good_format( buffer ) )
    {
        return 0; // Format incorrect
    }

    return bytes;
}