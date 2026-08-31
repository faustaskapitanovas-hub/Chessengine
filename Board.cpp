#include <iostream>
#include "Board.h"
#include <cstdlib>
#include <cctype>
#include <string>
using namespace std;
///starting board
Board::Board()
{
    whiteTurn = true;

    lastFromRow = -1;
    lastFromCol = -1;
    lastToRow = -1;
    lastToCol = -1;

        // Castling rights
    whiteKingMoved = false;
    blackKingMoved = false;

    whiteKingsideRookMoved = false;
    whiteQueensideRookMoved = false;

    blackKingsideRookMoved = false;
    blackQueensideRookMoved = false;
    char startingBoard[8][8] =
    {
        {'r','n','b','q','k','b','n','r'},
        {'p','p','p','p','p','p','p','p'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'P','P','P','P','P','P','P','P'},
        {'R','N','B','Q','K','B','N','R'}
    };

    for(int row = 0; row < 8; row++)
    {
        for(int col = 0; col < 8; col++)
        {
            board[row][col] = startingBoard[row][col];
        }
    }
}
///print board
void Board::printBoard()
{
    cout << "  a b c d e f g h" << endl;

    for(int row = 0; row < 8; row++)
    {
        cout << 8 - row << " ";

        for(int col = 0; col < 8; col++)
        {
            cout << board[row][col] << " ";
        }

        cout << endl;
    }
}
///move maker
void Board::makeMove(std::string move)
{
    // Save the board before attempting the move
    char savedBoard[8][8];
    bool savedWhiteKingMoved = whiteKingMoved;
bool savedBlackKingMoved = blackKingMoved;

bool savedWhiteKingsideRookMoved = whiteKingsideRookMoved;
bool savedWhiteQueensideRookMoved = whiteQueensideRookMoved;

bool savedBlackKingsideRookMoved = blackKingsideRookMoved;
bool savedBlackQueensideRookMoved = blackQueensideRookMoved;

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            savedBoard[row][col] = board[row][col];
        }
    }

    // Check move length
    if (move.length() != 4 && move.length() != 5)
    {
        std::cout << "Illegal move: Use e2e4 format." << std::endl;
        return;
    }

    // Convert starting square
    int fromCol = move[0] - 'a';
    int fromRow = 8 - (move[1] - '0');

    // Convert destination square
    int toCol = move[2] - 'a';
    int toRow = 8 - (move[3] - '0');

    // Check board boundaries
    if (fromRow < 0 || fromRow > 7 ||
        fromCol < 0 || fromCol > 7 ||
        toRow < 0 || toRow > 7 ||
        toCol < 0 || toCol > 7)
    {
        std::cout << "Illegal move: Square does not exist." << std::endl;
        return;
    }

    char piece = board[fromRow][fromCol];

    // No piece on starting square
    if (piece == '.')
    {
        std::cout << "Illegal move: There is no piece there." << std::endl;
        return;
    }

    // Check whose turn it is
    if (whiteTurn && piece >= 'a' && piece <= 'z')
    {
        std::cout << "Illegal move: It is White's turn." << std::endl;
        return;
    }

    if (!whiteTurn && piece >= 'A' && piece <= 'Z')
    {
        std::cout << "Illegal move: It is Black's turn." << std::endl;
        return;
    }


    if (piece == 'P' || piece == 'p')
    {
        // --------------------------------
        // WHITE PAWN
        // --------------------------------

        if (piece == 'P')
        {
            int direction = -1;

            // NORMAL ONE-SQUARE MOVE
            if (toCol == fromCol &&
                toRow == fromRow + direction &&
                board[toRow][toCol] == '.')
            {
                board[toRow][toCol] = piece;
                board[fromRow][fromCol] = '.';
            }

            // FIRST TWO-SQUARE MOVE
            else if (toCol == fromCol &&
                     fromRow == 6 &&
                     toRow == 4 &&
                     board[5][fromCol] == '.' &&
                     board[4][fromCol] == '.')
            {
                board[toRow][toCol] = piece;
                board[fromRow][fromCol] = '.';
            }

            // NORMAL CAPTURE
            else if (abs(toCol - fromCol) == 1 &&
                     toRow == fromRow + direction &&
                     board[toRow][toCol] >= 'a' &&
                     board[toRow][toCol] <= 'z')
            {
                board[toRow][toCol] = piece;
                board[fromRow][fromCol] = '.';
            }

            // EN PASSANT
            else if (abs(toCol - fromCol) == 1 &&
                     toRow == fromRow + direction &&
                     board[toRow][toCol] == '.' &&
                     lastFromRow == 1 &&
                     lastToRow == 3 &&
                     lastFromCol == toCol &&
                     board[lastToRow][lastToCol] == 'p')
            {
                board[toRow][toCol] = piece;
                board[fromRow][fromCol] = '.';
                board[lastToRow][lastToCol] = '.';
            }

            else
            {
                std::cout << "Illegal pawn move." << std::endl;
                return;
            }
        }

        // --------------------------------
        // BLACK PAWN
        // --------------------------------

        else
        {
            int direction = 1;

            // NORMAL ONE-SQUARE MOVE
            if (toCol == fromCol &&
                toRow == fromRow + direction &&
                board[toRow][toCol] == '.')
            {
                board[toRow][toCol] = piece;
                board[fromRow][fromCol] = '.';
            }

            // FIRST TWO-SQUARE MOVE
            else if (toCol == fromCol &&
                     fromRow == 1 &&
                     toRow == 3 &&
                     board[2][fromCol] == '.' &&
                     board[3][fromCol] == '.')
            {
                board[toRow][toCol] = piece;
                board[fromRow][fromCol] = '.';
            }

            // NORMAL CAPTURE
            else if (abs(toCol - fromCol) == 1 &&
                     toRow == fromRow + direction &&
                     board[toRow][toCol] >= 'A' &&
                     board[toRow][toCol] <= 'Z')
            {
                board[toRow][toCol] = piece;
                board[fromRow][fromCol] = '.';
            }

            // EN PASSANT
            else if (abs(toCol - fromCol) == 1 &&
                     toRow == fromRow + direction &&
                     board[toRow][toCol] == '.' &&
                     lastFromRow == 6 &&
                     lastToRow == 4 &&
                     lastFromCol == toCol &&
                     board[lastToRow][lastToCol] == 'P')
            {
                board[toRow][toCol] = piece;
                board[fromRow][fromCol] = '.';
                board[lastToRow][lastToCol] = '.';
            }

            else
            {
                std::cout << "Illegal pawn move." << std::endl;
                return;
            }
        }

        // --------------------------------
        // PROMOTION
        // --------------------------------

        if (piece == 'P' && toRow == 0)
        {
            if (move.length() != 5)
            {
                std::cout << "Promotion required. Use Q, R, B, or N."
                          << std::endl;

                // Undo the move
                restoreBoard(savedBoard);

                return;
            }

            char promotionPiece = move[4];

            if (promotionPiece == 'Q' ||
                promotionPiece == 'R' ||
                promotionPiece == 'B' ||
                promotionPiece == 'N')
            {
                board[toRow][toCol] = promotionPiece;
            }
            else
            {
                std::cout << "Invalid promotion piece. Use Q, R, B, or N."
                          << std::endl;

                // Undo the move
                restoreBoard(savedBoard);

                return;
            }
        }

        if (piece == 'p' && toRow == 7)
        {
            if (move.length() != 5)
            {
                std::cout << "Promotion required. Use q, r, b, or n."
                          << std::endl;

                // Undo the move
                restoreBoard(savedBoard);

                return;
            }

            char promotionPiece = move[4];

            if (promotionPiece == 'q' ||
                promotionPiece == 'r' ||
                promotionPiece == 'b' ||
                promotionPiece == 'n')
            {
                board[toRow][toCol] = promotionPiece;
            }
            else
            {
                std::cout << "Invalid promotion piece. Use q, r, b, or n."
                          << std::endl;

                // Undo the move
                restoreBoard(savedBoard);

                return;
            }
        }
    }
    else if (piece == 'N' || piece == 'n')
   {
    int rowDifference = abs(toRow - fromRow);
    int colDifference = abs(toCol - fromCol);

    // Check if the move has the correct L shape
    if (!((rowDifference == 2 && colDifference == 1) ||
          (rowDifference == 1 && colDifference == 2)))
    {
        std::cout << "Illegal knight move." << std::endl;
        return;
    }

    char destination = board[toRow][toCol];

    // White knight
    if (piece == 'N')
    {
        // Cannot capture another white piece
        if (destination >= 'A' && destination <= 'Z')
        {
            std::cout << "Illegal move: You cannot capture your own piece."
                      << std::endl;
            return;
        }
    }

    // Black knight
    if (piece == 'n')
    {
        // Cannot capture another black piece
        if (destination >= 'a' && destination <= 'z')
        {
            std::cout << "Illegal move: You cannot capture your own piece."
                      << std::endl;
            return;
        }
    }

    // Make the move
    board[toRow][toCol] = piece;
    board[fromRow][fromCol] = '.';

}
   else if (piece == 'B' || piece == 'b')
{
    int rowDifference = abs(toRow - fromRow);
    int colDifference = abs(toCol - fromCol);

    // Check if the move is diagonal
    if (rowDifference != colDifference)
    {
        std::cout << "Illegal bishop move." << std::endl;
        return;
    }

    // Determine direction
    int rowDirection;

    if (toRow > fromRow)
        rowDirection = 1;
    else
        rowDirection = -1;

    int colDirection;

    if (toCol > fromCol)
        colDirection = 1;
    else
        colDirection = -1;

    // Check every square between start and destination
    int currentRow = fromRow + rowDirection;
    int currentCol = fromCol + colDirection;

    while (currentRow != toRow || currentCol != toCol)
    {
        if (board[currentRow][currentCol] != '.')
        {
            std::cout << "Illegal bishop move: Path is blocked."
                      << std::endl;
            return;
        }

        currentRow += rowDirection;
        currentCol += colDirection;
    }

    // Check destination
    char destination = board[toRow][toCol];

    if (piece == 'B')
    {
        if (destination >= 'A' && destination <= 'Z')
        {
            std::cout << "Illegal move: You cannot capture your own piece."
                      << std::endl;
            return;
        }
    }
    else
    {
        if (destination >= 'a' && destination <= 'z')
        {
            std::cout << "Illegal move: You cannot capture your own piece."
                      << std::endl;
            return;
        }
    }

    // Move bishop
    board[toRow][toCol] = piece;
    board[fromRow][fromCol] = '.';
}
else if (piece == 'R' || piece == 'r')
{
    int rowDifference = abs(toRow - fromRow);
    int colDifference = abs(toCol - fromCol);

    // Rook must move horizontally or vertically
    if (rowDifference != 0 && colDifference != 0)
    {
        std::cout << "Illegal rook move." << std::endl;
        return;
    }

    // Determine direction
    int rowDirection = 0;
    int colDirection = 0;

    if (toRow > fromRow)
        rowDirection = 1;
    else if (toRow < fromRow)
        rowDirection = -1;

    if (toCol > fromCol)
        colDirection = 1;
    else if (toCol < fromCol)
        colDirection = -1;

    // Check path
    int currentRow = fromRow + rowDirection;
    int currentCol = fromCol + colDirection;

    while (currentRow != toRow || currentCol != toCol)
    {
        if (board[currentRow][currentCol] != '.')
        {
            std::cout << "Illegal rook move: Path is blocked."
                      << std::endl;
            return;
        }

        currentRow += rowDirection;
        currentCol += colDirection;
    }

    // Check destination
    char destination = board[toRow][toCol];

    if (piece == 'R')
    {
        if (destination >= 'A' && destination <= 'Z')
        {
            std::cout << "Illegal move: You cannot capture your own piece."
                      << std::endl;
            return;
        }
    }
    else
    {
        if (destination >= 'a' && destination <= 'z')
        {
            std::cout << "Illegal move: You cannot capture your own piece."
                      << std::endl;
            return;
        }
    }

    // Move rook
    board[toRow][toCol] = piece;
    board[fromRow][fromCol] = '.';
}
else if (piece == 'Q' || piece == 'q')
{
    int rowDifference = abs(toRow - fromRow);
    int colDifference = abs(toCol - fromCol);

    // Queen must move horizontally, vertically, or diagonally
    if (rowDifference != 0 &&
        colDifference != 0 &&
        rowDifference != colDifference)
    {
        std::cout << "Illegal queen move." << std::endl;
        return;
    }

    // Determine direction
    int rowDirection = 0;
    int colDirection = 0;

    if (toRow > fromRow)
        rowDirection = 1;
    else if (toRow < fromRow)
        rowDirection = -1;

    if (toCol > fromCol)
        colDirection = 1;
    else if (toCol < fromCol)
        colDirection = -1;

    // Check path
    int currentRow = fromRow + rowDirection;
    int currentCol = fromCol + colDirection;

    while (currentRow != toRow || currentCol != toCol)
    {
        if (board[currentRow][currentCol] != '.')
        {
            std::cout << "Illegal queen move: Path is blocked."
                      << std::endl;
            return;
        }

        currentRow += rowDirection;
        currentCol += colDirection;
    }

    // Check destination
    char destination = board[toRow][toCol];

    if (piece == 'Q')
    {
        if (destination >= 'A' && destination <= 'Z')
        {
            std::cout << "Illegal move: You cannot capture your own piece."
                      << std::endl;
            return;
        }
    }
    else
    {
        if (destination >= 'a' && destination <= 'z')
        {
            std::cout << "Illegal move: You cannot capture your own piece."
                      << std::endl;
            return;
        }
    }

    // Move queen
    board[toRow][toCol] = piece;
    board[fromRow][fromCol] = '.';
}
else if (piece == 'K' || piece == 'k')
{
    int rowDifference = abs(toRow - fromRow);
    int colDifference = abs(toCol - fromCol);

    // --------------------------------
    // CASTLING
    // --------------------------------

    // WHITE KINGSIDE: e1 -> g1
    if (piece == 'K' &&
        fromRow == 7 && fromCol == 4 &&
        toRow == 7 && toCol == 6)
    {
        // King must not have moved
        if (whiteKingMoved)
        {
            cout << "Illegal castling: White king has already moved." << endl;
            return;
        }

        // Rook must not have moved
        if (whiteKingsideRookMoved)
        {
            cout << "Illegal castling: White kingside rook has already moved." << endl;
            return;
        }

        // Squares f1 and g1 must be empty
        if (board[7][5] != '.' || board[7][6] != '.')
        {
            cout << "Illegal castling: Pieces are blocking the king." << endl;
            return;
        }

        // Rook must actually be on h1
        if (board[7][7] != 'R')
        {
            cout << "Illegal castling: Rook is not on h1." << endl;
            return;
        }

        // King cannot castle while in check
        if (isSquareAttacked(7, 4, false))
        {
            cout << "Illegal castling: King is currently in check." << endl;
            return;
        }

        // King cannot move through check
        if (isSquareAttacked(7, 5, false))
        {
            cout << "Illegal castling: King would pass through check." << endl;
            return;
        }

        // King cannot end in check
        if (isSquareAttacked(7, 6, false))
        {
            cout << "Illegal castling: King would end in check." << endl;
            return;
        }

        // Move king
        board[7][6] = 'K';
        board[7][4] = '.';

        // Move rook
        board[7][5] = 'R';
        board[7][7] = '.';
    }

    // WHITE QUEENSIDE: e1 -> c1
    else if (piece == 'K' &&
             fromRow == 7 && fromCol == 4 &&
             toRow == 7 && toCol == 2)
    {
        if (whiteKingMoved)
        {
            cout << "Illegal castling: White king has already moved." << endl;
            return;
        }

        if (whiteQueensideRookMoved)
        {
            cout << "Illegal castling: White queenside rook has already moved." << endl;
            return;
        }

        // b1, c1 and d1 must be empty
        if (board[7][1] != '.' ||
            board[7][2] != '.' ||
            board[7][3] != '.')
        {
            cout << "Illegal castling: Pieces are blocking the king." << endl;
            return;
        }

        // Rook must actually be on a1
        if (board[7][0] != 'R')
        {
            cout << "Illegal castling: Rook is not on a1." << endl;
            return;
        }

        // King cannot be in check
        if (isSquareAttacked(7, 4, false))
        {
            cout << "Illegal castling: King is currently in check." << endl;
            return;
        }

        // King cannot pass through d1 while attacked
        if (isSquareAttacked(7, 3, false))
        {
            cout << "Illegal castling: King would pass through check." << endl;
            return;
        }

        // King cannot end on c1 while attacked
        if (isSquareAttacked(7, 2, false))
        {
            cout << "Illegal castling: King would end in check." << endl;
            return;
        }

        // Move king
        board[7][2] = 'K';
        board[7][4] = '.';

        // Move rook
        board[7][3] = 'R';
        board[7][0] = '.';
    }

    // BLACK KINGSIDE: e8 -> g8
    else if (piece == 'k' &&
             fromRow == 0 && fromCol == 4 &&
             toRow == 0 && toCol == 6)
    {
        if (blackKingMoved)
        {
            cout << "Illegal castling: Black king has already moved." << endl;
            return;
        }

        if (blackKingsideRookMoved)
        {
            cout << "Illegal castling: Black kingside rook has already moved." << endl;
            return;
        }

        // f8 and g8 must be empty
        if (board[0][5] != '.' || board[0][6] != '.')
        {
            cout << "Illegal castling: Pieces are blocking the king." << endl;
            return;
        }

        // Rook must actually be on h8
        if (board[0][7] != 'r')
        {
            cout << "Illegal castling: Rook is not on h8." << endl;
            return;
        }

        // King cannot be in check
        if (isSquareAttacked(0, 4, true))
        {
            cout << "Illegal castling: King is currently in check." << endl;
            return;
        }

        // King cannot pass through check
        if (isSquareAttacked(0, 5, true))
        {
            cout << "Illegal castling: King would pass through check." << endl;
            return;
        }

        // King cannot end in check
        if (isSquareAttacked(0, 6, true))
        {
            cout << "Illegal castling: King would end in check." << endl;
            return;
        }

        // Move king
        board[0][6] = 'k';
        board[0][4] = '.';

        // Move rook
        board[0][5] = 'r';
        board[0][7] = '.';
    }

    // BLACK QUEENSIDE: e8 -> c8
    else if (piece == 'k' &&
             fromRow == 0 && fromCol == 4 &&
             toRow == 0 && toCol == 2)
    {
        if (blackKingMoved)
        {
            cout << "Illegal castling: Black king has already moved." << endl;
            return;
        }

        if (blackQueensideRookMoved)
        {
            cout << "Illegal castling: Black queenside rook has already moved." << endl;
            return;
        }

        // b8, c8 and d8 must be empty
        if (board[0][1] != '.' ||
            board[0][2] != '.' ||
            board[0][3] != '.')
        {
            cout << "Illegal castling: Pieces are blocking the king." << endl;
            return;
        }

        // Rook must actually be on a8
        if (board[0][0] != 'r')
        {
            cout << "Illegal castling: Rook is not on a8." << endl;
            return;
        }

        // King cannot be in check
        if (isSquareAttacked(0, 4, true))
        {
            cout << "Illegal castling: King is currently in check." << endl;
            return;
        }

        // King cannot pass through d8
        if (isSquareAttacked(0, 3, true))
        {
            cout << "Illegal castling: King would pass through check." << endl;
            return;
        }

        // King cannot end on c8
        if (isSquareAttacked(0, 2, true))
        {
            cout << "Illegal castling: King would end in check." << endl;
            return;
        }

        // Move king
        board[0][2] = 'k';
        board[0][4] = '.';

        // Move rook
        board[0][3] = 'r';
        board[0][0] = '.';
    }

    // --------------------------------
    // NORMAL KING MOVE
    // --------------------------------
    else
    {
        // King can only move one square
        if (rowDifference > 1 || colDifference > 1)
        {
            cout << "Illegal king move." << endl;
            return;
        }

        char destination = board[toRow][toCol];

        // White king cannot capture white piece
        if (piece == 'K' && isWhitePiece(destination))
        {
            cout << "Illegal move: You cannot capture your own piece."
                 << endl;
            return;
        }

        // Black king cannot capture black piece
        if (piece == 'k' && isBlackPiece(destination))
        {
            cout << "Illegal move: You cannot capture your own piece."
                 << endl;
            return;
        }

        // Make normal king move
        board[toRow][toCol] = piece;
        board[fromRow][fromCol] = '.';
    }
}
else
    {
        std::cout << "We haven't implemented that piece yet."
                  << std::endl;
        return;
    }
