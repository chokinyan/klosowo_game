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

typedef struct TreeNode
{
    Position start;
    Position end;
    int score;
    struct TreeNode *children;
    int child_count;
} TreeNode;

extern Position ai_piece_pos[AI_MAX_PIECES];

gboolean ai_make_move();

bool ai_place_barrer();

#endif // KLOSNOWO_AI_H
