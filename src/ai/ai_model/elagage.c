#include "ai/ai_model/elagage.h"

AiTreeNode *AiTreeBase = NULL;

void init_min_max()
{
    // Initialize the min-max algorithm
    AiTreeBase = (AiTreeNode *)malloc( sizeof( AiTreeNode ) );
    AiTreeBase->children = NULL;
    AiTreeBase->child_count = 0;
    AiTreeBase->is_wining = false;
    AiTreeBase->team = ai_team;
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

int min_max( int depth, int heuristic, int alpha, int beta, AiTreeNode *node )
{
    if ( depth == 0 )
        return calculate_heuristic();

    if ( current_team != ai_team )
    {
        int m = ai_eval();
        for ( int i = 0; i < node->child_count; i++ )
        {
            int eval = min_max( depth - 1, heuristic, alpha, beta, node->children + i );
            if ( eval < m )
                m = eval;
            else if ( m <= alpha )
                return m;

            beta = ( beta < m ) ? beta : m;
        }
        return m;
    }
    else
    {
        int m = ai_eval();
        for ( int i = 0; i < node->child_count; i++ )
        {
            int eval = min_max( depth - 1, heuristic, alpha, beta, node->children + i );
            if ( eval > m )
                m = eval;
            else if ( m >= beta )
                return m;

            alpha = ( alpha > m ) ? alpha : m;
        }
        return m;
    }

    return 0;
}

void generate_child( AiTreeNode *node )
{
    Position current_team_pieces[AI_MAX_PIECES];
    memcpy( current_team_pieces, ( node->team == RED ) ? red_team_pices_pos : blue_team_pices_pos,
            sizeof( current_team_pieces ) );

    memset( node->piece_positions, 0, sizeof( node->piece_positions ) );

    memset( node->piece_positions, 0, sizeof( node->piece_positions ) );

    for ( short i = 0; i < AI_MAX_PIECES; i++ )
    {
        if ( current_team_pieces[i].x == -1 && current_team_pieces[i].y == -1 )
            continue;

        Position piece_pos = current_team_pieces[i];
        node->piece_positions[i].max_x = BOARD_ROWS - piece_pos.x - 1;
        node->piece_positions[i].max_y = BOARD_COLS - piece_pos.y - 1;
        node->piece_positions[i].min_x = piece_pos.x - 1 - BOARD_ROWS;
        node->piece_positions[i].min_y = piece_pos.y - 1 - BOARD_COLS;

        for ( short j = 0; j < AI_MAX_PIECES; j++ )
        {
            if ( current_team_pieces[j].x == -1 && current_team_pieces[j].y == -1 )
                continue;

            if ( current_team_pieces[j].x == piece_pos.x && current_team_pieces[j].y == piece_pos.y )
                continue;

            Position other_piece_pos = current_team_pieces[j];

            if ( other_piece_pos.x < node->piece_positions[i].min_x )
                node->piece_positions[i].min_x = other_piece_pos.x;
            if ( other_piece_pos.y < node->piece_positions[i].min_y )
                node->piece_positions[i].min_y = other_piece_pos.y;
            if ( other_piece_pos.x > node->piece_positions[i].max_x )
                node->piece_positions[i].max_x = other_piece_pos.x;
            if ( other_piece_pos.y > node->piece_positions[i].max_y )
                node->piece_positions[i].max_y = other_piece_pos.y;

            Position enemy_piece_pos = current_team_pieces[j];
            if ( enemy_piece_pos.x < node->piece_positions[i].min_x )
                node->piece_positions[i].min_x = enemy_piece_pos.x;
            if ( enemy_piece_pos.y < node->piece_positions[i].min_y )
                node->piece_positions[i].min_y = enemy_piece_pos.y;
            if ( enemy_piece_pos.x > node->piece_positions[i].max_x )
                node->piece_positions[i].max_x = enemy_piece_pos.x;
            if ( enemy_piece_pos.y > node->piece_positions[i].max_y )
                node->piece_positions[i].max_y = enemy_piece_pos.y;
        }
    }
}