// --------------------------------
// UPDATE CASTLING RIGHTS
// --------------------------------

if (piece == 'K')
{
    whiteKingMoved = true;
}

if (piece == 'k')
{
    blackKingMoved = true;
}

if (piece == 'R')
{
    if (fromRow == 7 && fromCol == 7)
    {
        whiteKingsideRookMoved = true;
    }

    if (fromRow == 7 && fromCol == 0)
    {
        whiteQueensideRookMoved = true;
    }
}

if (piece == 'r')
{
    if (fromRow == 0 && fromCol == 7)
    {
        blackKingsideRookMoved = true;
    }

    if (fromRow == 0 && fromCol == 0)
    {
        blackQueensideRookMoved = true;
    }
}



// Check whether the move leaves our own king in check
if (isKingInCheck(whiteTurn))
{
    restoreBoard(savedBoard);
        whiteKingMoved = savedWhiteKingMoved;
    blackKingMoved = savedBlackKingMoved;

    whiteKingsideRookMoved = savedWhiteKingsideRookMoved;
    whiteQueensideRookMoved = savedWhiteQueensideRookMoved;

    blackKingsideRookMoved = savedBlackKingsideRookMoved;
    blackQueensideRookMoved = savedBlackQueensideRookMoved;

    std::cout << "Illegal move: Your king would be in check."
              << std::endl;

    return;
}

