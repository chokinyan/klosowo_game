#ifndef TYPES_H
#define TYPES_H

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

#define BOARD_ROWS 7
#define BOARD_COLS 11

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
    KING,
    TOWER
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
typedef enum Teams
{
    BLUE,
    RED
} Teams;

/**
 * @brief Represent a board cell content
 */
typedef struct BoardCell
{
    PawnType pawn;
    CellsType type;
} BoardCell;

#endif