# Chessengine
A chess engine built by me with help of AI
# C++ Chess Engine ♟️

A chess engine written in **C++** that allows a human player to play White against an AI-controlled Black player directly from the terminal.

The project implements the core components of a chess engine from scratch, including board representation, legal move generation, check/checkmate detection, special chess moves, position evaluation, and AI search using **Minimax** and **Alpha-Beta pruning**.

---

## Features

* ♟️ Complete 8×8 chess board representation
* 👤 Human vs AI gameplay
* 🤖 AI opponent using Minimax and Alpha-Beta pruning
* 🔎 Legal move generation
* ♜ Movement rules for all chess pieces
* 👑 Check detection
* 💀 Checkmate detection
* 🤝 Stalemate detection
* 🏰 Castling
* ⚔️ En passant
* 👸 Pawn promotion
* 📊 Material and positional evaluation
* 🌳 Perft move-generation testing
* ⏱️ AI search-time measurement
* 📝 Game recording
* 💾 Game saved to `game.pgn`
* 📋 Display of available legal moves

---

# How the Engine Works

The engine is separated into several major components:

```text
                    ┌───────────────┐
                    │     main.cpp  │
                    │  Game Loop    │
                    └───────┬───────┘
                            │
             ┌──────────────┼──────────────┐
             ▼              ▼              ▼
       ┌──────────┐   ┌──────────┐   ┌────────────┐
       │  Board   │   │  Engine  │   │ Evaluator  │
       └────┬─────┘   └────┬─────┘   └────────────┘
            │              │
            │              ▼
            │       Minimax / Alpha-Beta
            │
            ├── Move Generation
            ├── Move Validation
            ├── Check Detection
            ├── Castling
            ├── En Passant
            └── Promotion
```

The `Board` class is responsible for representing and validating chess positions.

The `Engine` class searches through possible future positions to determine the best move.

The `Evaluator` assigns a numerical score to a position so the engine can compare moves.

The `GameRecorder` stores the moves played during the game and saves the completed game to a file.

---

# Project Structure

A typical project structure is:

```text
ChessEngine/
│
├── main.cpp
├── Board.cpp
├── Board.h
├── Engine.cpp
├── Engine.h
├── Evaluator.cpp
├── Evaluator.h
├── GameRecorder.cpp
├── GameRecorder.h
│
├── game.pgn
│
└── README.md
```

---

# 1. `main.cpp`

`main.cpp` contains the main game loop and connects all of the engine components together.

At startup, the program creates:

```cpp
Board board;
Engine engine;
Evaluator evaluator;
GameRecorder recorder;
```

These objects represent:

* `Board` — current chess position and rules
* `Engine` — AI search
* `Evaluator` — position scoring
* `GameRecorder` — move history and game saving

The board is initially displayed and evaluated.

The user is then informed that they are playing White and can enter moves using coordinate notation such as:

```text
e2e4
g1f3
f1c4
```

The main loop alternates between the human and AI.

### Human turn

When it is White's turn:

```cpp
if (board.isWhiteTurn())
```

the program waits for the player to enter a move.

Typing:

```text
quit
```

ends the game.

Otherwise, the move is passed to:

```cpp
board.makeMove(move);
```

The resulting position is then evaluated and recorded.

### AI turn

When it is Black's turn, the engine searches for the best move:

```cpp
string aiMove =
    engine.getBestMoveAlphaBeta(board, 5);
```

The `5` represents the search depth.

The program also measures how long the search takes using C++'s `<chrono>` library.

For example:

```text
AI is thinking...
AI plays: e7e5
Search time: 342 ms
```

After every move, the board, evaluation, game status, and legal moves are displayed.

At the end of the game:

```cpp
recorder.printGame();
recorder.saveToFile("game.pgn");
```

the move history is printed and saved.

---

# 2. `Board.cpp`

The `Board` class is the core of the chess rules.

It is responsible for:

* Storing the board
* Making moves
* Validating moves
* Generating legal moves
* Detecting attacks
* Detecting check
* Detecting checkmate
* Detecting stalemate
* Handling castling
* Handling en passant
* Handling promotion
* Saving/restoring positions

---

## Board Representation

