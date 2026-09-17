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
            if ( ( is_server || is_client ) && is_connected )
            {
                Position start = ai_team == RED ? ( Position ){ .x = 0, .y = 0 } : ( Position ){ .x = 6, .y = 10 };
                int result = network_send_move( ( Position ){ .x = start.y, .y = start.x },
                                                ( Position ){ .x = pos.y, .y = pos.x } );
                if ( result == 0 )
                    log_error( "Erreur lors de l'envoi du message du mur par l'IA." );
            }

            log_debug( "AI barrier placed at (%d,%d)", pos.x, pos.y );
            return true;
        }
        return true;
    }

    return false;
}