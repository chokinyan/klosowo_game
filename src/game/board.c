#include "game/board.h"
#include <string.h>

/**
 * @brief Setup the board with initial values
 * @param board Board to initialize
 * @param red_pawns Array of red pawns
 * @param blue_pawns Array of blue pawns
 */
void setup_board( BoardCell board[BOARD_ROWS][BOARD_COLS] )
{
    memset( board, 0, sizeof( BoardCell ) * BOARD_ROWS * BOARD_COLS ); // Initialize all cells to EMPTY

    // Set up the blue team
    board[0][0].type = BLUE_CAMP; // Blue camp
    board[1][1].type = BLUE_TEAM; // Blue king

    // Set up the blue towers
    int blue_tower_positions[9][2] = { { 0, 2 }, { 0, 3 }, { 1, 2 }, { 1, 3 }, { 2, 0 },
                                       { 2, 1 }, { 2, 2 }, { 3, 0 }, { 3, 1 } };
    for ( int i = 0; i < 9; i++ )
    {
        int x = blue_tower_positions[i][0];
        int y = blue_tower_positions[i][1];
        board[x][y].type = BLUE_TEAM;
    }

    // Set up the red team
    board[6][10].type = RED_CAMP; // Red camp
    board[5][9].type = RED_TEAM;  // Red king

    // Set up the red towers
    int red_tower_positions[9][2] = { { 3, 9 }, { 3, 10 }, { 4, 8 }, { 4, 9 }, { 4, 10 },
                                      { 5, 7 }, { 5, 8 },  { 6, 7 }, { 6, 8 } };
    for ( int i = 0; i < 9; i++ )
    {
        int x = red_tower_positions[i][0];
        int y = red_tower_positions[i][1];
        board[x][y].type = RED_TEAM;
    }
}

bool is_valid_position( BoardCell board[BOARD_ROWS][BOARD_COLS], Position pos )
{
    return !is_out_of_bound( pos ) || is_nothing_in_cell( board, pos );
}

bool is_out_of_bound( Position pos )
{
    bool x_out = pos.x < 0 || pos.x >= BOARD_ROWS;
    bool y_out = pos.y < 0 || pos.y >= BOARD_COLS;

    return x_out || y_out;
}

bool is_nothing_in_cell( BoardCell board[BOARD_ROWS][BOARD_COLS], Position pos )
{

    BoardCell cell = board[pos.x][pos.y];

    return cell.type == BARRER || cell.pawn == NULL_PAWN;
}
