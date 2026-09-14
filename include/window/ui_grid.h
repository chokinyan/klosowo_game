/**
 * \file ui_grid.h
 *  Dessin de la grille du plateau + gestion des clics
 * (IHM).
 * \author grp 6 immersion ensisa
 */
#ifndef KLOSNOWO_UI_GRID_H
#define KLOSNOWO_UI_GRID_H

#include <gtk/gtk.h>

void cell_on_click( GtkGestureClick *gesture, int n_press,
                    double x, double y,
                    gpointer user_data );

/**  Dessine les lignes de la grille du plateau (BOARD_ROWS
 * x BOARD_COLS). */
void draw_bord( GtkDrawingArea *drawing_area,
                cairo_t *cairo, int width, int height,
                gpointer user_data );

#endif
