#include "game/player/capture.h"
#include "game/board.h"

bool seultout( BoardCell board[BOARD_ROWS][BOARD_COLS], Position start, Position end, Teams pawn_team )
{

    if ( start.x != end.x ) // Check for x
    {
        short step = start.x > end.x ? 1 : -1;
        end.x += step;
        if ( is_out_of_bound( end ) ) // Check out of bound for next cell
            return false;

        if ( is_nothing_in_cell( board, end ) || board[end.y][end.x].type == BARRER ||
             check_pawn_is_mate( pawn_team, board[end.y][end.x] ) ) // Check if there a pawn
            return false;

        end.x += step;

        if ( is_out_of_bound( end ) ) // Check out of bound for next cell
        {

            capture( board, ( Position ){ .x = end.x - step, .y = end.y } );

            return true;
        }

        if ( is_nothing_in_cell( board, end ) && board[end.y][end.x].type != BARRER &&
             check_pawn_is_mate( pawn_team, board[end.y][end.x] ) ) // Check if there a pawn
        {

            capture( board, ( Position ){ .x = end.x - step, .y = end.y } );

            return true;
        }
    }
    else // Check for y
    {
        short step = start.y > end.y ? 1 : -1;

        end.y += step;
        if ( is_out_of_bound( end ) ) // Check out of bound for next cell
            return false;

        if ( is_nothing_in_cell( board, end ) || board[end.y][end.x].type == BARRER ||
             check_pawn_is_mate( pawn_team, board[end.y][end.x] ) ) // Check if there a pawn
            return false;

        end.y += step;

        if ( is_out_of_bound( end ) ) // Check out of bound for next cell
            return true;

        if ( is_nothing_in_cell( board, end ) && board[end.y][end.x].type != BARRER &&
             check_pawn_is_mate( pawn_team, board[end.y][end.x] ) ) // Check if there no pawn
            return true;
    }

    return false;
}

bool linca( BoardCell board[BOARD_ROWS][BOARD_COLS], Position pos, Teams pawn_team )
{
    Position kill_pawn_position[4] = { 0 };

    // Start Check for x up
    if ( is_out_of_bound( ( Position ){ .x = pos.x + 1, .y = pos.y } ) ||
         is_out_of_bound( ( Position ){ .x = pos.x + 2, .y = pos.y } ) )
    {
        if ( check_pawn_is_enemy( pawn_team, board[pos.y][pos.x + 1] ) &&
             check_pawn_is_mate( pawn_team, board[pos.y][pos.x + 2] ) )
        {
            kill_pawn_position[0] = ( Position ){ .x = pos.x + 1, .y = pos.y };
        }
    }
    // End checking for x up

    // Start checking for x down
    if ( is_out_of_bound( ( Position ){ .x = pos.x - 1, .y = pos.y } ) ||
         is_out_of_bound( ( Position ){ .x = pos.x - 2, .y = pos.y } ) )
    {
        if ( check_pawn_is_enemy( pawn_team, board[pos.y][pos.x - 1] ) &&
             check_pawn_is_mate( pawn_team, board[pos.y][pos.x - 2] ) )
        {
            kill_pawn_position[1] = ( Position ){ .x = pos.x - 1, .y = pos.y };
        }
    }
    // End checking for x down

    // Start checking for y up
    if ( is_out_of_bound( ( Position ){ .x = pos.x, .y = pos.y + 1 } ) ||
         is_out_of_bound( ( Position ){ .x = pos.x, .y = pos.y + 2 } ) )
    {
        if ( check_pawn_is_enemy( pawn_team, board[pos.y + 1][pos.x] ) &&
             check_pawn_is_mate( pawn_team, board[pos.y + 2][pos.x] ) )
        {
            kill_pawn_position[2] = ( Position ){ .x = pos.x, .y = pos.y + 1 };
        }
    }
    // End checking for y up

    // Start checking for y down
    if ( is_out_of_bound( ( Position ){ .x = pos.x, .y = pos.y - 1 } ) ||
         is_out_of_bound( ( Position ){ .x = pos.x, .y = pos.y - 2 } ) )
    {
        if ( check_pawn_is_enemy( pawn_team, board[pos.y - 1][pos.x] ) &&
             check_pawn_is_mate( pawn_team, board[pos.y - 2][pos.x] ) )
        {
            kill_pawn_position[3] = ( Position ){ .x = pos.x, .y = pos.y - 1 };
        }
    }
    // End checking for y down

    for ( int i = 0; i < 4; i++ )
    {
        if ( kill_pawn_position[i].x != 0 && kill_pawn_position[i].y != 0 )
        {
            capture( board, kill_pawn_position[i] );
        }
    }

    return true;
}

bool capture( BoardCell board[BOARD_ROWS][BOARD_COLS], Position target_position )
{

    board[target_position.y][target_position.x].pawn = NULL_PAWN;
    board[target_position.y][target_position.x].type = EMPTY;

    return true;
}

bool check_pawn_is_enemy( Teams pawn_team, BoardCell board_cell_check )
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

bool check_pawn_is_mate( Teams pawn_team, BoardCell board_cell_check )
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