// The move is legal, so remember it for en passant
lastFromRow = fromRow;
lastFromCol = fromCol;
lastToRow = toRow;
lastToCol = toCol;

// Change turn
whiteTurn = !whiteTurn;
}
///attack and check detection
bool Board::isSquareAttacked(int row, int col, bool byWhite)
{
    // PAWN ATTACKS

    if (byWhite)
    {
        int pawnRow = row + 1;

        if (pawnRow >= 0 && pawnRow < 8)
        {
            if (col - 1 >= 0 && board[pawnRow][col - 1] == 'P')
                return true;

            if (col + 1 < 8 && board[pawnRow][col + 1] == 'P')
                return true;
        }
    }
    else
    {
        int pawnRow = row - 1;

        if (pawnRow >= 0 && pawnRow < 8)
        {
            if (col - 1 >= 0 && board[pawnRow][col - 1] == 'p')
                return true;

            if (col + 1 < 8 && board[pawnRow][col + 1] == 'p')
                return true;
        }
    }

    // KNIGHT ATTACKS

int knightMoves[8][2] =
{
    {-2, -1},
    {-2,  1},
    {-1, -2},
    {-1,  2},
    { 1, -2},
    { 1,  2},
    { 2, -1},
    { 2,  1}
};

for (int i = 0; i < 8; i++)
{
    int checkRow = row + knightMoves[i][0];
    int checkCol = col + knightMoves[i][1];

    if (checkRow >= 0 && checkRow < 8 &&
        checkCol >= 0 && checkCol < 8)
    {
        if (byWhite && board[checkRow][checkCol] == 'N')
            return true;

        if (!byWhite && board[checkRow][checkCol] == 'n')
            return true;
    }
}

// KING ATTACKS

for (int rowOffset = -1; rowOffset <= 1; rowOffset++)
{
    for (int colOffset = -1; colOffset <= 1; colOffset++)
    {
        if (rowOffset == 0 && colOffset == 0)
            continue;

        int checkRow = row + rowOffset;
        int checkCol = col + colOffset;

        if (checkRow >= 0 && checkRow < 8 &&
            checkCol >= 0 && checkCol < 8)
        {
            if (byWhite && board[checkRow][checkCol] == 'K')
                return true;

            if (!byWhite && board[checkRow][checkCol] == 'k')
                return true;
        }
    }
}
// ROOK / QUEEN ATTACKS

int straightDirections[4][2] =
{
    {-1, 0},
    { 1, 0},
    { 0,-1},
    { 0, 1}
};

for (int direction = 0; direction < 4; direction++)
{
    int checkRow = row + straightDirections[direction][0];
    int checkCol = col + straightDirections[direction][1];

    while (checkRow >= 0 && checkRow < 8 &&
           checkCol >= 0 && checkCol < 8)
    {
        char piece = board[checkRow][checkCol];

        if (piece != '.')
        {
            if (byWhite)
            {
                if (piece == 'R' || piece == 'Q')
                    return true;
            }
            else
            {
                if (piece == 'r' || piece == 'q')
                    return true;
            }

            break;
        }

        checkRow += straightDirections[direction][0];
        checkCol += straightDirections[direction][1];
    }
}

// BISHOP / QUEEN ATTACKS

int diagonalDirections[4][2] =
{
    {-1,-1},
    {-1, 1},
    { 1,-1},
    { 1, 1}
};

for (int direction = 0; direction < 4; direction++)
{
    int checkRow = row + diagonalDirections[direction][0];
    int checkCol = col + diagonalDirections[direction][1];

    while (checkRow >= 0 && checkRow < 8 &&
           checkCol >= 0 && checkCol < 8)
    {
        char piece = board[checkRow][checkCol];

        if (piece != '.')
        {
            if (byWhite)
            {
                if (piece == 'B' || piece == 'Q')
                    return true;
            }
            else
            {
                if (piece == 'b' || piece == 'q')
                    return true;
            }

            break;
        }

        checkRow += diagonalDirections[direction][0];
        checkCol += diagonalDirections[direction][1];
    }
}


    return false;
}


