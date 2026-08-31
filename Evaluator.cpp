#include "Evaluator.h"

using namespace std;

Evaluator::Evaluator()
{
}

int Evaluator::getPieceValue(char piece)
{
    switch (piece)
    {
        case 'P':
        case 'p':
            return 100;

        case 'N':
        case 'n':
            return 320;

        case 'B':
        case 'b':
            return 330;

        case 'R':
        case 'r':
            return 500;

        case 'Q':
        case 'q':
            return 900;

        case 'K':
        case 'k':
            return 0;

        default:
            return 0;
    }
}

int Evaluator::evaluate(Board& board)
{
    // --------------------------------
    // CHECKMATE
    // --------------------------------

    if (board.isCheckmate(true))
    {
        // White is checkmated
        return -100000;
    }

    if (board.isCheckmate(false))
    {
        // Black is checkmated
        return 100000;
    }

    int score = 0;

    // --------------------------------
    // LOOK AT EVERY SQUARE
    // --------------------------------

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            char piece = board.getPiece(row, col);

            if (piece == '.')
            {
                continue;
            }

            int value = getPieceValue(piece);

            // =================================
            // WHITE PIECES
            // =================================

            if (piece >= 'A' && piece <= 'Z')
            {
                score += value;

                // --------------------------------
                // KNIGHT DEVELOPMENT
                // --------------------------------

                if (piece == 'N')
                {
                    // White's original knights start
                    // on b1 and g1.
                    //
                    // If they are no longer there,
                    // reward development.

                    if (!((row == 7 && col == 1) ||
                          (row == 7 && col == 6)))
                    {
                        score += 30;
                    }
                }

                // --------------------------------
                // PAWN ADVANCEMENT
                // --------------------------------

                if (piece == 'P')
                {
                    // White starts on row 6.
                    //
                    // Every row closer to row 0
                    // means the pawn advanced.

                    int advancement = 6 - row;

                    score += advancement * 5;
                }
            }

            // =================================
            // BLACK PIECES
            // =================================

            else if (piece >= 'a' && piece <= 'z')
            {
                score -= value;

                // --------------------------------
                // KNIGHT DEVELOPMENT
                // --------------------------------

                if (piece == 'n')
                {
                    // Black's original knights start
                    // on b8 and g8.

                    if (!((row == 0 && col == 1) ||
                          (row == 0 && col == 6)))
                    {
                        score -= 30;
                    }
                }

                // --------------------------------
                // PAWN ADVANCEMENT
                // --------------------------------

                if (piece == 'p')
                {
                    // Black starts on row 1.
                    //
                    // Every row closer to row 7
                    // means the pawn advanced.

                    int advancement = row - 1;

                    score -= advancement * 5;
                }
            }
        }
    }

    return score;
}
