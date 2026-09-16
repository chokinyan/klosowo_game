#ifndef KLOSNOWO_TYPES_H
#define KLOSNOWO_TYPES_H

#include <stdbool.h>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

#define BOARD_ROWS 7
#define BOARD_COLS 11

#define MAX_TOUR 66

extern bool game_ended;
extern int current_tour;

// Variable globale pour garder en memoire le tuyau de
// connexion (la socket)
extern short sock_fd;
extern bool is_server;
extern bool is_client;
extern bool is_connected;
extern bool is_ai_mode;
extern bool is_local;

extern char *opposent_ip;
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

extern TeamsColor my_color;

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

typedef struct Capture
{
    Position start;
    Position end;
    TeamsColor team;
} Capture;

typedef struct Conquete
{
    bool is_ok;
    TeamsColor team;
} Conquete;

extern Position diagonal_pos[11];

extern TeamsColor current_team;
extern SelectedPawn is_pawn_selected;
extern BoardCell game_board[BOARD_ROWS][BOARD_COLS];

extern Position red_team_pices_pos[10];
extern Position blue_team_pices_pos[10];
extern TeamsColor ai_team;

#endif