bool Board::isKingInCheck(bool white)
{
    char king;

    if (white)
        king = 'K';
    else
        king = 'k';

    // Find the king
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (board[row][col] == king)
            {
                return isSquareAttacked(row, col, !white);
            }
        }
    }

    return false;
}

///undo move

void Board::undoMove(int fromRow, int fromCol,
                     int toRow, int toCol,
                     char capturedPiece)
{
    // Move the piece back
    board[fromRow][fromCol] = board[toRow][toCol];

    // Restore whatever was captured
    board[toRow][toCol] = capturedPiece;
}


bool Board::isWhitePiece(char piece)
{
    return piece >= 'A' && piece <= 'Z';
}

bool Board::isBlackPiece(char piece)
{
    return piece >= 'a' && piece <= 'z';
}


void Board::restoreBoard(char savedBoard[8][8])
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            board[row][col] = savedBoard[row][col];
        }
    }
}

std::vector<std::string> Board::getLegalMoves()
{
    std::vector<std::string> legalMoves;

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            char piece = board[row][col];

            // Skip empty squares
            if (piece == '.')
                continue;

            // Only look at pieces belonging to the current player
            if (whiteTurn && !isWhitePiece(piece))
                continue;

            if (!whiteTurn && !isBlackPiece(piece))
                continue;

            // We are starting with pawns
            if (piece == 'P' || piece == 'p')
            {
                // White pawn
                if (piece == 'P')
                {
                   // White pawn one square forward
if (row - 1 >= 0 && board[row - 1][col] == '.')
{
    std::string move;

    move += char('a' + col);
    move += char('1' + (7 - row));
    move += char('a' + col);
    move += char('1' + (7 - (row - 1)));

    // Promotion
if (row - 1 == 0)
{
    if (isMoveLegal(move + "Q"))
        legalMoves.push_back(move + "Q");

    if (isMoveLegal(move + "R"))
        legalMoves.push_back(move + "R");

    if (isMoveLegal(move + "B"))
        legalMoves.push_back(move + "B");

    if (isMoveLegal(move + "N"))
        legalMoves.push_back(move + "N");
}
else
{
    if (isMoveLegal(move))
        legalMoves.push_back(move);
}
}

                    // Two squares forward from starting position
                    if (row == 6 &&
                        board[row - 1][col] == '.' &&
                        board[row - 2][col] == '.')
                    {
                        std::string move;

                        move += char('a' + col);
                        move += char('1' + (7 - row));
                        move += char('a' + col);
                        move += char('1' + (7 - (row - 2)));

                        if (isMoveLegal(move))
{
    legalMoves.push_back(move);
}
                    }
                    // White pawn captures
if (row - 1 >= 0)
{
    // Capture to the left
    if (col - 1 >= 0 && isBlackPiece(board[row - 1][col - 1]))
    {
        std::string move;

        move += char('a' + col);
        move += char('1' + (7 - row));
        move += char('a' + (col - 1));
        move += char('1' + (7 - (row - 1)));

if (row - 1 == 0)
{
    if (isMoveLegal(move + "Q"))
        legalMoves.push_back(move + "Q");

    if (isMoveLegal(move + "R"))
        legalMoves.push_back(move + "R");

    if (isMoveLegal(move + "B"))
        legalMoves.push_back(move + "B");

    if (isMoveLegal(move + "N"))
        legalMoves.push_back(move + "N");
}
else
{
    if (isMoveLegal(move))
    {
        legalMoves.push_back(move);
    }
}
    }

    // Capture to the right
    if (col + 1 < 8 && isBlackPiece(board[row - 1][col + 1]))
    {
        std::string move;

        move += char('a' + col);
        move += char('1' + (7 - row));
        move += char('a' + (col + 1));
        move += char('1' + (7 - (row - 1)));

if (row - 1 == 0)
{
    if (isMoveLegal(move + "Q"))
        legalMoves.push_back(move + "Q");

    if (isMoveLegal(move + "R"))
        legalMoves.push_back(move + "R");

    if (isMoveLegal(move + "B"))
        legalMoves.push_back(move + "B");

    if (isMoveLegal(move + "N"))
        legalMoves.push_back(move + "N");
}
else
{
    if (isMoveLegal(move))
    {
        legalMoves.push_back(move);
    }
}
    }
}
// White en passant
if (row == 3)
{
    // Capture black pawn on the left
    if (col - 1 >= 0 &&
        board[row][col - 1] == 'p' &&
        lastFromRow == 1 &&
        lastToRow == 3 &&
        lastFromCol == col - 1 &&
        lastToCol == col - 1)
    {
        std::string move;

        move += char('a' + col);
        move += char('1' + (7 - row));
        move += char('a' + (col - 1));
        move += char('1' + (7 - (row - 1)));

        if (isMoveLegal(move))
{
    legalMoves.push_back(move);
}
    }

    // Capture black pawn on the right
    if (col + 1 < 8 &&
        board[row][col + 1] == 'p' &&
        lastFromRow == 1 &&
        lastToRow == 3 &&
        lastFromCol == col + 1 &&
        lastToCol == col + 1)
    {
        std::string move;

        move += char('a' + col);
        move += char('1' + (7 - row));
        move += char('a' + (col + 1));
        move += char('1' + (7 - (row - 1)));

       if (isMoveLegal(move))
{
    legalMoves.push_back(move);
}
    }
}
                }

                // Black pawn
                if (piece == 'p')
                {
                    // One square forward
                    if (row + 1 < 8 && board[row + 1][col] == '.')
                    {
                        std::string move;

                        move += char('a' + col);
                        move += char('1' + (7 - row));
                        move += char('a' + col);
                        move += char('1' + (7 - (row + 1)));
if (row + 1 == 7)
{
    if (isMoveLegal(move + "q"))
        legalMoves.push_back(move + "q");

    if (isMoveLegal(move + "r"))
        legalMoves.push_back(move + "r");

    if (isMoveLegal(move + "b"))
        legalMoves.push_back(move + "b");

    if (isMoveLegal(move + "n"))
        legalMoves.push_back(move + "n");
}
else
{
    if (isMoveLegal(move))
    {
        legalMoves.push_back(move);
    }
}
                    }

                    // Two squares forward from starting position
                    if (row == 1 &&
                        board[row + 1][col] == '.' &&
                        board[row + 2][col] == '.')
                    {
                        std::string move;

                        move += char('a' + col);
                        move += char('1' + (7 - row));
                        move += char('a' + col);
                        move += char('1' + (7 - (row + 2)));

                        if (isMoveLegal(move))
{
    legalMoves.push_back(move);
}
                    }
                    // Black pawn captures
if (row + 1 < 8)
{
    // Capture to the left
    if (col - 1 >= 0 && isWhitePiece(board[row + 1][col - 1]))
    {
        std::string move;

        move += char('a' + col);
        move += char('1' + (7 - row));
        move += char('a' + (col - 1));
        move += char('1' + (7 - (row + 1)));

       if (row + 1 == 7)
{
    if (isMoveLegal(move + "q"))
        legalMoves.push_back(move + "q");

    if (isMoveLegal(move + "r"))
        legalMoves.push_back(move + "r");

    if (isMoveLegal(move + "b"))
        legalMoves.push_back(move + "b");

    if (isMoveLegal(move + "n"))
        legalMoves.push_back(move + "n");
}
else
{
    if (isMoveLegal(move))
    {
        legalMoves.push_back(move);
    }
}
    }

    // Capture to the right
    if (col + 1 < 8 && isWhitePiece(board[row + 1][col + 1]))
    {
        std::string move;

        move += char('a' + col);
        move += char('1' + (7 - row));
        move += char('a' + (col + 1));
        move += char('1' + (7 - (row + 1)));

if (row + 1 == 7)
{
    if (isMoveLegal(move + "q"))
        legalMoves.push_back(move + "q");

    if (isMoveLegal(move + "r"))
        legalMoves.push_back(move + "r");

    if (isMoveLegal(move + "b"))
        legalMoves.push_back(move + "b");

    if (isMoveLegal(move + "n"))
        legalMoves.push_back(move + "n");
}
else
{
    if (isMoveLegal(move))
    {
        legalMoves.push_back(move);
    }
}
    }
}
// Black en passant
if (row == 4)
{
    // Capture white pawn on the left
    if (col - 1 >= 0 &&
        board[row][col - 1] == 'P' &&
        lastFromRow == 6 &&
        lastToRow == 4 &&
        lastFromCol == col - 1 &&
        lastToCol == col - 1)
    {
        std::string move;

        move += char('a' + col);
        move += char('1' + (7 - row));
        move += char('a' + (col - 1));
        move += char('1' + (7 - (row + 1)));

        if (isMoveLegal(move))
{
    legalMoves.push_back(move);
}
    }

    // Capture white pawn on the right
    if (col + 1 < 8 &&
        board[row][col + 1] == 'P' &&
        lastFromRow == 6 &&
        lastToRow == 4 &&
        lastFromCol == col + 1 &&
        lastToCol == col + 1)
    {
        std::string move;

        move += char('a' + col);
        move += char('1' + (7 - row));
        move += char('a' + (col + 1));
        move += char('1' + (7 - (row + 1)));

        if (isMoveLegal(move))
{
    legalMoves.push_back(move);
}
    }
}
                }
            }

            // Knight moves
if (piece == 'N' || piece == 'n')
{
    int knightMoves[8][2] =
    {
        {-2, -1},
        {-2,  1},
        {-1, -2},
        {-1,  2},
        { 1, -2},
        { 1,  2},
        { 2, -1},
        { 2,  1}
    };

    for (int i = 0; i < 8; i++)
    {
        int newRow = row + knightMoves[i][0];
        int newCol = col + knightMoves[i][1];

        // Make sure the destination is on the board
        if (newRow < 0 || newRow >= 8 ||
            newCol < 0 || newCol >= 8)
        {
            continue;
        }

        char destination = board[newRow][newCol];

        // White knight cannot move onto a white piece
        if (piece == 'N' && isWhitePiece(destination))
        {
            continue;
        }

        // Black knight cannot move onto a black piece
        if (piece == 'n' && isBlackPiece(destination))
        {
            continue;
        }

        std::string move;

        move += char('a' + col);
        move += char('1' + (7 - row));
        move += char('a' + newCol);
        move += char('1' + (7 - newRow));

        if (isMoveLegal(move))
{
    legalMoves.push_back(move);
}
    }
}
// Bishop moves
if (piece == 'B' || piece == 'b')
{
    int directions[4][2] =
    {
        {-1, -1},  // up-left
        {-1,  1},  // up-right
        { 1, -1},  // down-left
        { 1,  1}   // down-right
    };

    for (int i = 0; i < 4; i++)
    {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];

        while (newRow >= 0 && newRow < 8 &&
               newCol >= 0 && newCol < 8)
        {
            char destination = board[newRow][newCol];

            // Friendly piece blocks the bishop
            if (piece == 'B' && isWhitePiece(destination))
            {
                break;
            }

            if (piece == 'b' && isBlackPiece(destination))
            {
                break;
            }

            // Create the move
            std::string move;

            move += char('a' + col);
            move += char('1' + (7 - row));
            move += char('a' + newCol);
            move += char('1' + (7 - newRow));

            if (isMoveLegal(move))
{
    legalMoves.push_back(move);
}

            // Enemy piece can be captured,
            // but the bishop cannot move beyond it.
            if (piece == 'B' && isBlackPiece(destination))
            {
                break;
            }

            if (piece == 'b' && isWhitePiece(destination))
            {
                break;
            }

            // Continue along the diagonal
            newRow += directions[i][0];
            newCol += directions[i][1];
        }
    }
}
// Rook moves
if (piece == 'R' || piece == 'r')
{
    int directions[4][2] =
    {
        {-1,  0},  // up
        { 1,  0},  // down
        { 0, -1},  // left
        { 0,  1}   // right
    };

    for (int i = 0; i < 4; i++)
    {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];

        while (newRow >= 0 && newRow < 8 &&
               newCol >= 0 && newCol < 8)
        {
            char destination = board[newRow][newCol];

            // Friendly piece blocks the rook
            if (piece == 'R' && isWhitePiece(destination))
            {
                break;
            }

            if (piece == 'r' && isBlackPiece(destination))
            {
                break;
            }

            // Create the move
            std::string move;

            move += char('a' + col);
            move += char('1' + (7 - row));
            move += char('a' + newCol);
            move += char('1' + (7 - newRow));

            if (isMoveLegal(move))
{
    legalMoves.push_back(move);
}

            // Enemy piece can be captured,
            // but the rook cannot move beyond it.
            if (piece == 'R' && isBlackPiece(destination))
            {
                break;
            }

            if (piece == 'r' && isWhitePiece(destination))
            {
                break;
            }

            // Continue in the same direction
            newRow += directions[i][0];
            newCol += directions[i][1];
        }
    }
}
// Queen moves
if (piece == 'Q' || piece == 'q')
{
    int directions[8][2] =
    {
        {-1,  0},  // up
        { 1,  0},  // down
        { 0, -1},  // left
        { 0,  1},  // right

        {-1, -1},  // up-left
        {-1,  1},  // up-right
        { 1, -1},  // down-left
        { 1,  1}   // down-right
    };

    for (int i = 0; i < 8; i++)
    {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];

        while (newRow >= 0 && newRow < 8 &&
               newCol >= 0 && newCol < 8)
        {
            char destination = board[newRow][newCol];

            // Friendly piece blocks the queen
            if (piece == 'Q' && isWhitePiece(destination))
            {
                break;
            }

            if (piece == 'q' && isBlackPiece(destination))
            {
                break;
            }

            // Create move
            std::string move;

            move += char('a' + col);
            move += char('1' + (7 - row));
            move += char('a' + newCol);
            move += char('1' + (7 - newRow));

            if (isMoveLegal(move))
{
    legalMoves.push_back(move);
}

            // Enemy piece can be captured,
            // but the queen cannot move beyond it.
            if (piece == 'Q' && isBlackPiece(destination))
            {
                break;
            }

            if (piece == 'q' && isWhitePiece(destination))
            {
                break;
            }

            // Continue in the same direction
            newRow += directions[i][0];
            newCol += directions[i][1];
        }
    }
}

