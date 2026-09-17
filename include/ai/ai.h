#ifndef KLOSNOWO_AI_H
#define KLOSNOWO_AI_H

#include "glib.h"
#include "types/types.h"
#include <stdbool.h>

enum
{
    AI_DEPTH = 3,
    AI_MAX_PIECES = 10,
    AI_MAX_INF = 1000000000000,
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
    Position start;
    Position end;
    int score;
    TeamsColor team;
    struct AiTreeNode *children;
    int child_count;
    BoardCell board_state[BOARD_ROWS][BOARD_COLS];
    PieceMaxPosAble piece_positions[AI_MAX_PIECES];
} AiTreeNode;

extern Position ai_piece_pos[AI_MAX_PIECES];

gboolean ai_make_move();

bool ai_place_barrer();

#endif // KLOSNOWO_AI_H
