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

bool linca( BoardCell board[BOARD_ROWS][BOARD_COLS], Position pos, Teams pawn_team );

/**
 * @brief
 *
 * @param board
 * @param start
 * @param end
 * @return true is success, false otherwise
 */
bool seultout( BoardCell board[BOARD_ROWS][BOARD_COLS], Position start, Position end, Teams pawn_team );

/**
 * @brief
 *
 * @param board
 * @param target_position
 * @return true is success, false otherwise
 */
bool capture( BoardCell board[BOARD_ROWS][BOARD_COLS], Position target_position );

bool check_pawn_is_enemy( Teams pawn_team, BoardCell board_cell_check );

bool check_pawn_is_mate( Teams pawn_team, BoardCell board_cell_check );

#endif // CAPTURE_H
