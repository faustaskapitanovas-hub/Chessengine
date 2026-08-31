#include <iostream>
#include <string>
#include <chrono>

#include "Board.h"
#include "Engine.h"
#include "Evaluator.h"
#include "GameRecorder.h"

using namespace std;

int main()
{
    Board board;
    Engine engine;
    Evaluator evaluator;
    GameRecorder recorder;

    cout << "==============================" << endl;
    cout << "       C++ CHESS ENGINE       " << endl;
    cout << "==============================" << endl;

    board.printBoard();

    cout << "\nEvaluation: "
         << evaluator.evaluate(board)
         << endl;

    cout << "\nYou are White." << endl;
    cout << "Enter moves like e2e4." << endl;
    cout << "Type quit to exit." << endl;

    while (true)
    {
        // =========================
        // WHITE - HUMAN
        // =========================

        if (board.isWhiteTurn())
        {
            string move;

            cout << "\nYour move: ";
            cin >> move;

            if (move == "quit")
            {
                cout << "Game ended." << endl;
                break;
            }

            board.makeMove(move);

int evaluation = evaluator.evaluate(board);

recorder.addMove(move, evaluation);
        }

        // =========================
        // BLACK - AI
        // =========================

        else
        {
            cout << "\nAI is thinking..." << endl;

            auto start = chrono::high_resolution_clock::now();

string aiMove =
    engine.getBestMoveAlphaBeta(board, 5);

auto end = chrono::high_resolution_clock::now();

auto duration =
    chrono::duration_cast<chrono::milliseconds>(
        end - start
    );

cout << "AI plays: "
     << aiMove
     << endl;

cout << "Search time: "
     << duration.count()
     << " ms"
     << endl;

            if (aiMove == "")
            {
                cout << "AI has no legal moves." << endl;
                break;
            }


            board.makeMove(aiMove);

int evaluation = evaluator.evaluate(board);

recorder.addMove(aiMove, evaluation);
        }

        // =========================
        // DISPLAY POSITION
        // =========================

        cout << endl;

        board.printBoard();

        cout << "\nEvaluation: "
             << evaluator.evaluate(board)
             << endl;

        // =========================
        // CHECK GAME STATUS
        // =========================

        board.checkGameStatus();

        // =========================
        // SHOW LEGAL MOVES
        // =========================

        board.printLegalMoves();
    }
cout << endl;

recorder.printGame();

recorder.saveToFile("game.pgn");
    return 0;
}
