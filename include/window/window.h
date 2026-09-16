#ifndef KLOSNOWO_WINDOW_H
#define KLOSNOWO_WINDOW_H

#include <gtk/gtk.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

typedef enum
{
    WINDOW_BOARD,
    WINDOW_CONSOLE,
} WINDOW_TYPE;

void init_game_window( GtkWidget *window, WINDOW_TYPE type );

void init_game_board( GtkWidget *window );
void init_game_console( GtkWidget *window );

void draw_client_board( GtkWidget *window );
void draw_client_console( GtkWidget *window );

#endif
