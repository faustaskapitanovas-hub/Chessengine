#include <optional>
#include "ChessGUI.h"

#include <iostream>

using namespace std;

ChessGUI::ChessGUI(Board& board,
                   Engine& engine,
                   Evaluator& evaluator)
    : board(board),
      engine(engine),
      evaluator(evaluator),
      window(sf::VideoMode({800, 800}), "C++ Chess Engine"),
      selectedRow(-1),
      selectedCol(-1),
      pieceSelected(false)
{
}

void ChessGUI::run()
{
    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (const auto* mouseButton =
                    event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButton->button ==
                    sf::Mouse::Button::Left)
                {
                    handleMouseClick(
                        mouseButton->position.x,
                        mouseButton->position.y
                    );
                }
            }
        }

        window.clear();

        drawBoard();
        drawPieces();

        window.display();
    }
}


void ChessGUI::drawBoard()
{
    const float squareSize = 100.0f;

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            sf::RectangleShape square(
                sf::Vector2f(squareSize, squareSize)
            );

            square.setPosition(
                {col * squareSize,
                 row * squareSize}
            );

            if ((row + col) % 2 == 0)
            {
                square.setFillColor(
                    sf::Color(240, 217, 181)
                );
            }
            else
            {
                square.setFillColor(
                    sf::Color(181, 136, 99)
                );
            }

            window.draw(square);
        }
    }
}



void ChessGUI::drawPieces()
{
    const float squareSize = 100.0f;

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            char piece = board.getPiece(row, col);

            if (piece == '.')
            {
                continue;
            }

            sf::CircleShape pieceShape(30.0f);

            pieceShape.setPosition(
                {col * squareSize + 20.0f,
                 row * squareSize + 20.0f}
            );

            if (piece >= 'A' && piece <= 'Z')
            {
                pieceShape.setFillColor(
                    sf::Color::White
                );

                pieceShape.setOutlineColor(
                    sf::Color::Black
                );
            }
            else
            {
                pieceShape.setFillColor(
                    sf::Color::Black
                );

                pieceShape.setOutlineColor(
                    sf::Color::White
                );
            }

            pieceShape.setOutlineThickness(3.0f);

            window.draw(pieceShape);
        }
    }
}


void ChessGUI::handleMouseClick(int x, int y)
{
    const int col = x / 100;
    const int row = y / 100;

    if (row < 0 || row >= 8 ||
        col < 0 || col >= 8)
    {
        return;
    }

    makePlayerMove(row, col);
}



void ChessGUI::makePlayerMove(int row, int col)
{
    char piece = board.getPiece(row, col);

    // --------------------------------
    // FIRST CLICK
    // --------------------------------

    if (!pieceSelected)
    {
        // Only allow White pieces
        if (piece >= 'A' && piece <= 'Z')
        {
            selectedRow = row;
            selectedCol = col;

            pieceSelected = true;

            cout << "Selected piece at "
                 << selectedRow << ", "
                 << selectedCol << endl;
        }

        return;
    }

    // --------------------------------
    // SECOND CLICK
    // --------------------------------

    string move;

    char fromFile =
        'a' + selectedCol;

    char fromRank =
        '8' - selectedRow;

    char toFile =
        'a' + col;

    char toRank =
        '8' - row;

    move += fromFile;
    move += fromRank;
    move += toFile;
    move += toRank;

    cout << "Trying move: "
         << move << endl;

    board.makeMove(move);

    pieceSelected = false;

    selectedRow = -1;
    selectedCol = -1;

    // --------------------------------
    // AI TURN
    // --------------------------------

    if (!board.isWhiteTurn())
    {
        makeAIMove();
    }
}


void ChessGUI::makeAIMove()
{
    cout << "AI thinking..." << endl;

    string aiMove =
        engine.getBestMoveAlphaBeta(board, 5);

    if (aiMove.empty())
    {
        cout << "Game over." << endl;
        return;
    }

    cout << "AI plays: "
         << aiMove
         << endl;

    board.makeMove(aiMove);

    cout << "Evaluation: "
         << evaluator.evaluate(board)
         << endl;
}
