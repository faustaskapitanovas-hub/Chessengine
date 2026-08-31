#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "Board.h"

class Evaluator
{
public:
    Evaluator();

    int evaluate(Board& board);
private:
    int getPieceValue(char piece);
};

#endif