// King moves
if (piece == 'K' || piece == 'k')
{
    int directions[8][2] =
    {
        {-1, -1},  // up-left
        {-1,  0},  // up
        {-1,  1},  // up-right
        { 0, -1},  // left
        { 0,  1},  // right
        { 1, -1},  // down-left
        { 1,  0},  // down
        { 1,  1}   // down-right
    };

    for (int i = 0; i < 8; i++)
    {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];

        // Make sure the destination is on the board
        if (newRow < 0 || newRow >= 8 ||
            newCol < 0 || newCol >= 8)
        {
            continue;
        }

        char destination = board[newRow][newCol];

        // King cannot capture its own piece
        if (piece == 'K' && isWhitePiece(destination))
        {
            continue;
        }

        if (piece == 'k' && isBlackPiece(destination))
        {
            continue;
        }

        std::string move;

        move += char('a' + col);
        move += char('1' + (7 - row));
        move += char('a' + newCol);
        move += char('1' + (7 - newRow));

        if (isMoveLegal(move))
{
    legalMoves.push_back(move);
}
    }
    // White castling
// White castling
if (piece == 'K' && !whiteKingMoved)
{
    // White kingside castling: e1 -> g1
    if (!whiteKingsideRookMoved &&
        board[7][7] == 'R' &&
        board[7][5] == '.' &&
        board[7][6] == '.')
    {
        if (isMoveLegal("e1g1"))
        {
            legalMoves.push_back("e1g1");
        }
    }

    // White queenside castling: e1 -> c1
    if (!whiteQueensideRookMoved &&
        board[7][0] == 'R' &&
        board[7][1] == '.' &&
        board[7][2] == '.' &&
        board[7][3] == '.')
    {
        if (isMoveLegal("e1c1"))
        {
            legalMoves.push_back("e1c1");
        }
    }
}
    // Black castling
