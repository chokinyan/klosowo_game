#include "game/board.h"
#include <string.h>

BoardCell game_board[BOARD_ROWS][BOARD_COLS];
int current_tour;
TeamsColor current_team;
bool game_ended;

/**
 * @brief Setup the board with initial values
 */
void setup_board()
{
    memset( game_board, 0, sizeof( BoardCell ) * BOARD_ROWS * BOARD_COLS ); // Initialize all cells to EMPTY

    current_team = BLUE;
    current_tour = 0;
    game_ended = false;

    // Set up the blue team
    game_board[0][0].type = BLUE_CAMP; // Blue camp

    game_board[1][1].type = BLUE_TEAM; // Blue king
    game_board[1][1].pawn = BLUE_KING;

    // Set up the blue towers
    int blue_tower_positions[9][2] = { { 0, 2 }, { 0, 3 }, { 1, 2 }, { 1, 3 }, { 2, 0 },
                                       { 2, 1 }, { 2, 2 }, { 3, 0 }, { 3, 1 } };
    for ( int i = 0; i < 9; i++ )
    {
        int x = blue_tower_positions[i][0];
        int y = blue_tower_positions[i][1];
        game_board[x][y].type = BLUE_TEAM;
        game_board[x][y].pawn = BLUE_SOLDIER;
    }

    // Set up the red team
    game_board[6][10].type = RED_CAMP; // Red camp

    game_board[5][9].type = RED_TEAM; // Red king
    game_board[5][9].pawn = RED_KING;

    // Set up the red towers
    int red_tower_positions[9][2] = { { 3, 9 }, { 3, 10 }, { 4, 8 }, { 4, 9 }, { 4, 10 },
                                      { 5, 7 }, { 5, 8 },  { 6, 7 }, { 6, 8 } };
    for ( int i = 0; i < 9; i++ )
    {
        int x = red_tower_positions[i][0];
        int y = red_tower_positions[i][1];
        game_board[x][y].type = RED_TEAM;
        game_board[x][y].pawn = RED_SOLDIER;
    }
}

bool is_valid_position( Position pos ) { return !is_out_of_bound( pos ) && is_nothing_in_cell( pos ); }

bool is_out_of_bound( Position pos )
{
    bool x_out = pos.x < 0 || pos.x >= BOARD_ROWS;
    bool y_out = pos.y < 0 || pos.y >= BOARD_COLS;

    return x_out || y_out;
}

bool is_nothing_in_cell( Position pos )
{

    BoardCell cell = game_board[pos.x][pos.y];

    return cell.type != BARRER && cell.pawn != NULL_PAWN;
}

bool is_diagonal( Position pos )
{
    if ( is_out_of_bound( pos ) )
        return false;

    int extra = BOARD_COLS - BOARD_ROWS;         // Check more size of the rectangle to make a square
    int offset = ( BOARD_ROWS - 1 ) + extra / 2; // Offset to make a square

    int expected_row = offset - pos.y;
    if ( expected_row < 0 )
        expected_row = 0;
    if ( expected_row >= BOARD_ROWS )
        expected_row = BOARD_ROWS - 1;

    return expected_row == pos.x;
}

bool is_own_side( TeamsColor team, Position pos )
{
    int offset = ( BOARD_ROWS - 1 ) + ( BOARD_COLS - BOARD_ROWS ) / 2;
    int boundary = offset - pos.y; // pas de clamp ici

    return team == BLUE ? pos.x < boundary : pos.x > boundary;
}

bool is_player_around( Position pos )
{
    if ( !is_out_of_bound( ( Position ){ .x = pos.x + 1, .y = pos.y } ) &&
         game_board[pos.x + 1][pos.y].pawn != NULL_PAWN )
        return true;

    if ( !is_out_of_bound( ( Position ){ .x = pos.x - 1, .y = pos.y } ) &&
         game_board[pos.x - 1][pos.y].pawn != NULL_PAWN )
        return true;

    if ( !is_out_of_bound( ( Position ){ .x = pos.x, .y = pos.y + 1 } ) &&
         game_board[pos.x][pos.y + 1].pawn != NULL_PAWN )
        return true;

    if ( !is_out_of_bound( ( Position ){ .x = pos.x, .y = pos.y - 1 } ) &&
         game_board[pos.x][pos.y - 1].pawn != NULL_PAWN )
        return true;

    return false;
}