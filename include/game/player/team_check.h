#ifndef KLOSNOWO_TEAM_CHECK_H
#define KLOSNOWO_TEAM_CHECK_H

#include "types/types.h"
#include <stdbool.h>

bool check_pawn_is_mate( TeamsColor pawn_team, BoardCell board_cell_check );

TeamsColor color_opponent( TeamsColor pawn_team );

char *color_name( TeamsColor pawn_team );

bool check_pawn_is_enemy( TeamsColor pawn_team, BoardCell board_cell_check );

#endif // KLOSNOWO_TEAM_CHECK_H