// Black castling
if (piece == 'k' && !blackKingMoved)
{
    // Black kingside castling: e8 -> g8
    if (!blackKingsideRookMoved &&
        board[0][7] == 'r' &&
        board[0][5] == '.' &&
        board[0][6] == '.')
    {
        if (isMoveLegal("e8g8"))
        {
            legalMoves.push_back("e8g8");
        }
    }

    // Black queenside castling: e8 -> c8
    if (!blackQueensideRookMoved &&
        board[0][0] == 'r' &&
        board[0][1] == '.' &&
        board[0][2] == '.' &&
        board[0][3] == '.')
    {
        if (isMoveLegal("e8c8"))
        {
            legalMoves.push_back("e8c8");
        }
    }
}





}




        }
    }

    return legalMoves;
}

bool Board::isMoveLegal(const std::string& move)
{
    if (move.length() != 4 && move.length() != 5)
        return false;

    int fromCol = move[0] - 'a';
    int fromRow = 7 - (move[1] - '1');

    int toCol = move[2] - 'a';
    int toRow = 7 - (move[3] - '1');

    // Check coordinates
    if (fromRow < 0 || fromRow >= 8 ||
        fromCol < 0 || fromCol >= 8 ||
        toRow < 0 || toRow >= 8 ||
        toCol < 0 || toCol >= 8)
    {
        return false;
    }

    char piece = board[fromRow][fromCol];

    if (piece == '.')
        return false;

    // Make sure piece belongs to current player
    if (whiteTurn && !isWhitePiece(piece))
        return false;

    if (!whiteTurn && !isBlackPiece(piece))
        return false;

    // Cannot capture your own piece
    char destination = board[toRow][toCol];

    if (piece == 'P' || piece == 'N' ||
        piece == 'B' || piece == 'R' ||
        piece == 'Q' || piece == 'K')
    {
        if (isWhitePiece(destination))
            return false;
    }
    else
    {
        if (isBlackPiece(destination))
            return false;
    }

    // Cannot capture the enemy king
    if (destination == 'K' || destination == 'k')
        return false;

    // Save board
    char savedBoard[8][8];

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            savedBoard[row][col] = board[row][col];
        }
    }

    // Save castling rights
    bool savedWhiteKingMoved = whiteKingMoved;
    bool savedBlackKingMoved = blackKingMoved;

    bool savedWhiteKingsideRookMoved =
        whiteKingsideRookMoved;

    bool savedWhiteQueensideRookMoved =
        whiteQueensideRookMoved;

    bool savedBlackKingsideRookMoved =
        blackKingsideRookMoved;

    bool savedBlackQueensideRookMoved =
        blackQueensideRookMoved;

    // --------------------------------------------------
    // CASTLING
    // --------------------------------------------------

    bool castling = false;

    // White kingside
    if (piece == 'K' &&
        fromRow == 7 && fromCol == 4 &&
        toRow == 7 && toCol == 6)
    {
        castling = true;

        if (whiteKingMoved ||
            whiteKingsideRookMoved)
        {
            goto restore;
        }

        if (board[7][7] != 'R')
            goto restore;

        if (board[7][5] != '.' ||
            board[7][6] != '.')
        {
            goto restore;
        }

        // King cannot castle through check
        if (isSquareAttacked(7, 4, false) ||
            isSquareAttacked(7, 5, false) ||
            isSquareAttacked(7, 6, false))
        {
            goto restore;
        }

        // Move king
        board[7][6] = 'K';
        board[7][4] = '.';

        // Move rook
        board[7][5] = 'R';
        board[7][7] = '.';
    }

    // White queenside
    else if (piece == 'K' &&
             fromRow == 7 && fromCol == 4 &&
             toRow == 7 && toCol == 2)
    {
        castling = true;

        if (whiteKingMoved ||
            whiteQueensideRookMoved)
        {
            goto restore;
        }

        if (board[7][0] != 'R')
            goto restore;

        if (board[7][1] != '.' ||
            board[7][2] != '.' ||
            board[7][3] != '.')
        {
            goto restore;
        }

        if (isSquareAttacked(7, 4, false) ||
            isSquareAttacked(7, 3, false) ||
            isSquareAttacked(7, 2, false))
        {
            goto restore;
        }

        // Move king
        board[7][2] = 'K';
        board[7][4] = '.';

        // Move rook
        board[7][3] = 'R';
        board[7][0] = '.';
    }

    // Black kingside
    else if (piece == 'k' &&
             fromRow == 0 && fromCol == 4 &&
             toRow == 0 && toCol == 6)
    {
        castling = true;

        if (blackKingMoved ||
            blackKingsideRookMoved)
        {
            goto restore;
        }

        if (board[0][7] != 'r')
            goto restore;

        if (board[0][5] != '.' ||
            board[0][6] != '.')
        {
            goto restore;
        }

        if (isSquareAttacked(0, 4, true) ||
            isSquareAttacked(0, 5, true) ||
            isSquareAttacked(0, 6, true))
        {
            goto restore;
        }

        // Move king
        board[0][6] = 'k';
        board[0][4] = '.';

        // Move rook
        board[0][5] = 'r';
        board[0][7] = '.';
    }

    // Black queenside
    else if (piece == 'k' &&
             fromRow == 0 && fromCol == 4 &&
             toRow == 0 && toCol == 2)
    {
        castling = true;

        if (blackKingMoved ||
            blackQueensideRookMoved)
        {
            goto restore;
        }

        if (board[0][0] != 'r')
            goto restore;

        if (board[0][1] != '.' ||
            board[0][2] != '.' ||
            board[0][3] != '.')
        {
            goto restore;
        }

        if (isSquareAttacked(0, 4, true) ||
            isSquareAttacked(0, 3, true) ||
            isSquareAttacked(0, 2, true))
        {
            goto restore;
        }

        // Move king
        board[0][2] = 'k';
        board[0][4] = '.';

        // Move rook
        board[0][3] = 'r';
        board[0][0] = '.';
    }

    // --------------------------------------------------
    // NORMAL MOVE
    // --------------------------------------------------

    else
    {
        // Normal move
        board[toRow][toCol] = piece;
        board[fromRow][fromCol] = '.';

        // En passant
        if ((piece == 'P' || piece == 'p') &&
            fromCol != toCol &&
            destination == '.')
        {
            if (piece == 'P')
            {
                // White pawn captures black pawn
                if (board[toRow + 1][toCol] == 'p')
                    board[toRow + 1][toCol] = '.';
            }
            else
            {
                // Black pawn captures white pawn
                if (board[toRow - 1][toCol] == 'P')
                    board[toRow - 1][toCol] = '.';
            }
        }

        // Promotion
        if (move.length() == 5)
        {
            char promotionPiece = move[4];

            if (piece == 'P')
            {
                if (promotionPiece != 'Q' &&
                    promotionPiece != 'R' &&
                    promotionPiece != 'B' &&
                    promotionPiece != 'N')
                {
                    goto restore;
                }

                board[toRow][toCol] = promotionPiece;
            }
            else if (piece == 'p')
            {
                if (promotionPiece != 'q' &&
                    promotionPiece != 'r' &&
                    promotionPiece != 'b' &&
                    promotionPiece != 'n')
                {
                    goto restore;
                }

                board[toRow][toCol] = promotionPiece;
            }
            else
            {
                // Only pawns can promote
                goto restore;
            }
        }
    }

    // --------------------------------------------------
    // CHECK KING
    // --------------------------------------------------

    if (isKingInCheck(whiteTurn))
        goto restore;

    // Everything is legal
    goto success;


