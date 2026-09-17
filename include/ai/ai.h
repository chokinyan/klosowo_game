#ifndef KLOSNOWO_AI_H
#define KLOSNOWO_AI_H

#include "glib.h"
#include "types/types.h"
#include <stdbool.h>

enum
{
    AI_DEPTH = 7,
    AI_MAX_PIECES = 10,
    AI_MAX_INF = 10000000,
    AI_MIN_INF = -AI_MAX_INF
};

typedef struct PieceMaxPosAble
{
    char max_x;
    char max_y;
    char min_x;
    char min_y;
} PieceMaxPosAble;

typedef struct AiTreeNode
{
    TeamsColor team;
    struct AiTreeNode *children;
    short child_count;
    BoardCell board_state[BOARD_ROWS][BOARD_COLS];
    PieceMaxPosAble piece_positions[AI_MAX_PIECES];
    Position ai_team_pos[AI_MAX_PIECES];
    Position enemy_team_pos[AI_MAX_PIECES]; // NOUVEAU
    short start_x, start_y, end_x, end_y;
} AiTreeNode;

extern Position ai_piece_pos[AI_MAX_PIECES];

gboolean ai_make_move();

bool ai_place_barrer();

#endif // KLOSNOWO_AI_H
