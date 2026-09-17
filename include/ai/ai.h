#ifndef KLOSNOWO_AI_H
#define KLOSNOWO_AI_H

#include "glib.h"
#include "types/types.h"
#include <stdbool.h>

enum
{
    AI_DEPTH = 3,
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
    short start_x;
    short start_y;
    short end_x;
    short end_y;
    bool is_wining;
} AiTreeNode;

extern Position ai_piece_pos[AI_MAX_PIECES];

gboolean ai_make_move();

bool ai_place_barrer();

#endif // KLOSNOWO_AI_H
