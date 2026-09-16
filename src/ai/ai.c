#include "ai/ai.h"

#include "ai/ai_model/rng_ai.h"
#include "game/player/movement.h"
#include <stdlib.h>

Position ai_piece_pos[AI_MAX_PIECES];

gboolean ai_make_move() { return rng_ai(); }

bool ai_place_barrer()
{
    for ( short i = 0; i < 400; i++ )
    {
        Position pos = { .x = rand() % BOARD_ROWS, .y = rand() % BOARD_COLS };

        if ( place_barrer( pos ) )
            return true;
    }

    return false;
}