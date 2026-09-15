#include "game/player/capture.h"
#include "game/board.h"
#include "game/player/team_check.h"

bool seultout( Position start, Position end, TeamsColor pawn_team )
{

    if ( start.x != end.x ) // Check for x
    {
        short step = start.x > end.x ? 1 : -1;
        end.x += step;
        if ( is_out_of_bound( end ) ) // Check out of bound for next cell
            return false;

        if ( is_nothing_in_cell( end ) || game_board[end.x][end.y].type == BARRER ||
             check_pawn_is_mate( pawn_team, game_board[end.x][end.y] ) ) // Check if there a pawn
            return false;

        end.x += step;

        if ( is_out_of_bound( end ) ) // Check out of bound for next cell
        {

            capture( ( Position ){ .x = end.x - step, .y = end.y } );

            return true;
        }

        if ( is_nothing_in_cell( end ) && game_board[end.x][end.y].type != BARRER &&
             check_pawn_is_mate( pawn_team, game_board[end.x][end.y] ) ) // Check if there a pawn
        {

            capture( ( Position ){ .x = end.x - step, .y = end.y } );

            return true;
        }
    }
    else // Check for y
    {
        short step = start.y > end.y ? 1 : -1;

        end.y += step;
        if ( is_out_of_bound( end ) ) // Check out of bound for next cell
            return false;

        if ( is_nothing_in_cell( end ) || game_board[end.x][end.y].type == BARRER ||
             check_pawn_is_mate( pawn_team, game_board[end.x][end.y] ) ) // Check if there a pawn
            return false;

        end.y += step;

        if ( is_out_of_bound( end ) )
        {

            capture( ( Position ){ .x = end.x, .y = end.y - step } );
            return true;
        } // Check out of bound for next cell

        if ( is_nothing_in_cell( end ) && game_board[end.x][end.y].type != BARRER &&
             check_pawn_is_mate( pawn_team, game_board[end.x][end.y] ) )
        {
            capture( ( Position ){ .x = end.x, .y = end.y - step } );
            return true;
        } // Check if there no pawn
    }

    return false;
}

bool linca( Position pos, TeamsColor pawn_team )
{
    Position kill_pawn_position[4] = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } };
    bool kill_pawn_found[4] = { false, false, false, false };

    // Start Check for x up
    if ( !is_out_of_bound( ( Position ){ .x = pos.x + 1, .y = pos.y } ) &&
         !is_out_of_bound( ( Position ){ .x = pos.x + 2, .y = pos.y } ) )
    {
        if ( check_pawn_is_enemy( pawn_team, game_board[pos.x + 1][pos.y] ) &&
             check_pawn_is_mate( pawn_team, game_board[pos.x + 2][pos.y] ) )
        {
            kill_pawn_position[0] = ( Position ){ .x = pos.x + 1, .y = pos.y };
            kill_pawn_found[0] = true;
        }
    }
    // End checking for x up

    // Start checking for x down
    if ( !is_out_of_bound( ( Position ){ .x = pos.x - 1, .y = pos.y } ) &&
         !is_out_of_bound( ( Position ){ .x = pos.x - 2, .y = pos.y } ) )
    {
        if ( check_pawn_is_enemy( pawn_team, game_board[pos.x - 1][pos.y] ) &&
             check_pawn_is_mate( pawn_team, game_board[pos.x - 2][pos.y] ) )
        {
            kill_pawn_position[1] = ( Position ){ .x = pos.x - 1, .y = pos.y };
            kill_pawn_found[1] = true;
        }
    }
    // End checking for x down

    // Start checking for y up
    if ( !is_out_of_bound( ( Position ){ .x = pos.x, .y = pos.y + 1 } ) &&
         !is_out_of_bound( ( Position ){ .x = pos.x, .y = pos.y + 2 } ) )
    {
        if ( check_pawn_is_enemy( pawn_team, game_board[pos.x][pos.y + 1] ) &&
             check_pawn_is_mate( pawn_team, game_board[pos.x][pos.y + 2] ) )
        {
            kill_pawn_position[2] = ( Position ){ .x = pos.x, .y = pos.y + 1 };
            kill_pawn_found[2] = true;
        }
    }
    // End checking for y up

    // Start checking for y down
    if ( !is_out_of_bound( ( Position ){ .x = pos.x, .y = pos.y - 1 } ) &&
         !is_out_of_bound( ( Position ){ .x = pos.x, .y = pos.y - 2 } ) )
    {
        if ( check_pawn_is_enemy( pawn_team, game_board[pos.x][pos.y - 1] ) &&
             check_pawn_is_mate( pawn_team, game_board[pos.x][pos.y - 2] ) )
        {
            kill_pawn_position[3] = ( Position ){ .x = pos.x, .y = pos.y - 1 };
            kill_pawn_found[3] = true;
        }
    }
    // End checking for y down

    for ( int i = 0; i < 4; i++ )
    {
        if ( kill_pawn_found[i] )
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
        game_ended = true;
        return true;
    }

    game_board[target_position.x][target_position.y].pawn = NULL_PAWN;
    game_board[target_position.x][target_position.y].type = EMPTY;

    return true;
}