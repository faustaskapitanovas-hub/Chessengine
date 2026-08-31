#include "Engine.h"

using namespace std;

Engine::Engine()
{
    minimaxNodes = 0;
    alphaBetaNodes = 0;
}
long long Engine::perft(Board& board, int depth)
{
    // We reached the final depth.
    // This position counts as one node.
    if (depth == 0)
    {
        return 1;
    }

    vector<string> legalMoves = board.getLegalMoves();

    long long nodes = 0;

    for (const string& move : legalMoves)
    {
        // Save the entire position
        PositionState state = board.savePosition();

        // Make the move
        board.makeMove(move);

        // Recursively count positions
        nodes += perft(board, depth - 1);

        // Restore the exact position
        board.restorePosition(state);
    }

    return nodes;
}

int Engine::minimax(Board& board, int depth, bool maximizingPlayer)
{
    minimaxNodes++;
    // Stop searching
    if (depth == 0)
    {
        return evaluator.evaluate(board);
    }

    std::vector<std::string> legalMoves = board.getLegalMoves();

    // No legal moves
    if (legalMoves.empty())
    {
        return evaluator.evaluate(board);
    }

    if (maximizingPlayer)
    {
        int bestScore = -1000000;

        for (const std::string& move : legalMoves)
        {
            PositionState state = board.savePosition();

            board.makeMove(move);

            int score = minimax(
                board,
                depth - 1,
                false
            );

            board.restorePosition(state);

            if (score > bestScore)
            {
                bestScore = score;
            }
        }

        return bestScore;
    }
    else
    {
        int bestScore = 1000000;

        for (const std::string& move : legalMoves)
        {
            PositionState state = board.savePosition();

            board.makeMove(move);

            int score = minimax(
                board,
                depth - 1,
                true
            );

            board.restorePosition(state);

            if (score < bestScore)
            {
                bestScore = score;
            }
        }

        return bestScore;
    }
}

std::string Engine::getBestMove(Board& board, int depth)
{
    std::vector<std::string> legalMoves = board.getLegalMoves();

    if (legalMoves.empty())
    {
        return "";
    }

    bool maximizingPlayer = board.isWhiteTurn();

    std::string bestMove = legalMoves[0];

    int bestScore;

    if (maximizingPlayer)
    {
        bestScore = -1000000;
    }
    else
    {
        bestScore = 1000000;
    }

    for (const std::string& move : legalMoves)
    {
        PositionState state = board.savePosition();

        board.makeMove(move);

        int score = minimax(
            board,
            depth - 1,
            !maximizingPlayer
        );

        board.restorePosition(state);

        if (maximizingPlayer)
        {
            if (score > bestScore)
            {
                bestScore = score;
                bestMove = move;
            }
        }
        else
        {
            if (score < bestScore)
            {
                bestScore = score;
                bestMove = move;
            }
        }
    }

    return bestMove;
}


int Engine::alphaBeta(Board& board,
                      int depth,
                      int alpha,
                      int beta,
                      bool maximizingPlayer)
{
    alphaBetaNodes++;

    if (depth == 0)
    {
        return evaluator.evaluate(board);
    }

    vector<string> legalMoves = board.getLegalMoves();

    if (legalMoves.empty())
    {
        return evaluator.evaluate(board);
    }

    if (maximizingPlayer)
    {
        int bestScore = -1000000;

        for (const string& move : legalMoves)
        {
            PositionState state = board.savePosition();

            board.makeMove(move);

            int score = alphaBeta(
                board,
                depth - 1,
                alpha,
                beta,
                false
            );

            board.restorePosition(state);

            if (score > bestScore)
            {
                bestScore = score;
            }

            if (bestScore > alpha)
            {
                alpha = bestScore;
            }

            // Beta cutoff
            if (beta <= alpha)
            {
                break;
            }
        }

        return bestScore;
    }
    else
    {
        int bestScore = 1000000;

        for (const string& move : legalMoves)
        {
            PositionState state = board.savePosition();

            board.makeMove(move);

            int score = alphaBeta(
                board,
                depth - 1,
                alpha,
                beta,
                true
            );

            board.restorePosition(state);

            if (score < bestScore)
            {
                bestScore = score;
            }

            if (bestScore < beta)
            {
                beta = bestScore;
            }

            // Alpha cutoff
            if (beta <= alpha)
            {
                break;
            }
        }

        return bestScore;
    }
}

string Engine::getBestMoveAlphaBeta(Board& board, int depth)
{
    vector<string> legalMoves = board.getLegalMoves();

    if (legalMoves.empty())
    {
        return "";
    }

    alphaBetaNodes = 0;

    bool maximizingPlayer = board.isWhiteTurn();

    string bestMove = legalMoves[0];

    int bestScore;

    if (maximizingPlayer)
    {
        bestScore = -1000000;
    }
    else
    {
        bestScore = 1000000;
    }

    for (const string& move : legalMoves)
    {
        PositionState state = board.savePosition();

        board.makeMove(move);

        int score = alphaBeta(
            board,
            depth - 1,
            -1000000,
            1000000,
            !maximizingPlayer
        );

        board.restorePosition(state);

        if (maximizingPlayer)
        {
            if (score > bestScore)
            {
                bestScore = score;
                bestMove = move;
            }
        }
        else
        {
            if (score < bestScore)
            {
                bestScore = score;
                bestMove = move;
            }
        }
    }

    return bestMove;
}

long long Engine::getMinimaxNodes() const
{
    return minimaxNodes;
}

long long Engine::getAlphaBetaNodes() const
{
    return alphaBetaNodes;
}

