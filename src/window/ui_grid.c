/**
 * @file ui_grid.c
 * @brief Implementation de ui_grid.h
 * @author grp 6 ensisa
 */
#include "window/ui_grid.h"
#include "game/board.h"
#include "game/player/movement.h"
#include "types/types.h"

void draw_bord( GtkDrawingArea *drawing_area, cairo_t *cairo, int width, int height, gpointer user_data )
{
    (void)drawing_area;
    (void)user_data;

    const double cell_width = (double)width / BOARD_COLS;
    const double cell_height = (double)height / BOARD_ROWS;

    for ( int row = 0; row < BOARD_ROWS; row++ )
    {
        for ( int col = 0; col < BOARD_COLS; col++ )
        {
            switch ( game_board[row][col].type )
            {
            case RED_TEAM:
                cairo_set_source_rgba( cairo, 1, 0, 0, 0.7 );
                break;

            case RED_CAMP:
                cairo_set_source_rgba( cairo, 1, 0, 0, 0.7 );
                break;
            case BLUE_CAMP:
                cairo_set_source_rgba( cairo, 0, 0, 1, 0.7 );
                break;
            case BLUE_TEAM:
                cairo_arc( cairo, ( col * cell_width ) / 2, ( row * cell_height ) / 2, 20, 0, 2 * G_PI );
                cairo_stroke( cairo );
                cairo_set_source_rgba( cairo, 0, 0, 1, 0.7 );
                break;
            case BARRER:
                cairo_set_source_rgba( cairo, 0.54, 0.32, 0.16, 0.7 );
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

    for ( int row = 0; row < BOARD_ROWS; row++ )
        for ( int col = 0; col < BOARD_COLS; col++ )
        {
        }
}

void cell_on_click( GtkGestureClick *gesture, int n_press, double x, double y, gpointer user_data )
{
    (void)gesture;
    (void)n_press;

    GtkWidget *area = GTK_WIDGET( user_data );

    int area_width = gtk_widget_get_width( area );
    int area_height = gtk_widget_get_height( area );

    const double cell_width = (double)area_width / BOARD_COLS;
    const double cell_height = (double)area_height / BOARD_ROWS;

    int col = (int)( x / cell_width );
    int row = (int)( y / cell_height );

    if ( row >= 0 && row < BOARD_ROWS && col >= 0 && col < BOARD_COLS )
    {
        if ( is_pawn_selected.is_selected )
        {
            Position start = { .x = is_pawn_selected.position.x, .y = is_pawn_selected.position.y };
            Position end = { .x = row, .y = col };

            if ( is_movement_possible( start, end ) )
            {
                moove_player( start, end, current_team );
                is_pawn_selected.position.x = 0;
                is_pawn_selected.position.y = 0;
                is_pawn_selected.is_selected = false;

                current_tour++;

                current_team = ( current_team == RED ) ? BLUE : RED;
            }
        }

        if ( is_the_team( current_team, ( Position ){ .x = row, .y = col } ) )
        {
            g_print( "row : %i / col : %i\n", row, col );
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
            end_game( red_point > blue_point ? RED : BLUE );
        }
    }
}
