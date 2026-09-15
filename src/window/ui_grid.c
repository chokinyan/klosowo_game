/**
 * @file ui_grid.c
 * @brief Implementation de ui_grid.h
 * @author grp 6 ensisa
 */
#include "window/ui_grid.h"
#include "game/board.h"
#include "game/player/movement.h"
#include "log/log.h"
#include "network/client.h"
#include "network/server.h"
#include "types/types.h"

void draw_board( GtkDrawingArea *drawing_area, cairo_t *cairo, int width, int height, gpointer user_data )
{
    (void)drawing_area;
    (void)user_data;

    const double cell_width = (double)width / BOARD_COLS;
    const double cell_height = (double)height / BOARD_ROWS;

    for ( int row = 0; row < BOARD_ROWS; row++ )
    {
        for ( int col = 0; col < BOARD_COLS; col++ )
        {
            BoardCell cell = game_board[row][col];
            switch ( cell.type )
            {
            case RED_TEAM:
                cairo_set_source_rgba( cairo, 1, 0, 0, 1.0 );
                if ( cell.pawn != NULL_PAWN )
                {
                    cairo_arc( cairo, ( col * cell_width ) + ( cell_width / 2 ),
                               ( row * cell_height ) + ( cell_height / 2 ), 10, 0, 2 * G_PI );
                    cairo_stroke_preserve( cairo );
                }
                if ( cell.pawn == RED_KING )
                {
                    cairo_arc( cairo, ( col * cell_width ) + ( cell_width / 2 ),
                               ( row * cell_height ) + ( cell_height / 2 ), 5, 0, 2 * G_PI );
                    cairo_fill_preserve( cairo );
                    cairo_stroke_preserve( cairo );
                }
                cairo_set_source_rgba( cairo, 1, 0, 0, 0.4 );
                break;

            case RED_CAMP:
                cairo_set_source_rgba( cairo, 1, 0, 0, 0.4 );
                break;
            case BLUE_CAMP:
                cairo_set_source_rgba( cairo, 0, 0, 1, 0.4 );
                break;
            case BLUE_TEAM:
                cairo_set_source_rgba( cairo, 0, 0, 1, 1.0 );
                if ( cell.pawn != NULL_PAWN )
                {
                    cairo_arc( cairo, ( col * cell_width ) + ( cell_width / 2 ),
                               ( row * cell_height ) + ( cell_height / 2 ), 10, 0, 2 * G_PI );
                    cairo_stroke_preserve( cairo );
                }
                if ( cell.pawn == BLUE_KING )
                {
                    cairo_arc( cairo, ( col * cell_width ) + ( cell_width / 2 ),
                               ( row * cell_height ) + ( cell_height / 2 ), 5, 0, 2 * G_PI );
                    cairo_fill_preserve( cairo );
                    cairo_stroke_preserve( cairo );
                }

                cairo_set_source_rgba( cairo, 0, 0, 1, 0.4 );
                break;
            case BARRER:
                cairo_set_source_rgba( cairo, 0.54, 0.32, 0.16, 1.0 );
                cairo_arc( cairo, ( col * cell_width ) + ( cell_width / 2 ),
                           ( row * cell_height ) + ( cell_height / 2 ), 10, 0, 2 * G_PI );
                cairo_fill_preserve( cairo );
                cairo_set_source_rgba( cairo, 0.54, 0.32, 0.16, 0.4 );
                break;
            default:
                cairo_set_source_rgba( cairo, 1, 1, 1, 0 );
                break;
            }
            if ( game_board[row][col].is_selected )
            {
                cairo_set_source_rgba( cairo, 0, 1, 0, 0.7 );
            }
            if ( is_diagonal( ( Position ){ .x = row, .y = col } ) && game_board[row][col].type == EMPTY )
            {
                cairo_set_source_rgba( cairo, 1.0, 1.0, 0.0, 0.7 );
            }
            cairo_rectangle( cairo, col * cell_width, row * cell_height, cell_width, cell_height );
            cairo_fill( cairo );
        }
    }

    cairo_set_source_rgb( cairo, 0.0, 0.0, 0.0 );
    cairo_set_line_width( cairo, 2 );
    for ( int row = 0; row < BOARD_ROWS; row++ )
        for ( int col = 0; col < BOARD_COLS; col++ )
            cairo_rectangle( cairo, col * cell_width, row * cell_height, cell_width, cell_height );
    cairo_stroke( cairo );
}

