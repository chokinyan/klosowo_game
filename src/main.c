#include "game/board.h"
#include "log/log.h"
#include "network/network.h"
#include "regex.h"
#include "types/types.h"
#include "window/window.h"

bool is_server = false;
bool is_client = false;

char *ip_address = NULL;
int port = 0;

void activate( GtkApplication *app )
{
    GtkWidget *window;

    window = gtk_application_window_new( app );

    init_game_window( window, CLIENT_BOARD );
}

int main( int argc, char **argv )
{

    regex_t regex;
    const char *pattern_server = "^[0-9]{1,5}$"; // Format attendu pour le port
    const char *pattern_client_connect =
        "^([0-9]{1,3}\\.){3}[0-9]{1,3}:[0-9]{1,5}$"; // Format attendu pour les barricades

    for ( int i = 1; i < argc; i++ )
    {
        int verf_client = regcomp( &regex, pattern_client_connect, 0 );
        verf_client = regexec( &regex, argv[i], 0, NULL, 0 );
        if ( verf_client == 0 )
        {
            char *colon = strrchr( ip_address, ':' );
            if ( colon != NULL )
            {
                *colon = '\0';
                port = atoi( colon + 1 );
            }
            ip_address = argv[i];
            continue;
        }
        int verf_port = regcomp( &regex, pattern_server, 0 );
        verf_port = regexec( &regex, argv[i], 0, NULL, 0 );
        if ( verf_port == 0 )
        {
            port = atoi( argv[i] );
            continue;
        }
        if ( strcmp( argv[i], "-s" ) == 0 )
        {
            is_server = true;
        }
        else if ( strcmp( argv[i], "-c" ) == 0 )
        {
            is_client = true;
        }
    }

    if ( is_server && is_client )
    {
        g_print( "Erreur : Vous ne pouvez pas etre a la fois serveur et client.\n" );
        return 1;
    }

    if ( is_server )
    {
        g_print( "Lancement du serveur sur le port %d...\n", port );
        network_init( 1, NULL, port );
    }
    else if ( is_client )
    {
        g_print( "Connexion au serveur %s sur le port %d...\n", ip_address, port );
        network_init( 0, ip_address, port );
    }

    GtkApplication *app;
    int status;

    setup_board();

    app = gtk_application_new( "org.gtk.example", G_APPLICATION_DEFAULT_FLAGS );
    g_signal_connect( app, "activate", G_CALLBACK( activate ), NULL );

    status = g_application_run( G_APPLICATION( app ), argc, argv );
    g_object_unref( app );

    return status;
}