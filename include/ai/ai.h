#ifndef KLOSNOWO_AI_H
#define KLOSNOWO_AI_H

#include "glib.h"
#include "types/types.h"
#include <stdbool.h>

enum
{
    AI_DEPTH = 3,
    AI_MAX_MOVES = 50,
    AI_MAX_PIECES = 10,
    AI_MAX_SCORE = 1000
};

extern Position ai_piece_pos[AI_MAX_PIECES];

gboolean ai_make_move();

bool ai_place_barrer();

#endif // KLOSNOWO_AI_H
