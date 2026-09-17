#include "game/player/capture.h"
#include "ai/ai.h"
#include "game/board.h"
#include "game/player/team_check.h"

bool seultout( Position start, Position end, TeamsColor pawn_team )
{

    if ( start.x != end.x ) // Check for x
    {
        char step = start.x < end.x ? 1 : -1;
        if ( check_seultout( start, end, pawn_team, game_board ) )
        {
            capture( ( Position ){ .x = end.x + step, .y = end.y } );
            return true;
        }
    }
    else // Check for y
    {
        char step = start.y < end.y ? 1 : -1;

        if ( check_seultout( start, end, pawn_team, game_board ) )
        {
            capture( ( Position ){ .x = end.x, .y = end.y + step } );
            return true;
        }
    }

    return false;
}

bool linca( Position pos, TeamsColor pawn_team )
{
    Position kill_pawn_position[4] = { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } };

    check_linca( pos, pawn_team, kill_pawn_position, game_board );

    for ( int i = 0; i < 4; i++ )
    {
        if ( kill_pawn_position[i].x != -1 && kill_pawn_position[i].y != -1 )
        {
            capture( kill_pawn_position[i] );
        }
    }

    return true;
}

bool capture( Position target_position )
{

    BoardCell target = game_board[target_position.x][target_position.y];

    if ( target.pawn == RED_KING || target.pawn == BLUE_KING )
    {
        end_game( target.pawn == RED_KING ? BLUE : RED );
        return true;
    }

    Position *team_pieces_pos = target.pawn == RED_SOLDIER ? red_team_pices_pos : blue_team_pices_pos;

    for ( int i = 0; i < AI_MAX_PIECES; i++ )
    {
        if ( team_pieces_pos[i].x == target_position.x && team_pieces_pos[i].y == target_position.y )
        {
            team_pieces_pos[i] = ( Position ){ .x = -1, .y = -1 };
            break;
        }
    }

    game_board[target_position.x][target_position.y].pawn = NULL_PAWN;
    game_board[target_position.x][target_position.y].type = EMPTY;

    return true;
}

bool capture_win( Position target_position )
{
    BoardCell target = game_board[target_position.x][target_position.y];

    if ( target.pawn == RED_KING || target.pawn == BLUE_KING )
    {
        return true;
    }

    return false;
}

bool check_seultout( Position start, Position end, TeamsColor pawn_team, BoardCell board[BOARD_ROWS][BOARD_COLS] )
{
    if ( start.x != end.x ) // Check for x
    {
        char step = start.x < end.x ? 1 : -1;
        end.x += step;
        if ( is_out_of_bound( end ) ) // Check out of bound for next cell
            return false;

        if ( !check_pawn_is_enemy( pawn_team, board[end.x][end.y] ) ) // Check if there a enemy pawn
            return false;

        end.x += step;

        if ( is_out_of_bound( end ) ) // Check out of bound for next cell
            return true;

        if ( is_nothing_in_cell( end ) ) // Check if there a pawn
            return true;
    }
    else // Check for y
    {
        char step = start.y < end.y ? 1 : -1;

        end.y += step;
        if ( is_out_of_bound( end ) ) // Check out of bound for next cell
            return false;

        if ( !check_pawn_is_enemy( pawn_team, board[end.x][end.y] ) ) // Check if there a enemy pawn
            return false;

        end.y += step;

        if ( is_out_of_bound( end ) )
            return true; // Check out of bound for next cell

        if ( is_nothing_in_cell( end ) )
            return true; // Check if there no pawn
    }

    return false;
}

void check_linca( Position pos, TeamsColor pawn_team, Position *kill_pawn_position,
                  BoardCell board[BOARD_ROWS][BOARD_COLS] )
{
    // Start Check for x up
    if ( !is_out_of_bound( ( Position ){ .x = pos.x + 1, .y = pos.y } ) &&
         !is_out_of_bound( ( Position ){ .x = pos.x + 2, .y = pos.y } ) )
    {
        if ( check_pawn_is_enemy( pawn_team, board[pos.x + 1][pos.y] ) &&
             check_pawn_is_mate( pawn_team, board[pos.x + 2][pos.y] ) )
        {
            kill_pawn_position[0] = ( Position ){ .x = pos.x + 1, .y = pos.y };
        }
    }
    // End checking for x up

    // Start checking for x down
    if ( !is_out_of_bound( ( Position ){ .x = pos.x - 1, .y = pos.y } ) &&
         !is_out_of_bound( ( Position ){ .x = pos.x - 2, .y = pos.y } ) )
    {
        if ( check_pawn_is_enemy( pawn_team, board[pos.x - 1][pos.y] ) &&
             check_pawn_is_mate( pawn_team, board[pos.x - 2][pos.y] ) )
        {
            kill_pawn_position[1] = ( Position ){ .x = pos.x - 1, .y = pos.y };
        }
    }
    // End checking for x down

    // Start checking for y up
    if ( !is_out_of_bound( ( Position ){ .x = pos.x, .y = pos.y + 1 } ) &&
         !is_out_of_bound( ( Position ){ .x = pos.x, .y = pos.y + 2 } ) )
    {
        if ( check_pawn_is_enemy( pawn_team, board[pos.x][pos.y + 1] ) &&
             check_pawn_is_mate( pawn_team, board[pos.x][pos.y + 2] ) )
        {
            kill_pawn_position[2] = ( Position ){ .x = pos.x, .y = pos.y + 1 };
        }
    }
    // End checking for y up

    // Start checking for y down
    if ( !is_out_of_bound( ( Position ){ .x = pos.x, .y = pos.y - 1 } ) &&
         !is_out_of_bound( ( Position ){ .x = pos.x, .y = pos.y - 2 } ) )
    {
        if ( check_pawn_is_enemy( pawn_team, board[pos.x][pos.y - 1] ) &&
             check_pawn_is_mate( pawn_team, board[pos.x][pos.y - 2] ) )
        {
            kill_pawn_position[3] = ( Position ){ .x = pos.x, .y = pos.y - 1 };
        }
    }
    // End checking for y down
}