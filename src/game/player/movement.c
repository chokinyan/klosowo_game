#include "game/player/movement.h"
#include "game/board.h"
#include "game/player/capture.h"

bool moove_player( BoardCell board[BOARD_ROWS][BOARD_COLS], Position start, Position end, Teams pawn_team )
{

    if ( !is_position_accessible( board, start, end ) )
        return false;

    if ( !is_movement_possible( board, start, end ) )
        return false;

    board[end.y][end.x] = board[start.y][start.x];
    board[start.y][start.x].pawn = NULL_PAWN;

    seultout( board, start, end, pawn_team );
    linca( board, end, pawn_team );

    return true;
}

bool is_position_accessible( BoardCell board[BOARD_ROWS][BOARD_COLS], Position start, Position end )
{

    if ( !is_valid_position( board, end ) )
        return false;

    bool x_is_valide = start.x == end.x;
    bool y_is_valide = start.y == end.y;

    return x_is_valide ^ y_is_valide;
}

bool is_movement_possible( BoardCell board[BOARD_ROWS][BOARD_COLS], Position start, Position end )
{
    if ( start.x != end.x ) // Check for x
    {
        short step = start.x > end.x ? 1 : -1;
        for ( short x = end.x + step; x != start.x; x += step )
        {
            if ( !is_valid_position( board, ( Position ){ .x = x, .y = start.y } ) )
                return false;
        }
    }
    else // Check for y
    {
        short step = start.y > end.y ? 1 : -1;
        for ( short y = end.y + step; y != start.y; y += step )
        {
            if ( !is_valid_position( board, ( Position ){ .x = start.x, .y = y } ) )
                return false;
        }
    }

    return true;
}