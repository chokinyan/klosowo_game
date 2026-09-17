#ifndef KLOSNOWO_CAPTURE_H
#define KLOSNOWO_CAPTURE_H

#include "types/types.h"
#include <stdbool.h>

/**
 * @brief
 *
 * @param board
 * @param pos
 * @return true is success, false otherwise
 */

bool linca( Position pos, TeamsColor pawn_team );

/**
 * @brief
 *
 * @param board
 * @param start
 * @param end
 * @return true is success, false otherwise
 */
bool seultout( Position start, Position end, TeamsColor pawn_team );

/**
 * @brief
 *
 * @param board
 * @param target_position
 * @return true is success, false otherwise
 */
bool capture( Position target_position );

bool check_seultout( Position start, Position end, TeamsColor pawn_team, BoardCell board[BOARD_ROWS][BOARD_COLS] );

void check_linca( Position pos, TeamsColor pawn_team, Position *kill_pawn_position, BoardCell board[BOARD_ROWS][BOARD_COLS] );

#endif // KLOSNOWO_CAPTURE_H
