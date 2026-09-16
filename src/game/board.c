#include "game/board.h"
#include "log/log.h"
#include <string.h>

BoardCell game_board[BOARD_ROWS][BOARD_COLS];
int current_tour;
TeamsColor current_team;
bool game_ended;
SelectedPawn is_pawn_selected;
Position diagonal_pos[11];
TeamsColor my_color;

Position red_team_pices_pos[10];
Position blue_team_pices_pos[10];

/*
0    1    2    3    4    5    6    7    8    9   10
 -----------------------------------------------------
0  |  CB   .    TB   TB   .    .    .    .    J    J    J   |
1  |  .    RB   TB   TB   .    .    .    J    .    .    .   |
2  |  TB   TB   TB   .    .    .    J    .    .    .    .   |
3  |  TB   TB   .    .    .    J    .    .    .    TR   TR  |
4  |  .    .    .    .    J    .    .    .    TR   TR   TR  |
5  |  .    .    .    J    .    .    .    TR   TR   RR   .   |
6  |  J    J    J    .    .    .    .    TR   TR   .    CR  |
 -----------------------------------------------------


*/

/**
 * @brief Setup the board with initial values
 */
void setup_board()
{
    memset( game_board, 0, sizeof( BoardCell ) * BOARD_ROWS * BOARD_COLS ); // Initialize all cells to EMPTY

    current_team = BLUE;
    current_tour = 0;
    game_ended = false;

    is_pawn_selected.position.x = 0;
    is_pawn_selected.position.y = 0;
    is_pawn_selected.is_selected = false;

    diagonal_pos[0] = ( Position ){ .x = 0, .y = 8 };
    diagonal_pos[1] = ( Position ){ .x = 0, .y = 9 };
    diagonal_pos[2] = ( Position ){ .x = 0, .y = 10 };
    diagonal_pos[3] = ( Position ){ .x = 1, .y = 7 };
    diagonal_pos[4] = ( Position ){ .x = 2, .y = 6 };
    diagonal_pos[5] = ( Position ){ .x = 3, .y = 5 };
    diagonal_pos[6] = ( Position ){ .x = 4, .y = 4 };
    diagonal_pos[7] = ( Position ){ .x = 5, .y = 3 };
    diagonal_pos[8] = ( Position ){ .x = 6, .y = 0 };
    diagonal_pos[9] = ( Position ){ .x = 6, .y = 1 };
    diagonal_pos[10] = ( Position ){ .x = 6, .y = 2 };

    // Set up the blue team

    memcpy( blue_team_pices_pos,
            ( Position[] ){ { .x = 0, .y = 2 },
                            { .x = 0, .y = 3 },
                            { .x = 1, .y = 2 },
                            { .x = 1, .y = 3 },
                            { .x = 2, .y = 0 },
                            { .x = 2, .y = 1 },
                            { .x = 2, .y = 2 },
                            { .x = 3, .y = 0 },
                            { .x = 3, .y = 1 },
                            { .x = 1, .y = 1 } },
            sizeof blue_team_pices_pos );

    game_board[0][0].type = BLUE_CAMP; // Blue camp

    game_board[1][1].type = BLUE_TEAM; // Blue king
    game_board[1][1].pawn = BLUE_KING;

    // Set up the blue towers

    for ( int i = 0; i < 9; i++ )
    {
        int x = blue_team_pices_pos[i].x;
        int y = blue_team_pices_pos[i].y;
        game_board[x][y].type = BLUE_TEAM;
        game_board[x][y].pawn = BLUE_SOLDIER;
    }

    // Set up the red team

    memcpy( red_team_pices_pos,
            ( Position[] ){ { .x = 3, .y = 9 },
                            { .x = 3, .y = 10 },
                            { .x = 4, .y = 8 },
                            { .x = 4, .y = 9 },
                            { .x = 4, .y = 10 },
                            { .x = 5, .y = 7 },
                            { .x = 5, .y = 8 },
                            { .x = 6, .y = 7 },
                            { .x = 6, .y = 8 },
                            { .x = 5, .y = 9 } },
            sizeof red_team_pices_pos );

    game_board[6][10].type = RED_CAMP; // Red camp

    game_board[5][9].type = RED_TEAM; // Red king
    game_board[5][9].pawn = RED_KING;

    // Set up the red towers
    for ( int i = 0; i < 9; i++ )
    {
        int x = red_team_pices_pos[i].x;
        int y = red_team_pices_pos[i].y;
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

    return cell.type != BARRER && cell.pawn == NULL_PAWN;
}

bool is_diagonal( Position pos )
{

    for ( short i = 0; i < 11; i++ )
    {
        if ( diagonal_pos[i].x == pos.x && diagonal_pos[i].y == pos.y )
        {
            return true;
        }
    }

    return false;
}

bool is_own_side( TeamsColor team, Position pos )
{
    int offset = ( BOARD_ROWS - 1 ) + ( BOARD_COLS - BOARD_ROWS ) / 2;
    int boundary = offset - pos.y; // pas de clamp ici

    return team == BLUE ? pos.x < boundary : pos.x > boundary;
}

bool is_wrong_barrer_cell( Position pos )
{

    if ( current_team == BLUE )
    {
        if ( pos.x == 1 && pos.y == 0 )
            return true;
        else if ( pos.x == 0 && pos.y == 1 )
            return true;
    }
    else
    {
        if ( pos.x == 5 && pos.y == 10 )
            return true;
        else if ( pos.x == 6 && pos.y == 9 )
            return true;
    }

    return false;
}

void end_game( TeamsColor winner )
{
    game_ended = true;
    if ( winner == BLUE )
        log_debug( "Blue team won the game!" );
    else
        log_debug( "Red team won the game!" );
}