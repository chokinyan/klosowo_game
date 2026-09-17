#include "ai/ai_model/elagage.h"
#include "game/player/capture.h"
#include "game/player/movement.h"
#include <stdio.h>
#include <stdlib.h>

AiTreeNode *AiTreeBase = NULL;

void init_min_max()
{
    // Initialize the min-max algorithm
    AiTreeBase = (AiTreeNode *)malloc( sizeof( AiTreeNode ) );
    AiTreeBase->children = NULL;
    AiTreeBase->child_count = 0;
    memcpy( AiTreeBase->ai_team_pos, ( AiTreeBase->team == RED ) ? red_team_pices_pos : blue_team_pices_pos,
            sizeof( AiTreeBase->ai_team_pos ) );
    memcpy( AiTreeBase->enemy_team_pos, ( ai_team == RED ) ? blue_team_pices_pos : red_team_pices_pos,
            sizeof( AiTreeBase->enemy_team_pos ) );
    AiTreeBase->team = ai_team;
    memcpy( AiTreeBase->board_state, game_board, sizeof( BoardCell ) * BOARD_ROWS * BOARD_COLS );

    generate_child( AiTreeBase );
    min_max( AI_DEPTH, 0, AI_MIN_INF, AI_MAX_INF, AiTreeBase );
}

static bool is_path_clear_on_board( Position start, Position end, BoardCell board[BOARD_ROWS][BOARD_COLS] )
{
    if ( start.x < 0 || start.x >= BOARD_ROWS || start.y < 0 || start.y >= BOARD_COLS )
        return false;
    if ( end.x < 0 || end.x >= BOARD_ROWS || end.y < 0 || end.y >= BOARD_COLS )
        return false;

    bool same_row = ( start.x == end.x );
    bool same_col = ( start.y == end.y );
    if ( same_row == same_col ) // ni l'un ni l'autre (ou les deux, meme case) -> invalide
        return false;

    if ( board[end.x][end.y].pawn != NULL_PAWN || board[end.x][end.y].type == BARRER )
        return false;

    if ( same_row )
    {
        int step = ( end.y > start.y ) ? 1 : -1;
        for ( int y = start.y + step; y != end.y; y += step )
            if ( board[start.x][y].pawn != NULL_PAWN || board[start.x][y].type == BARRER )
                return false;
    }
    else
    {
        int step = ( end.x > start.x ) ? 1 : -1;
        for ( int x = start.x + step; x != end.x; x += step )
            if ( board[x][start.y].pawn != NULL_PAWN || board[x][start.y].type == BARRER )
                return false;
    }
    return true;
}

int calculate_heuristic( AiTreeNode *node )
{
    BoardCell( *board )[BOARD_COLS] = node->board_state;

    CellsType my_control_type = ( ai_team == RED ) ? RED_TEAM : BLUE_TEAM;
    CellsType enemy_control_type = ( ai_team == RED ) ? BLUE_TEAM : RED_TEAM;

    int my_control = 0, enemy_control = 0;
    int my_soldiers = 0, enemy_soldiers = 0;
    Position my_king = { -1, -1 };

    for ( int x = 0; x < BOARD_ROWS; x++ )
    {
        for ( int y = 0; y < BOARD_COLS; y++ )
        {
            CellsType type = board[x][y].type;
            if ( type != RED_CAMP && type != BLUE_CAMP ) // hors cites, jamais controlables
            {
                if ( type == my_control_type )
                    my_control++;
                else if ( type == enemy_control_type )
                    enemy_control++;
            }

            PawnType pawn = board[x][y].pawn;
            if ( ai_team == RED )
            {
                if ( pawn == RED_SOLDIER )
                    my_soldiers++;
                else if ( pawn == RED_KING )
                    my_king = ( Position ){ x, y };
                else if ( pawn == BLUE_SOLDIER )
                    enemy_soldiers++;
            }
            else
            {
                if ( pawn == BLUE_SOLDIER )
                    my_soldiers++;
                else if ( pawn == BLUE_KING )
                    my_king = ( Position ){ x, y };
                else if ( pawn == RED_SOLDIER )
                    enemy_soldiers++;
            }
        }
    }

    int score = 0;
    score += ( my_control - enemy_control ) * 2;
    score += ( my_soldiers - enemy_soldiers ) * 5;

    // Bonus : plus mon roi est proche de la cite adverse, mieux c'est
    // (conquete = victoire immediate)
    Position enemy_city = ( ai_team == RED ) ? ( Position ){ 0, 0 } : ( Position ){ BOARD_ROWS - 1, BOARD_COLS - 1 };
    if ( my_king.x != -1 )
    {
        int dist = abs( my_king.x - enemy_city.x ) + abs( my_king.y - enemy_city.y );
        score += ( 20 - dist );
    }

    return score;
}

