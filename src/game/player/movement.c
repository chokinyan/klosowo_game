#include "game/player/movement.h"
#include "game/board.h"
#include "game/player/capture.h"
#include "log/log.h"
#include <string.h>

bool moove_player( Position start, Position end, TeamsColor pawn_team )
{

    if ( !is_position_accessible( start, end ) )
        return false;

    if ( !is_movement_possible( start, end ) )
        return false;

    is_conquete( start, end );

    if ( game_board[end.x][end.y].type == RED_CAMP || game_board[end.x][end.y].type == BLUE_CAMP )
    {
        game_board[end.x][end.y].pawn = game_board[start.x][start.y].pawn;
    }
    else
    {
        game_board[end.x][end.y] = game_board[start.x][start.y];
    }

    Position team_playing_pieces[10];

    memcpy( team_playing_pieces, pawn_team == RED ? red_team_pices_pos : blue_team_pices_pos,
            sizeof( team_playing_pieces ) );

    for ( short i = 0; i < 10; i++ )
    {
        if ( team_playing_pieces[i].x == -1 && team_playing_pieces[i].y == -1 )
            continue;
        if ( team_playing_pieces[i].x == start.x && team_playing_pieces[i].y == start.y )
        {
            team_playing_pieces[i] = end;
            break;
        }
    }

    memcpy( pawn_team == RED ? red_team_pices_pos : blue_team_pices_pos, team_playing_pieces,
            sizeof( team_playing_pieces ) );

    game_board[start.x][start.y].pawn = NULL_PAWN;

    seultout( start, end, pawn_team );
    linca( end, pawn_team );

    log_debug( "Move made : (%d,%d) -> (%d,%d) / round : %d", start.x, start.y, end.x, end.y, current_tour );

    return true;
}

bool is_position_accessible( Position start, Position end )
{

    if ( !is_valid_position( end ) )
        return false;

    bool x_is_valide = start.x == end.x;
    bool y_is_valide = start.y == end.y;

    return x_is_valide ^ y_is_valide;
}

bool is_movement_possible( Position start, Position end )
{
    if ( start.x != end.x ) // Check for x
    {
        short step = start.x > end.x ? 1 : -1;
        for ( short x = end.x + step; x != start.x; x += step )
        {
            if ( !is_valid_position( ( Position ){ .x = x, .y = start.y } ) )
                return false;
        }
    }
    else // Check for y
    {
        short step = start.y > end.y ? 1 : -1;
        for ( short y = end.y + step; y != start.y; y += step )
        {
            if ( !is_valid_position( ( Position ){ .x = start.x, .y = y } ) )
                return false;
        }
    }

    return true;
}

bool place_barrer( Position pos )
{
    if ( is_out_of_bound( pos ) )
        return false;

    if ( game_board[pos.x][pos.y].type == RED_CAMP || game_board[pos.x][pos.y].type == BLUE_CAMP )
        return false;

    if ( !is_own_side( current_team, pos ) || is_diagonal( pos ) || is_player_around( pos ) )
        return false;

    game_board[pos.x][pos.y].type = BARRER;

    return true;
}

bool is_conquete( Position start, Position end )
{

    PawnType pawn = game_board[start.x][start.y].pawn;

    {
        switch ( pawn )
        {

        case RED_KING:
            if ( game_board[end.x][end.y].type == BLUE_CAMP )
            {
                end_game( RED );
                return true;
            }
            return false;
        case BLUE_KING:
            if ( game_board[end.x][end.y].type == RED_CAMP )
            {
                end_game( BLUE );
                return true;
            }
            return false;
        default:
            return false;
        }
    }

    return false;
}

bool is_the_team( TeamsColor player_color, Position pos )
{

    if ( is_out_of_bound( pos ) )
        return false;

    PawnType pawn = game_board[pos.x][pos.y].pawn;

    switch ( player_color )
    {
    case BLUE:
        return pawn == BLUE_KING || pawn == BLUE_SOLDIER;
    case RED:
        return pawn == RED_KING || pawn == RED_SOLDIER;
    }

    return false;
}