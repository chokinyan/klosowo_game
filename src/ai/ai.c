#include "ai/ai.h"
#include "game/player/movement.h"
#include <stdlib.h>
#include <string.h>

extern Position ai_piece_pos[AI_MAX_PIECES];

gboolean ai_make_move()
{

    memset( ai_piece_pos, 0, sizeof( ai_piece_pos ) );

    memcpy( ai_piece_pos, ai_team == RED ? red_team_pices_pos : blue_team_pices_pos, sizeof( ai_piece_pos ) );

    for ( short j = 0; j < 400; j++ )
    {
        int x = rand() % AI_MAX_PIECES;

        if ( ai_piece_pos[x].x == -1 && ai_piece_pos[x].y == -1 )
            continue;

        Position piece = ai_piece_pos[x];

        for ( short i = 0; i < AI_MAX_MOVES; i++ )
        {

            Position end = { .x = rand() % BOARD_ROWS, .y = rand() % BOARD_COLS };

            if ( moove_player( piece, end, ai_team ) )
            {
                memcpy( ai_team == RED ? red_team_pices_pos : blue_team_pices_pos, ai_piece_pos,
                        sizeof( ai_piece_pos ) );
                return true;
            }
        }
    }

    return false;
}

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
