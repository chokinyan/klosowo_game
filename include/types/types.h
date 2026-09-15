#ifndef KLOSNOWO_TYPES_H
#define KLOSNOWO_TYPES_H

#include <stdbool.h>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

#define BOARD_ROWS 7
#define BOARD_COLS 11

#define MAX_TOUR 64

extern bool game_ended;
extern int current_tour;

// Tout les type de logger possible
typedef enum
{
    LOG,
    DEBUG,
    WARN,
    ERROR,
    BASELOG,
} LogError;

/**
 * @brief Positon structur
 */
typedef struct Position
{
    short x;
    short y;
} Position;

/**
 * @brief All pawn types
 */
typedef enum
{
    NULL_PAWN,
    BLUE_KING,
    BLUE_SOLDIER,
    RED_KING,
    RED_SOLDIER,
} PawnType;

/**
 * @brief All cells types
 */
typedef enum
{
    EMPTY,
    RED_TEAM,
    RED_CAMP,
    BLUE_CAMP,
    BLUE_TEAM,
    BARRER,
} CellsType;

/**
 * @brief All possible teams color
 *
 */
typedef enum TeamsColor
{
    BLUE,
    RED
} TeamsColor;

/**
 * @brief Represent a board cell content
 */
typedef struct BoardCell
{
    PawnType pawn;
    CellsType type;
    bool is_selected;
} BoardCell;

/**
 * @brief Represent a selected pawn
 *
 */
typedef struct SelectedPawn
{
    Position position;
    bool is_selected;
} SelectedPawn;

extern Position diagonal_pos[11];

extern TeamsColor current_team;
extern SelectedPawn is_pawn_selected;
extern BoardCell game_board[BOARD_ROWS][BOARD_COLS];

#endif