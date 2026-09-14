#include "window/window.h"

void activate( GtkApplication *app )
{
    GtkWidget *window;

    window = gtk_application_window_new( app );

    init_game_window( window, CLIENT_BOARD );
}

int main( int argc, char **argv )
{
    GtkApplication *app;
    int status;

    app = gtk_application_new( "org.gtk.example", G_APPLICATION_DEFAULT_FLAGS );
    g_signal_connect( app, "activate", G_CALLBACK( activate ), NULL );

    status = g_application_run( G_APPLICATION( app ), argc, argv );
    g_object_unref( app );

    return status;
}