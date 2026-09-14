#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "types/types.h"

#include <stdbool.h>

/**
 * @brief Setup the board with initial values
 * @param board Board to initialize
 * @param red_pawns Array of red pawns
 * @param blue_pawns Array of blue pawns
 */
void setup_board( BoardCell board[BOARD_ROWS][BOARD_COLS] );

/**
 * @brief Check if a position is valid
 * @param pos Position to check
 * @return true if the position is valid, false otherwise
 */
bool is_valid_position( BoardCell board[BOARD_ROWS][BOARD_COLS], Position pos );

/**
 * @brief Check if position is out of bound
 *
 * @param pos
 * @return true if it is, false otherwise
 */

bool is_out_of_bound( Position pos );

/**
 * @brief check if somethik is in a cell
 *
 * @param board
 * @param pos
 * @return true if nothing, false otherwise
 */

bool is_nothing_in_cell( BoardCell board[BOARD_ROWS][BOARD_COLS], Position pos );

#endif