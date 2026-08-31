#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include "Board.h"
#include "Evaluator.h"

class Engine
{
public:
    Engine();

    long long perft(Board& board, int depth);

    std::string getBestMove(Board& board, int depth);
    std::string getBestMoveAlphaBeta(Board& board, int depth);
    long long getMinimaxNodes() const;
long long getAlphaBetaNodes() const;

private:
    int minimax(Board& board, int depth, bool maximizingPlayer);

int alphaBeta(Board& board,
              int depth,
              int alpha,
              int beta,
              bool maximizingPlayer);

    Evaluator evaluator;

    long long minimaxNodes;
long long alphaBetaNodes;
};

#endif
