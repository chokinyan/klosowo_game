#ifndef KLOSOWO_ELAGAGE_H
#define KLOSOWO_ELAGAGE_H

#include "ai/ai.h"

extern AiTreeNode *AiTreeBase;

int ai_eval();

void init_min_max();

static bool is_path_clear_on_board( Position start, Position end, BoardCell board[BOARD_ROWS][BOARD_COLS] );

int calculate_heuristic( AiTreeNode *node );

int min_max( int depth, int heuristic, int alpha, int beta, AiTreeNode *node );

void generate_child( AiTreeNode *node );

bool minimax_ai_move();

#endif // KLOSOWO_ELAGAGE_H