
#include "GameRecorder.h"
#include <iostream>
#include <fstream>

using namespace std;

GameRecorder::GameRecorder()
{
}

void GameRecorder::addMove(const string& move, int evaluation)
{
    moves.push_back(move);
    evaluations.push_back(evaluation);
}

int GameRecorder::getMoveCount() const
{
    return moves.size();
}

void GameRecorder::printGame()
{
    cout << "\n========== GAME RECORD ==========" << endl;

    for (int i = 0; i < moves.size(); i++)
    {
        cout << i + 1
             << ". "
             << moves[i]
             << "  Evaluation: "
             << evaluations[i]
             << endl;
    }

    cout << "Total moves: "
         << moves.size()
         << endl;

    cout << "=================================" << endl;
}

void GameRecorder::saveToFile(const string& filename)
{
    ofstream file(filename.c_str());

    if (!file)
    {
        cout << "Error: Could not save game." << endl;
        return;
    }

    file << "[Game \"C++ Chess Engine\"]\n";
    file << "[White \"Human\"]\n";
    file << "[Black \"AI\"]\n\n";

    for (int i = 0; i < moves.size(); i++)
    {
        if (i % 2 == 0)
        {
            file << (i / 2) + 1 << ". ";
        }

        file << moves[i] << " ";

        if (i % 2 == 1)
        {
            file << "\n";
        }
    }

    file << "\n";

    file.close();

    cout << "Game saved to "
         << filename
         << endl;
}