restore:

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            board[row][col] = savedBoard[row][col];
        }
    }

    whiteKingMoved = savedWhiteKingMoved;
    blackKingMoved = savedBlackKingMoved;

    whiteKingsideRookMoved =
        savedWhiteKingsideRookMoved;

    whiteQueensideRookMoved =
        savedWhiteQueensideRookMoved;

    blackKingsideRookMoved =
        savedBlackKingsideRookMoved;

    blackQueensideRookMoved =
        savedBlackQueensideRookMoved;

    return false;


success:

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            board[row][col] = savedBoard[row][col];
        }
    }

    whiteKingMoved = savedWhiteKingMoved;
    blackKingMoved = savedBlackKingMoved;

    whiteKingsideRookMoved =
        savedWhiteKingsideRookMoved;

    whiteQueensideRookMoved =
        savedWhiteQueensideRookMoved;

    blackKingsideRookMoved =
        savedBlackKingsideRookMoved;

    blackQueensideRookMoved =
        savedBlackQueensideRookMoved;

    return true;
}








bool Board::isCheckmate(bool white)
{
    // The king must be in check
    if (!isKingInCheck(white))
    {
        return false;
    }

    // Temporarily set the turn
    bool savedTurn = whiteTurn;
    whiteTurn = white;

    std::vector<std::string> moves = getLegalMoves();

    // Restore turn
    whiteTurn = savedTurn;

    // Checkmate = in check + no legal moves
    if (moves.empty())
    {
        return true;
    }

    return false;
}


