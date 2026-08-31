#ifndef CHESSGUI_H
#define CHESSGUI_H

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Engine.h"
#include "Evaluator.h"

class ChessGUI
{
public:
    ChessGUI(Board& board, Engine& engine, Evaluator& evaluator);

    void run();

private:
    Board& board;
    Engine& engine;
    Evaluator& evaluator;

    sf::RenderWindow window;

    int selectedRow;
    int selectedCol;

    bool pieceSelected;

    void drawBoard();
    void drawPieces();

    void handleMouseClick(int x, int y);

    void makePlayerMove(int row, int col);
    void makeAIMove();
};

#endif
