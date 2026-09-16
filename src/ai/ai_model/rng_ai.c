#include "ai/ai_model/rng_ai.h"
#include "ai/ai.h"
#include "game/player/movement.h"
#include "log/log.h"
#include <string.h>

bool rng_ai()
{
    memset( ai_piece_pos, 0, sizeof( ai_piece_pos ) );

    memcpy( ai_piece_pos, ai_team == RED ? red_team_pices_pos : blue_team_pices_pos, sizeof( ai_piece_pos ) );

    log_debug( "Ai play" );

    for ( short j = 0; j < 400; j++ )
    {
        int x = rand() % AI_MAX_PIECES;

        if ( ai_piece_pos[x].x == -1 && ai_piece_pos[x].y == -1 )
            continue;

        Position piece = ai_piece_pos[x];

        for ( char i = 0; i < 50; i++ )
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
