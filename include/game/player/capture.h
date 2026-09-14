#ifndef CAPTURE_H
#define CAPTURE_H

#include "types/types.h"
#include <stdbool.h>

/**
 * @brief
 *
 * @param board
 * @param pos
 * @return true is success, false otherwise
 */

bool linca( BoardCell board[BOARD_ROWS][BOARD_COLS], Position pos, TeamsColor pawn_team );

/**
 * @brief
 *
 * @param board
 * @param start
 * @param end
 * @return true is success, false otherwise
 */
bool seultout( BoardCell board[BOARD_ROWS][BOARD_COLS], Position start, Position end, TeamsColor pawn_team );

/**
 * @brief
 *
 * @param board
 * @param target_position
 * @return true is success, false otherwise
 */
bool capture( BoardCell board[BOARD_ROWS][BOARD_COLS], Position target_position );

#endif // CAPTURE_H
