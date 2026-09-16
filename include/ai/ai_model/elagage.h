#ifndef KLOSOWO_ELAGAGE_H
#define KLOSOWO_ELAGAGE_H

#include "ai/ai.h"

extern AiTreeNode *AiTreeBase;

int ai_eval();

int calculate_heuristic();

int min_max( int depth, int heuristic, int alpha, int beta );

#endif // KLOSOWO_ELAGAGE_H