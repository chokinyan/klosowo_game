#include "window/window.h"
#include "types/types.h"
#include "window/ui_grid.h"

void init_game_window( GtkWidget *window, WINDOW_TYPE window_type )
{
    gtk_window_set_default_size( GTK_WINDOW( window ), WINDOW_WIDTH, WINDOW_HEIGHT );
    gtk_window_set_resizable( GTK_WINDOW( window ), 0 );
    const char *title;
    switch ( window_type )
    {
    case CLIENT_BOARD:
        title = "jeu cote client";
        draw_client_board( window );
        break;

    case CLIENT_CONSOLE:
        title = "console cote client";
        draw_client_console( window );
        break;

    case SERVER_BOARD:
        title = "jeu cote server";
        draw_server_board( window );
        break;

    case SERVER_CONSOLE:
        title = "console cote server";
        draw_server_console( window );
        break;

    default:
        g_print( "Window type not found !" );
        return;
    }

    gtk_window_set_title( GTK_WINDOW( window ), title );

    gtk_window_present( GTK_WINDOW( window ) );
}

void init_game_board( GtkWidget *window )
{

    GtkWidget *area;
    GtkGesture *click;

    TeamsColor my_color = is_server ? RED : BLUE;

    area = gtk_drawing_area_new();

    gtk_drawing_area_set_draw_func( GTK_DRAWING_AREA( area ), draw_board, NULL, NULL );

    click = gtk_gesture_click_new();
    g_signal_connect( click, "pressed", G_CALLBACK( cell_on_click ), area );
    if ( is_server )
        g_io_add_watch( g_io_channel_unix_new( sock_fd ), G_IO_IN, on_network_data, area );
    else if ( is_client )
        g_io_add_watch( g_io_channel_unix_new( sock_fd ), G_IO_IN, on_network_data, area );
    gtk_widget_add_controller( area, GTK_EVENT_CONTROLLER( click ) );

    gtk_window_set_child( GTK_WINDOW( window ), area );
}

void init_game_console( GtkWidget *window ) { (void)window; }

void draw_client_board( GtkWidget *window ) { init_game_board( window ); }

void draw_client_console( GtkWidget *window ) { (void)window; }

void draw_server_board( GtkWidget *window ) { init_game_board( window ); }

void draw_server_console( GtkWidget *window ) { (void)window; }
