#include "ai/ai_model/elagage.h"

AiTreeNode *AiTreeBase = NULL;

void init_min_max()
{
    // Initialize the min-max algorithm
    AiTreeBase = (AiTreeNode *)malloc( sizeof( AiTreeNode ) );
    AiTreeBase->children = NULL;
    AiTreeBase->child_count = 0;
    AiTreeBase->score = 0;
    AiTreeBase->team = ai_team;
    AiTreeBase->start = ( Position ){ 0, 0 };
    AiTreeBase->end = ( Position ){ 0, 0 };
    memcpy( AiTreeBase->board_state, game_board, sizeof( BoardCell ) * BOARD_ROWS * BOARD_COLS );
}

int ai_eval()
{
    int score = 0;

    return score;
}

int calculate_heuristic()
{
    int heuristic = 0;

    return heuristic;
}

int min_max( int depth, int heuristic, int alpha, int beta )
{
    if ( depth == 0 )
        return calculate_heuristic();

    if ( current_team != ai_team )
    {
        int M = ai_eval();
        for ( int i = 0; i < AiTreeBase->child_count; i++ )
        {
            int eval = min_max( depth - 1, heuristic, alpha, beta );
            beta = ( eval < beta ) ? eval : beta;
            if ( beta <= alpha )
                break; // Alpha-beta pruning
            beta = ( eval < beta ) ? eval : beta;
        }
        return M;
    }
    else
    {
        int M = ai_eval();
        for ( int i = 0; i < AiTreeBase->child_count; i++ )
        {
            int eval = min_max( depth - 1, heuristic, alpha, beta );
            alpha = ( eval > alpha ) ? eval : alpha;
            if ( beta <= alpha )
                break; // Alpha-beta pruning
            alpha = ( eval > alpha ) ? eval : alpha;
        }
        return M;
    }

    return 0;
}
