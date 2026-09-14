#include "game/player/team_check.h"

bool check_pawn_is_enemy( TeamsColor pawn_team, BoardCell board_cell_check )
{
    if ( board_cell_check.type == BARRER || board_cell_check.pawn != NULL_PAWN )
    {
        return false;
    }

    if ( pawn_team == RED && board_cell_check.type != RED_TEAM )
    {
        return board_cell_check.type != EMPTY;
    }
    else if ( pawn_team == BLUE && board_cell_check.type != BLUE_TEAM )
    {
        return board_cell_check.type != EMPTY;
    }

    return false;
}

bool check_pawn_is_mate( TeamsColor pawn_team, BoardCell board_cell_check )
{
    if ( board_cell_check.type == BARRER || board_cell_check.pawn != NULL_PAWN )
    {
        return false;
    }

    if ( pawn_team == RED && board_cell_check.type == RED_TEAM )
    {
        return board_cell_check.type != EMPTY;
    }
    else if ( pawn_team == BLUE && board_cell_check.type == BLUE_TEAM )
    {
        return board_cell_check.type != EMPTY;
    }

    return false;
}

TeamsColor color_opponent( TeamsColor pawn_team )
{
    switch ( pawn_team )
    {
    case BLUE:
        return RED;
    case RED:
        return BLUE;
    default:
        return 2;
    }
}

char *color_name( TeamsColor pawn_team )
{
    switch ( pawn_team )
    {
    case BLUE:
        return "BLEU";
    case RED:
        return "ROUGE";
    default:
        return "?";
    }
}