int min_max( int depth, int heuristic, int alpha, int beta, AiTreeNode *node )
{
    if ( depth == 0 )
        return calculate_heuristic( node );

    if ( node->child_count == 0 )
        generate_child( node );

    if ( node->team != ai_team )
    {
        int m = AI_MAX_INF;
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
        int m = AI_MIN_INF;
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
    node->child_count = 0;
    node->children = NULL;

    bool node_is_ai = ( node->team == ai_team );
    Position *mover_pos = node_is_ai ? node->ai_team_pos : node->enemy_team_pos;
    Position *opponent_pos = node_is_ai ? node->enemy_team_pos : node->ai_team_pos;

    for ( int i = 0; i < AI_MAX_PIECES; i++ )
    {
        Position start = mover_pos[i];
        if ( start.x == -1 && start.y == -1 )
            continue;

        for ( int x = 0; x < BOARD_ROWS; x++ )
        {
            for ( int y = 0; y < BOARD_COLS; y++ )
            {
                Position end = { .x = x, .y = y };

                if ( !is_path_clear_on_board( start, end, node->board_state ) )
                    continue;

                node->children =
                    (AiTreeNode *)realloc( node->children, sizeof( AiTreeNode ) * ( node->child_count + 1 ) );
                AiTreeNode *child = &node->children[node->child_count];

                child->team = ( node->team == RED ) ? BLUE : RED;
                child->children = NULL;
                child->child_count = 0;
                child->start_x = start.x;
                child->start_y = start.y;
                child->end_x = end.x;
                child->end_y = end.y;

                memcpy( child->board_state, node->board_state, sizeof( child->board_state ) );
                memcpy( child->ai_team_pos, node->ai_team_pos, sizeof( child->ai_team_pos ) );
                memcpy( child->enemy_team_pos, node->enemy_team_pos, sizeof( child->enemy_team_pos ) );

                // Deplace la piece dans la copie de l'enfant
                Position *child_mover_pos = node_is_ai ? child->ai_team_pos : child->enemy_team_pos;
                child_mover_pos[i] = end;

                child->board_state[end.x][end.y] = child->board_state[start.x][start.y];
                child->board_state[start.x][start.y] = ( BoardCell ){ 0 };

                // Applique une eventuelle capture (Linca/Seultou) sur la copie de l'enfant
                Position victim[4] = { { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } };
                check_linca( end, node->team, victim, game_board );
                for ( short v = 0; v < 4; v++ )
                {
                    if ( victim[v].x != -1 )
                    {
                        child->board_state[victim[v].x][victim[v].y] = ( BoardCell ){ 0 };

                        Position *child_opponent_pos = node_is_ai ? child->enemy_team_pos : child->ai_team_pos;

                        for ( int k = 0; k < AI_MAX_PIECES; k++ )
                        {
                            if ( child_opponent_pos[k].x == victim[v].x && child_opponent_pos[k].y == victim[v].y )
                            {
                                child_opponent_pos[k] = ( Position ){ -1, -1 };
                                break;
                            }
                        }
                    }
                }

                node->child_count++;
            }
        }
    }
}

bool minimax_ai_move()
{
    AiTreeNode root;
    root.team = ai_team;
    memcpy( root.board_state, game_board, sizeof( root.board_state ) );
    memcpy( root.ai_team_pos, ( ai_team == RED ) ? red_team_pices_pos : blue_team_pices_pos,
            sizeof( root.ai_team_pos ) );
    memcpy( root.enemy_team_pos, ( ai_team == RED ) ? blue_team_pices_pos : red_team_pices_pos,
            sizeof( root.enemy_team_pos ) );
    root.children = NULL;
    root.child_count = 0;

    generate_child( &root );

    if ( root.child_count == 0 )
        return false; // aucun coup possible

    int best_index = 0;
    int best_value = AI_MIN_INF;

    for ( int i = 0; i < root.child_count; i++ )
    {
        int value = min_max( AI_DEPTH - 1, 0, AI_MIN_INF, AI_MAX_INF, &root.children[i] );
        if ( value > best_value )
        {
            best_value = value;
            best_index = i;
        }
    }

    Position start = { root.children[best_index].start_x, root.children[best_index].start_y };
    Position end = { root.children[best_index].end_x, root.children[best_index].end_y };

    bool result = moove_player( start, end, ai_team, game_board ); // le VRAI coup, sur le VRAI plateau

    free( root.children );
    return result;
}