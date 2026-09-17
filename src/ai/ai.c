#include "ai/ai.h"
#include "ai/ai_model/elagage.h"

#include "game/player/movement.h"
#include "log/log.h"
#include "network/client.h"
#include <stdlib.h>

Position ai_piece_pos[AI_MAX_PIECES];

gboolean ai_make_move() { return minimax_ai_move(); }

bool ai_place_barrer()
{
    for ( short i = 0; i < 400; i++ )
    {
        Position pos = { .x = rand() % BOARD_ROWS, .y = rand() % BOARD_COLS };

        if ( place_barrer( pos ) )
        {
            if ( is_server || is_client )
            {
                Position sentinel =
                    ( ai_team == RED ) ? ( Position ){ .x = 10, .y = 6 } : ( Position ){ .x = 0, .y = 0 };
                network_send_move( sentinel,
                                   ( Position ){ .x = pos.y, .y = pos.x } ); // même swap x/y que le code humain
            }
            return true;
        }
    }
    return false;
}