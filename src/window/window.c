#include "window/window.h"
#include "log/log.h"
#include "types/types.h"
#include "window/ui_grid.h"

TeamsColor ai_team;

void init_game_window( GtkWidget *window, WINDOW_TYPE window_type )
{
    gtk_window_set_default_size( GTK_WINDOW( window ), WINDOW_WIDTH, WINDOW_HEIGHT );
    gtk_window_set_resizable( GTK_WINDOW( window ), 0 );
    const char *title;
    switch ( window_type )
    {
    case WINDOW_BOARD:
        title = "jeu du klosowo";
        draw_client_board( window );
        break;

    case WINDOW_CONSOLE:
        title = "console";
        draw_client_console( window );
        break;

    default:
        log_error( "Window type not found !" );
        return;
    }

    gtk_window_set_title( GTK_WINDOW( window ), title );

    gtk_window_present( GTK_WINDOW( window ) );
}

void init_game_board( GtkWidget *window )
{

    GtkWidget *area;
    GtkGesture *click;

    ai_team = is_server ? RED : BLUE;

    if ( !is_ai_mode )
    {
        if ( is_server )
            my_color = RED;
        else if ( is_client )
            my_color = BLUE;
    }
    else
    {
        my_color = ai_team;
    }

    area = gtk_drawing_area_new();

    gtk_drawing_area_set_draw_func( GTK_DRAWING_AREA( area ), draw_board, NULL, NULL );

    click = gtk_gesture_click_new();
    if ( is_local )
    {
        log_debug( "Local mode, connecting click event" );
        g_signal_connect( click, "pressed", G_CALLBACK( cell_on_click ), area );
    }
    if ( is_server )
    {
        log_debug( "Server mode, connecting network event" );
        g_io_add_watch( g_io_channel_unix_new( sock_fd ), G_IO_IN, on_network_data, area );
    }
    if ( is_client )
    {
        log_debug( "Client mode, connecting network event" );
        g_io_add_watch( g_io_channel_unix_new( sock_fd ), G_IO_IN, on_network_data, area );
        if ( !is_ai_mode )
        {
            log_debug( "Client mode, connecting click event" );
            g_signal_connect( click, "pressed", G_CALLBACK( cell_on_click ), area );
        }
    }
    if ( is_ai_mode )
    {
        log_debug( "AI mode, connecting AI event" );
        g_timeout_add( 100, (GSourceFunc)on_ai_playing, area );
    }

    gtk_widget_add_controller( area, GTK_EVENT_CONTROLLER( click ) );

    gtk_window_set_child( GTK_WINDOW( window ), area );
}

void init_game_console( GtkWidget *window ) { (void)window; }

void draw_client_board( GtkWidget *window ) { init_game_board( window ); }

void draw_client_console( GtkWidget *window ) { init_game_console( window ); }