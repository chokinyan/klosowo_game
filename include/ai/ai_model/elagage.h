#ifndef KLOSOWO_ELAGAGE_H
#define KLOSOWO_ELAGAGE_H

#include "ai/ai.h"

extern AiTreeNode *AiTreeBase;

int ai_eval();

int calculate_heuristic( AiTreeNode *node );

int min_max( int depth, int heuristic, int alpha, int beta, AiTreeNode *node );

void generate_child( AiTreeNode *node );

#endif // KLOSOWO_ELAGAGE_H