#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "types/types.h"
#include <stdbool.h>

/**
 * @brief Move a player to a new position
 *
 * @param board Current game board
 * @param start initial position
 * @param end ended position
 * @return true if the move was successful, false otherwise
 */

bool moove_player( BoardCell board[BOARD_ROWS][BOARD_COLS], Position start, Position end, TeamsColor pawn_team );

/**
 * @brief Check if the position is valide
 *
 * @param board Game board
 * @param start initial position
 * @param end ended position
 * @return true if it can, false otherwise
 */
bool is_position_accessible( BoardCell board[BOARD_ROWS][BOARD_COLS], Position start, Position end );

/**
 * @brief Check if it can move
 *
 * @param board Game board
 * @param start initial position
 * @param end ended position
 * @return true if it can, false otherwise
 */
bool is_movement_possible( BoardCell board[BOARD_ROWS][BOARD_COLS], Position start, Position end );

#endif // MOVEMENT_H
