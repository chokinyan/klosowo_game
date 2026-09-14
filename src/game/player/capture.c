#include "game/player/capture.h"
#include "game/board.h"

bool seultout( BoardCell board[BOARD_ROWS][BOARD_COLS], Position start, Position end )
{

    if ( start.x != end.x ) // Check for x
    {
        short step = start.x > end.x ? 1 : -1;
        end.x += step;
        if ( is_out_of_bound( end ) ) // Check out of bound for next cell
            return false;

        if ( is_nothing_in_cell( board, end ) || board[end.y][end.x].type == BARRER ) // Check if there a pawn
            return false;

        end.x += step;

        if ( is_out_of_bound( end ) ) // Check out of bound for next cell
        {

            capture( board, ( Position ){ .x = end.x - step, .y = end.y } );

            return true;
        }

        if ( is_nothing_in_cell( board, end ) && board[end.y][end.x].type != BARRER ) // Check if there a pawn
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

        if ( is_nothing_in_cell( board, end ) || board[end.y][end.x].type == BARRER ) // Check if there a pawn
            return false;

        end.y += step;

        if ( is_out_of_bound( end ) ) // Check out of bound for next cell
            return true;

        if ( is_nothing_in_cell( board, end ) && board[end.y][end.x].type != BARRER ) // Check if there no pawn
            return true;
    }

    return false;
}

bool capture( BoardCell board[BOARD_ROWS][BOARD_COLS], Position target_position )
{

    board[target_position.y][target_position.x].pawn = NULL_PAWN;
    board[target_position.y][target_position.x].type = EMPTY;

    return true;
}