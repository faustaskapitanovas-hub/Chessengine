#ifndef GAMERECORDER_H
#define GAMERECORDER_H

#include <string>
#include <vector>

class GameRecorder
{
public:
    GameRecorder();

    void addMove(const std::string& move, int evaluation);

    void printGame();

    void saveToFile(const std::string& filename);

    int getMoveCount() const;

private:
    std::vector<std::string> moves;
    std::vector<int> evaluations;
};

#endif
