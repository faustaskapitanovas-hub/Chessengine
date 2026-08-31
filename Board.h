#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>


struct PositionState
{
    char board[8][8];

    bool whiteTurn;

    int lastFromRow;
    int lastFromCol;
    int lastToRow;
    int lastToCol;

    bool whiteKingMoved;
    bool blackKingMoved;

    bool whiteKingsideRookMoved;
    bool whiteQueensideRookMoved;

    bool blackKingsideRookMoved;
    bool blackQueensideRookMoved;
};

class Board
{
public:
    Board();

    void printBoard();
    void makeMove(std::string move);
    std::vector<std::string> getLegalMoves();
    void printLegalMoves();
    long long perft(int depth);
bool isCheckmate(bool white);
bool isStalemate(bool white);
void checkGameStatus();
char getPiece(int row, int col) const;
bool isWhiteTurn() const;


private:
    friend class Engine;
    char board[8][8];
    bool whiteTurn;


    int lastFromRow;
    int lastFromCol;
    int lastToRow;
    int lastToCol;

    bool isWhitePiece(char piece);
    bool isBlackPiece(char piece);

    bool isSquareAttacked(int row, int col, bool byWhite);
    bool isKingInCheck(bool white);
    bool isMoveLegal(const std::string& move);




    void undoMove(int fromRow, int fromCol,
              int toRow, int toCol,
              char capturedPiece);

    void restoreBoard(char savedBoard[8][8]);


    bool whiteKingMoved;
bool blackKingMoved;

bool whiteKingsideRookMoved;
bool whiteQueensideRookMoved;

bool blackKingsideRookMoved;
bool blackQueensideRookMoved;


    PositionState savePosition();
    void restorePosition(const PositionState& state);





};

#endif