The chess board is represented using an 8×8 character array:

```cpp
char board[8][8];
```

Pieces are represented using characters.

### White pieces

```text
P = Pawn
N = Knight
B = Bishop
R = Rook
Q = Queen
K = King
```

### Black pieces

```text
p = Pawn
n = Knight
b = Bishop
r = Rook
q = Queen
k = King
```

An empty square is:

```text
.
```

The starting position is therefore represented as:

```text
r n b q k b n r
p p p p p p p p
. . . . . . . .
. . . . . . . .
. . . . . . . .
. . . . . . . .
P P P P P P P P
R N B Q K B N R
```

---

# 3. Coordinate Conversion

Moves use standard coordinate notation:

```text
e2e4
```

The first two characters represent the starting square:

```text
e2
```

and the final two represent the destination:

```text
e4
```

The engine converts these coordinates into array indexes.

For example:

```text
e2 → row 6, column 4
e4 → row 4, column 4
```

The board uses:

```text
row 0 = rank 8
row 7 = rank 1
```

while:

```text
column 0 = a
column 7 = h
```

This allows normal chess notation to be mapped onto the internal array representation.

---

# 4. Move Validation

The main move-making function is:

```cpp
Board::makeMove(std::string move)
```

It validates the move before changing the position.

The function checks things such as:

* Correct move format
* Valid board coordinates
* Whether a piece exists on the starting square
* Whether the piece belongs to the player whose turn it is
* Whether the destination contains a friendly piece
* Whether the piece can move in the requested way
* Whether sliding pieces have a clear path
* Whether special moves are legal
* Whether the move leaves the player's king in check

If a move would leave the player's own king in check, the board is restored.

---

# 5. Piece Movement

The engine implements movement rules individually for every piece.

## Pawns

Pawns support:

* One-square movement
* Two-square movement from the starting position
* Captures
* En passant
* Promotion

White pawns move toward decreasing array rows:

```text
6 → 5 → 4 → 3 → 2 → 1 → 0
```

Black pawns move toward increasing array rows:

```text
1 → 2 → 3 → 4 → 5 → 6 → 7
```

---

## Knights

Knights use the standard L-shaped movement:

```text
2 squares + 1 square
```

The engine checks all eight possible knight destinations.

Because knights can jump over pieces, no path checking is necessary.

---

## Bishops

Bishops move diagonally.

The engine walks through each of the four diagonal directions until it reaches:

* The edge of the board
* A friendly piece
* An enemy piece

An enemy piece can be captured, but the bishop cannot move beyond it.

---

## Rooks

Rooks move horizontally and vertically.

The engine checks the four possible directions:

```text
up
down
left
right
```

and verifies that no pieces block the path.

---

## Queens

Queens combine the movement of bishops and rooks.

The engine therefore checks eight directions:

```text
up
down
left
right

up-left
up-right
down-left
down-right
```

---

## Kings

Kings can move one square in any direction.

The engine also handles castling separately.

---

# 6. Castling

Castling is implemented for all four possibilities:

```text
White kingside:  e1 → g1
White queenside: e1 → c1

Black kingside:  e8 → g8
Black queenside: e8 → c8
```

The board keeps track of whether each king or rook has previously moved:

```cpp
whiteKingMoved
blackKingMoved

whiteKingsideRookMoved
whiteQueensideRookMoved

blackKingsideRookMoved
blackQueensideRookMoved
```

Castling also checks that:

* The king has not moved
* The appropriate rook has not moved
* The rook is actually present
* The required squares are empty
* The king is not currently in check
* The king does not pass through an attacked square
* The king does not finish on an attacked square

This prevents illegal castling positions.

---

# 7. En Passant

The engine tracks the previous move using:

```cpp
lastFromRow
lastFromCol
lastToRow
lastToCol
```

This allows it to determine whether a pawn has just moved two squares and can therefore be captured en passant.

For example:

```text
White pawn: e5
Black pawn: d7 → d5
White:      e5xd6 e.p.
```

The captured pawn is removed from its original square even though the destination square is empty.

---

# 8. Pawn Promotion

When a pawn reaches the final rank, the engine requires a promotion piece.

White promotion example:

```text
e7e8Q
```