void cell_on_click( GtkGestureClick *gesture, int n_press, double x, double y, gpointer user_data )
{
    (void)gesture;
    (void)n_press;

    if ( ( is_client || is_server ) && current_team != my_color )
        return;

    GtkWidget *area = GTK_WIDGET( user_data );

    int area_width = gtk_widget_get_width( area );
    int area_height = gtk_widget_get_height( area );

    const double cell_width = (double)area_width / BOARD_COLS;
    const double cell_height = (double)area_height / BOARD_ROWS;

    int col = (int)( x / cell_width );
    int row = (int)( y / cell_height );

    if ( row >= 0 && row < BOARD_ROWS && col >= 0 && col < BOARD_COLS && !game_ended )
    {

        if ( current_tour < 2 ) // Place barrier phase
        {
            if ( is_client && is_connected )
            {
                int result = network_send_move( ( Position ){ .x = 0, .y = 0 }, ( Position ){ .x = row, .y = col } );
                if ( result == 0 )
                {
                    log_error( "Erreur lors de l'envoi du message au serveur.\n" );
                }
                else
                {
                    place_barrer( ( Position ){ .x = row, .y = col }, current_team );
                    current_tour++;
                    current_team = ( current_team == RED ) ? BLUE : RED;
                    log_debug( "Message envoyé au serveur : %d.%d\n", row, col );
                }

                return;
            }
            if ( place_barrer( ( Position ){ .x = row, .y = col }, current_team ) )
            {
                current_tour++;
                current_team = ( current_team == RED ) ? BLUE : RED;
            }
            gtk_widget_queue_draw( area );
            return;
        }

        if ( is_pawn_selected.is_selected )
        {
            Position start = { .x = is_pawn_selected.position.x, .y = is_pawn_selected.position.y };
            Position end = { .x = row, .y = col };

            if ( is_client && is_connected )
            {
                int result = network_send_move( start, end );
                if ( result == 0 )
                {
                    log_error( "Erreur lors de l'envoi du message au serveur.\n" );
                }
                else
                {
                    game_board[start.x][start.y].is_selected = false;
                    game_board[end.x][end.y].is_selected = false;
                    is_pawn_selected.is_selected = false;

                    current_tour++;

                    current_team = ( current_team == RED ) ? BLUE : RED;
                }
                return;
            }

            if ( is_movement_possible( start, end ) )
                if ( moove_player( start, end, current_team ) )
                {
                    game_board[start.x][start.y].is_selected = false;
                    game_board[end.x][end.y].is_selected = false;
                    is_pawn_selected.is_selected = false;

                    current_tour++;

                    current_team = ( current_team == RED ) ? BLUE : RED;
                }
        }

        if ( is_the_team( current_team, ( Position ){ .x = row, .y = col } ) )
        {
            g_print( "row : %i / col : %i\n", row, col );
            game_board[row][col].is_selected = true;
            is_pawn_selected.position.x = row;
            is_pawn_selected.position.y = col;
            is_pawn_selected.is_selected = true;
        }
        if ( current_tour >= MAX_TOUR )
        {
            short blue_point = 0;
            short red_point = 0;

            for ( int i = 0; i < BOARD_ROWS; i++ )
            {
                for ( int j = 0; j < BOARD_COLS; j++ )
                {
                    if ( game_board[i][j].type == RED_TEAM )
                    {
                        red_point++;
                    }
                    else if ( game_board[i][j].type == BLUE_TEAM )
                    {
                        blue_point++;
                    }

                    if ( game_board[i][j].pawn == RED_SOLDIER )
                    {
                        red_point++;
                    }
                    else if ( game_board[i][j].pawn == BLUE_SOLDIER )
                    {
                        blue_point++;
                    }
                }
            }
            end_game( red_point <= blue_point ? BLUE : RED );
        }
    }

    gtk_widget_queue_draw( area );
}

// ui_grid.c — ajoute l'implémentation, et #include "network/network.h" en haut
gboolean on_network_data( GIOChannel *source, GIOCondition condition, gpointer user_data )
{
    (void)source;
    (void)condition;
    GtkWidget *area = GTK_WIDGET( user_data );

    char buffer[30];
    int bytes = network_receive( buffer, sizeof( buffer ) );
    if ( bytes <= 0 )
        return TRUE; // rien de valide recu, on continue quand meme a surveiller

    Position start, end;
    if ( sscanf( buffer, "%hu.%hu,%hu.%hu", &start.x, &start.y, &end.x, &end.y ) != 4 )
        return TRUE; // format invalide, ignore

    if ( current_tour < 2 ) // Place barrier phase
    {
        place_barrer( end, current_team );
        current_tour++;
        current_team = ( current_team == RED ) ? BLUE : RED;
    }

    if ( moove_player( start, end, current_team ) )
    {
        game_board[start.x][start.y].is_selected = false;
        current_tour++;
        current_team = ( current_team == RED ) ? BLUE : RED;
    }

    gtk_widget_queue_draw( area );
    return TRUE; // TRUE = continue a surveiller la socket
}