bool Board::isStalemate(bool white)
{
    // Stalemate requires the king NOT to be in check
    if (isKingInCheck(white))
    {
        return false;
    }

    // Temporarily set the turn
    bool savedTurn = whiteTurn;
    whiteTurn = white;

    std::vector<std::string> moves = getLegalMoves();

    // Restore turn
    whiteTurn = savedTurn;

    // Stalemate = not in check + no legal moves
    if (moves.empty())
    {
        return true;
    }

    return false;
}



void Board::checkGameStatus()
{
    if (isCheckmate(whiteTurn))
    {
        if (whiteTurn)
        {
            std::cout << "\nCHECKMATE! Black wins!\n";
        }
        else
        {
            std::cout << "\nCHECKMATE! White wins!\n";
        }

        return;
    }

    if (isStalemate(whiteTurn))
    {
        std::cout << "\nSTALEMATE! The game is a draw!\n";
        return;
    }

    if (isKingInCheck(whiteTurn))
    {
        if (whiteTurn)
        {
            std::cout << "\nWhite is in CHECK!\n";
        }
        else
        {
            std::cout << "\nBlack is in CHECK!\n";
        }
    }
}


void Board::printLegalMoves()
{
    vector<string> moves = getLegalMoves();

    cout << "\nLegal moves (" << moves.size() << "):\n";

    for (const string& move : moves)
    {
        cout << move << " ";
    }

    cout << endl;
}


PositionState Board::savePosition()
{
    PositionState state;

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            state.board[row][col] = board[row][col];
        }
    }

    state.whiteTurn = whiteTurn;

    state.lastFromRow = lastFromRow;
    state.lastFromCol = lastFromCol;
    state.lastToRow = lastToRow;
    state.lastToCol = lastToCol;

    state.whiteKingMoved = whiteKingMoved;
    state.blackKingMoved = blackKingMoved;

    state.whiteKingsideRookMoved =
        whiteKingsideRookMoved;

    state.whiteQueensideRookMoved =
        whiteQueensideRookMoved;

    state.blackKingsideRookMoved =
        blackKingsideRookMoved;

    state.blackQueensideRookMoved =
        blackQueensideRookMoved;

    return state;
}


void Board::restorePosition(const PositionState& state)
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            board[row][col] = state.board[row][col];
        }
    }

    whiteTurn = state.whiteTurn;

    lastFromRow = state.lastFromRow;
    lastFromCol = state.lastFromCol;
    lastToRow = state.lastToRow;
    lastToCol = state.lastToCol;

    whiteKingMoved = state.whiteKingMoved;
    blackKingMoved = state.blackKingMoved;

    whiteKingsideRookMoved =
        state.whiteKingsideRookMoved;

    whiteQueensideRookMoved =
        state.whiteQueensideRookMoved;

    blackKingsideRookMoved =
        state.blackKingsideRookMoved;

    blackQueensideRookMoved =
        state.blackQueensideRookMoved;
}


char Board::getPiece(int row, int col) const
{
    return board[row][col];
}

bool Board::isWhiteTurn() const
{
    return whiteTurn;
}