Black promotion example:

```text
e2e1q
```

The supported promotion pieces are:

```text
Queen
Rook
Bishop
Knight
```

Promotion is represented by a fifth character in the move string.

---

# 9. Attack Detection

The function:

```cpp
isSquareAttacked(int row, int col, bool byWhite)
```

determines whether a square is attacked by a particular side.

It checks attacks from:

* Pawns
* Knights
* Kings
* Rooks
* Queens
* Bishops

Sliding attacks are detected by walking along straight or diagonal directions until a piece is encountered.

This function is particularly important for:

* Check detection
* King movement
* Castling
* Legal move generation

---

# 10. Check Detection

The function:

```cpp
isKingInCheck(bool white)
```

first finds the appropriate king:

```cpp
K
```

for White or:

```cpp
k
```

for Black.

It then calls:

```cpp
isSquareAttacked(...)
```

to determine whether the king is currently attacked by the opponent.

---

# 11. Legal Move Generation

The function:

```cpp
std::vector<std::string> Board::getLegalMoves()
```

generates all legal moves for the player whose turn it is.

The process is roughly:

```text
Find every piece belonging to the current player
            ↓
Generate possible destinations
            ↓
Check movement rules
            ↓
Check captures
            ↓
Handle special moves
            ↓
Test whether the move leaves the king in check
            ↓
Keep only legal moves
```

The result is a vector of move strings such as:

```text
e2e4
e2e3
g1f3
g1h3
```

This function is also used heavily by the chess engine's search algorithm.

---

# 12. `isMoveLegal()`

The function:

```cpp
bool Board::isMoveLegal(const std::string& move)
```

is used when generating moves.

Instead of permanently applying every candidate move, the engine:

1. Saves the current position.
2. Applies the candidate move.
3. Checks whether the king is in check.
4. Restores the original position.
5. Returns whether the move is legal.

This is an important part of preventing moves that expose the player's own king.

---

# 13. Position Saving and Restoration

The engine defines a `PositionState` structure to store the complete state of a position.

This includes:

* Board contents
* Side to move
* Previous move information
* King movement status
* Rook movement status

The functions:

```cpp
savePosition()
restorePosition()
```

are heavily used by the search algorithm.

They allow the engine to explore hypothetical moves without permanently changing the real game position.

Conceptually:

```text
Current position
      │
      ├── Make move A
      │      └── Search
      │
      ├── Restore
      │
      ├── Make move B
      │      └── Search
      │
      └── Restore
```

This is fundamental to minimax and alpha-beta search.

---

# 14. Checkmate and Stalemate

Checkmate is detected using:

```cpp
isCheckmate(bool white)
```

A position is checkmate when:

```text
King is in check
+
There are no legal moves
```

Stalemate is detected using:

```cpp
isStalemate(bool white)
```

A position is stalemate when:

```text
King is NOT in check
+
There are no legal moves
```

The `checkGameStatus()` function combines these checks and displays the appropriate message.

---

# 15. `Evaluator.cpp`

The evaluator converts a chess position into a numerical score.

The basic principle is:

```text
Positive score → White is better
Negative score → Black is better
```

For example:

```text
+500  → White has an advantage
   0  → Roughly equal
-500  → Black has an advantage
```

---

## Piece Values

The engine uses the following material values:

| Piece  | Value |
| ------ | ----: |
| Pawn   |   100 |
| Knight |   320 |
| Bishop |   330 |
| Rook   |   500 |
| Queen  |   900 |
| King   |     0 |

The king receives a value of `0` because checkmate is handled separately using very large scores.

Checkmate scores are:

```cpp
-100000
```

when White is checkmated, and:

```cpp
100000
```

when Black is checkmated.

---

# 16. Positional Evaluation

The evaluator currently includes some simple positional bonuses.

## Knight Development

A knight receives a bonus if it has moved away from its original square.

White knights receive:

```text
+30
```

when developed.

Black knight development contributes:

```text
-30
```

because the evaluation is from White's perspective.

---

## Pawn Advancement

Pawn advancement is also rewarded.

For White:

```cpp
score += advancement * 5;
```

For Black:

```cpp
score -= advancement * 5;
```

