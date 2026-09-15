#ifndef KLOSNOWO_MOVEMENT_H
#define KLOSNOWO_MOVEMENT_H

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

bool moove_player( Position start, Position end, TeamsColor pawn_team );

/**
 * @brief Check if the position is valide
 *
 * @param board Game board
 * @param start initial position
 * @param end ended position
 * @return true if it can, false otherwise
 */
bool is_position_accessible( Position start, Position end );

/**
 * @brief Check if it can move
 *
 * @param board Game board
 * @param start initial position
 * @param end ended position
 * @return true if it can, false otherwise
 */
bool is_movement_possible( Position start, Position end );

bool place_barrer( Position pos, TeamsColor team );

bool is_conquete( Position start,Position end );

bool is_the_team( TeamsColor player_color, Position pos );

#endif // KLOSNOWO_MOVEMENT_H
