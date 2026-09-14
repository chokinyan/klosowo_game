/**
 * @file ui_grid.c
 * @brief Implementation de ui_grid.h
 * @author grp 6 ensisa
 */
#include "window/ui_grid.h"
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
            cairo_rectangle( cairo, col * cell_width, row * cell_height, cell_width, cell_height );
        }
    }

    cairo_set_source_rgb( cairo, 0.0, 0.0, 0.0 ); // Black lines
    cairo_set_line_width( cairo, 2 );
    cairo_stroke( cairo );
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
        g_print( "row : %i / col : %i\n", row, col );
    }
}