This gives the engine a basic preference for advancing pawns.

---

# 17. `Engine.cpp`

The `Engine` class is responsible for searching through possible chess positions.

It contains three main search components:

```text
Perft
Minimax
Alpha-Beta
```

---

# 18. Minimax

The basic Minimax algorithm searches through future positions.

The idea is:

```text
White tries to maximize the evaluation
Black tries to minimize the evaluation
```

For example:

```text
             Current Position
                    │
          ┌─────────┼─────────┐
          ▼         ▼         ▼
        Move A    Move B    Move C
          │         │         │
        Search    Search    Search
          │         │         │
          ▼         ▼         ▼
        Score     Score     Score
```

White chooses the highest score.

Black chooses the lowest score.

The recursive function is:

```cpp
minimax(Board& board,
        int depth,
        bool maximizingPlayer)
```

The `depth` determines how many moves ahead the engine searches.

---

# 19. Alpha-Beta Pruning

The engine also implements an optimized version of Minimax:

```cpp
alphaBeta(...)
```

Alpha-Beta pruning avoids searching branches that cannot possibly improve the final decision.

The two bounds are:

```text
Alpha = best guaranteed score for the maximizing player

Beta  = best guaranteed score for the minimizing player
```

When:

```text
beta <= alpha
```

the remaining moves in that branch can be ignored.

This creates a major performance improvement over plain Minimax.

Conceptually:

```text
                 Position
              /     |      \
             A      B       C
            / \    / \     / \
           ...    ...      ...

             ↓
      Alpha-Beta pruning

                 Position
              /     |      \
             A      B       C
            / \    /       / \
           ...   CUT      ...
```

The important point is that the skipped branches cannot change the final decision.

---

# 20. Search Depth

The current game uses:

```cpp
engine.getBestMoveAlphaBeta(board, 5);
```

Therefore, the AI searches to a depth of **5 plies**.

A ply is one individual move by one player.

So:

```text
Depth 1 = White move
Depth 2 = White + Black
Depth 3 = White + Black + White
...
Depth 5 = five individual moves
```

Increasing the depth generally makes the engine stronger but also increases computation time.

---

# 21. Node Counting

The engine tracks how many nodes each search algorithm visits.

```cpp
minimaxNodes
alphaBetaNodes
```

These counters can be retrieved using:

```cpp
getMinimaxNodes()
getAlphaBetaNodes()
```

This makes it possible to compare the efficiency of Minimax and Alpha-Beta pruning.

For example:

```text
Minimax:
1,250,000 nodes

Alpha-Beta:
180,000 nodes
```

The exact numbers depend on the position and move ordering.

---

# 22. Perft

The engine also includes a `perft()` function.

Perft is commonly used in chess programming to test the correctness of move generation.

It recursively counts the number of legal positions reachable at a given depth.

For example:

```cpp
perft(board, depth)
```

works conceptually like:

```text
Depth 0
→ 1 node

Depth 1
→ Count all legal moves

Depth 2
→ Count all positions after each legal move

Depth 3
→ Continue recursively
```

Perft is particularly useful for finding bugs in:

* Castling
* En passant
* Promotion
* Check detection
* Move generation

---

# 23. Game Recording

The `GameRecorder` class is responsible for storing the moves played during the game.

After each move, the program records:

```cpp
recorder.addMove(move, evaluation);
```

This stores both:

* The move
* The evaluation after the move

At the end of the game:

```cpp
recorder.printGame();
```

prints the recorded game.

The game is also saved using:

```cpp
recorder.saveToFile("game.pgn");
```

This creates:

```text
game.pgn
```

which can be used to preserve the game record.

---

# 24. Example Gameplay

When the program starts, it displays something similar to:

```text
==============================
       C++ CHESS ENGINE
==============================

  a b c d e f g h
8 r n b q k b n r
7 p p p p p p p p
6 . . . . . . . .
5 . . . . . . . .
4 . . . . . . . .
3 . . . . . . . .
2 P P P P P P P P
1 R N B Q K B N R

Evaluation: 0

You are White.
Enter moves like e2e4.
Type quit to exit.
```

The player can enter:

```text
Your move: e2e4
```

The engine then calculates Black's response:

```text
AI is thinking...
AI plays: e7e5
Search time: 125 ms
```

The updated position is displayed and the game continues.

---

# 25. Building the Project

The project uses standard C++ and does not require an external chess library.

For example, using `g++`:

```bash
g++ -std=c++17 main.cpp Board.cpp Engine.cpp Evaluator.cpp GameRecorder.cpp -o chess
```

Then run:

### Linux / macOS

```bash
./chess
```

### Windows

```bash
chess.exe
```

If your project contains additional `.cpp` files, include them in the compilation command.

---

# 26. Playing the Game

Once the executable is running, enter moves using coordinate notation:

```text
e2e4
```

Examples:

```text
e2e4
g1f3
f1c4
e1g1
```

Castling:

```text
e1g1
```

Promotion:

```text
e7e8Q
```

En passant is entered using the normal destination square.

To exit:

```text
quit
```

---

# 27. Design Philosophy

The project focuses on implementing the fundamental ideas behind chess engines rather than relying on an external chess framework.

The main pipeline is:

```text
                   Chess Position
                         │
                         ▼
                  Generate Moves
                         │
                         ▼
                  Validate Moves
                         │
                         ▼
                  Search Positions
                         │
                         ▼
                    Evaluate
                         │
                         ▼
                  Choose Best Move
```

This separation makes it possible to improve individual components independently.

For example, the evaluator can be improved without completely rewriting move generation, and the search algorithm can be optimized without changing the board representation.

---

# 28. Current Evaluation Model

The current evaluator is intentionally relatively simple.

It primarily considers:

* Material
* Knight development
* Pawn advancement
* Checkmate

It does **not** currently use more advanced engine techniques such as:

* Piece-square tables
* Mobility evaluation
* King safety evaluation
* Pawn structure analysis
* Passed-pawn evaluation
* Bishop pair bonuses
* Tactical extensions
* Quiescence search
* Transposition tables
* Opening books

This makes the project a good foundation for experimenting with stronger chess-engine techniques.

---

# 29. Possible Future Improvements

There are many ways the engine could be extended.

### Stronger Evaluation

Add:

* Piece-square tables
* King safety
* Mobility
* Center control
* Pawn structure
* Passed pawns
* Bishop pair bonus
* Rook activity
* Endgame-specific evaluation

### Search Improvements

Add:

* Move ordering
* Quiescence search
* Iterative deepening
* Transposition tables
* Principal variation tracking
* Killer-move heuristic
* History heuristic
* Null-move pruning

### Performance

The current engine copies/restores board state frequently during move generation and search.

Performance could potentially be improved with:

* Incremental board updates
* Make/unmake move architecture
* Zobrist hashing
* Bitboards
* Cached attack information

### User Interface

The console interface could eventually be replaced or supplemented with:

* A graphical chessboard
* Mouse controls
* UCI protocol support
* Chess GUI integration
* Online chess support

---

# 30. Learning Goals

This project demonstrates several important C++ and computer-science concepts:

* Object-oriented programming
* Classes and encapsulation
* Arrays
* Vectors
* Strings
* Recursion
* State management
* Algorithm design
* Tree search
* Backtracking
* Performance measurement
* File I/O
* Game-state simulation

The engine is particularly useful as a practical example of how **recursive search algorithms** can be applied to games with a large decision tree.

---

# 31. Summary

This project implements a chess engine from scratch in C++.

The major components are:

| Component      | Responsibility                 |
| -------------- | ------------------------------ |
| `main.cpp`     | Game loop and user interaction |
| `Board`        | Chess board and game rules     |
| `Evaluator`    | Position scoring               |
| `Engine`       | Minimax and Alpha-Beta search  |
| `GameRecorder` | Move history and game saving   |

The engine combines these components to allow a human player to play a complete chess game against an AI.

The current AI searches to depth 5 using **Alpha-Beta pruning**, while the board implementation supports important chess rules including **castling, en passant, promotion, check, checkmate, and stalemate**.

---

## License

Add your preferred license here, for example:

```text
MIT License
```

if you choose to release the project under the MIT License.

---

## Author

Created as a C++ chess-engine project focused on learning and implementing chess programming concepts from scratch.
