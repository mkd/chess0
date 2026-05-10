# Chess0
**DISCLAIMER: My family and my mental health need me, so this project is currently abandoned. If you have any question regarding Chess0 or Chess0x, email me to claudiomkd (at) gmail.com.**

Chess0 is a simple computer chess program developed in C++ for programming learning purposes.


## Purpose
Chess0 is a computer chess program, which aims at providing a simple chess
engine with a fully understandable source code and offering the basic tools for
analyzing the behavior of different AI implementations. Chess0 is an example of
simple AI for playing two-player turn-based games, and it provides a generic AI
interface (abstract class) which can be used by other programmers to implement
their own AI engine creating a new subclass of Chess0's AI interface. The two
main components to be implemented for a new AI engine are: 1) evaluation
function; and 2) tree search. Move generation is done by another part of the
application and it is not extensible at the moment.

Chess0 was developed as part of a Bachelor's Thesis project for Helsinki
Metropolia University of Applied Science (Finland), for the Bachelor's Degree in
Computer Science. The main goal of this open source project is to show software
developers a "good example" of well-structured application and how to structure
an application in C++. Chess0 has not been designed with speed and performance
in mind. Instead, the main focus is on source code readability, maintainability
and extendibility, with a special focus on learning programming.

You can read the complete thesis about Adaptive AI for Computer Chess
here: http://bit.ly/1NtNVJT


## Implementation
Chess0 is fully implemented in C++. There are a few optimizations (e.g.,
bitboards) which are developed with non-pure C++ or rather C-like properties,
to make the application run faster at critical points.

Chess0 has been designed to allow extendibility, which means that the
application can use multiple heuristic evaluation engines, different board
representations, different games rules, etc. Additionally, all different
implementations of representation can be used simultaneously at runtime. For
instance, Chess0 comes with a generic AI class out of which different evaluation
engines can be programmed and "plugged-in" into the application. The main chess
engine behind Chess0 is called "Adaptive AI" and it has its own class under
"src/ai/adaptive".

Chess0 uses a heuristic evaluation function, a minimax-like algorithm and an
alpha-beta pruning technique for speeding up the decision tree search
operations. In addition to this, Chess0's adaptive AI engine supports
features such as randomization, dynamic heuristics and quiescence search,
which dramatically improve the behavior of the application compared to
other master-level chess players.

Chess0's current ELO rating (https://en.wikipedia.org/wiki/Elo_rating_system):
- Fast games (blitz): 1264
- Standard games: 1240


## Evaluation Function
Chess0's heuristic evaluation is evaluated in two parts: 1) material evaluation;
and 2) positional evaluation. Material evaluation is specified inside the
generic ai.cpp implementation, however positional evaluation has to be
implemented separately for each specific AI engine. By default, Chess0 engine is
called Adaptive, and the positional evaluation function is described in
adaptive_position.cpp.

evaluation = evalMaterial() + evalPosition()

- Piece values:
.- Pawn   1.00
.- Knight 3.20
.- Bishop 3.30
.- Rook   5.00
.- Queen  9.20
.- King 200.00

- Positional tables: depending on the phase of the game, each piece will get an
  extra/minus set of points depending on which square they are placed. The
  tables for each piece and square have been borrowed from here:
  http://www.chessbin.com/post/Chess-Board-Evaluation

- Positional rewards/penalties:
  - Reward for mobility: each piece gets no. of moves / 2 extra centipawns
  - King shield:
    - -0.10 penalty for each pawn 1-square away from the castle
    - -0.40 penalty for each pawn 2-squares (or more) away from castle
  - -0.10 penalty for king on open file
  - -0.10 penalty for king with very low mobility
  - +0.40 reward for castled king
  - -0.30 penalty for king losing right to castle
  - -0.10 penalty for king under check (in end-game)
  - -0.75 penalty for king under check (in mid-game)
  - -0.10 penalty for queen moved in the opening
  - +0.20 reward for rook on open file
  - -0.10 penalty for rook moving before castling
  - +0.10 reward for pair of bishops at end-game
  - -0.10 penatly for pair of knights at end-game
  - -0.16 penatly for doubled pawn
  - -0.20 penalty for isolated pawn
  - +0.50 reward for passed pawn
  - -0.15 penalty for rook pawn
  - +0.10 reward for tempo (player's turn)
  - +0.10 reward for pair of bishops


## Supported Features
- **Iterative Deepening**: Chess0 uses a technique called 'iterative deepening'
  to first find the best potential moves at shallow depths and then, using a
  sorting algorithm, flags the best candidate moves to be the first ones to be
  searched at higher depths. Although slower in theory, iterative deepening
  makes Chess0 2-3x faster thanks to move ordering before every search.
  More information:
  https://en.wikipedia.org/wiki/Iterative_deepening_depth-first_search

- **Negamax:** Chess0 uses a simplified version of the minimax algorithm, called
  negamax, which is basically a more elegant solution to achieve the same
  result. The difference with minimax is that, on every ply, the search is
  negated for the opponent player, thus achievining the same results as if the
  program was calling two different functions, one per each player.
  More info: https://en.wikipedia.org/wiki/Negamax

- **Alpha-beta pruning:** Chess0 heavily relies on alpha-beta pruning to
  dramatically reduce the amount of moves in the search tree. Alpha-beta pruning
  makes Chess0 run 1-5x faster, depending on the order of the moves being
  analized.
  More info: https://en.wikipedia.org/wiki/Alpha–beta_pruning
 
- **Quiescence search:** this feature allows Chess0 to have a variable tree search
  depth, depending if the board situation is stable or not. The quiescence
  search basically searches for a quiet node in the decision tree, meaning that
  the move under analysis must not be a capture, a check nor a promotion. If the
  move is one of those critical moves, then the quiescence will continue
  iterating by calling itself. However, if the quiescence search finds a node
  whose move is not one of the critical moves, then it will return the normal
  evaluation, without recursing over itself anymore.
  More info: https://en.wikipedia.org/wiki/Quiescence_search

- **Randomization:** Chess0 has a configurable randomization factor (only at
  compilation time) that lets the computer choose different moves on two exact
  same situations. This flag is useful for testing or when Chess0 is being
  played many times, so that the computer will play a bit differently every
  time.

- **Dynamic heuristics:** Chess0 easily recognizes different situations in the
  board, specially between opening, middle-game and end-game. Therefore, the
  computer can play differently accordingly. For example, piece development is
  more important at the opening, whereas King being active is more important at
  the end of the game. All these and more are "understood" by Chess0 and put
  into play according to the existing situation on the board.

- **MVV/LVA (Most Valuable Victim / Least Valuable Attacker):** For move
  ordering, besides many other techniques, Chess0 also uses an algorithm for
  ordering the moves taking into account the fact that less-valuable pieces
  attacking higher-value pieces may return a higher score. For example, if in
  the list of moves there is such a move that a pawn may capture a queen,
  then that move will be most likely to return a high score, since the pawn
  is the least valuable piece on the board, and the queen is the most valuable
  piece on the board. This boosts the performance of the search, since probable
  higher-score moves are evaluated before probable lower-score moves, thus
  speeding up the alpha-beta pruning, as the non-interesting parts of the tree
  are cutoff early in the search process. More info:
  https://chessprogramming.wikispaces.com/MVV-LVA

- **Bitboards:** Chess0 has a very simplistic and rudimentary way of using
  BitBoards. To begin with, Chess0 does not rely entirely on BitBoards, but
  rather use some "selected" BitBoards to speed up certain calculations. The
  ultimate goal is to transition Chess0 to BitBoard representation as much as
  possible, to the extent where array representation is not needed any more. The
  benefits of using only BitBoards could be a move generation and search
  algorithms 3-5x faster than the current engine's speed.
  More info: https://en.wikipedia.org/wiki/Bitboard

- **XBoard support:** Chess0 supports the XBoard protocol version 2, which means
  that you can play against Chess0 using a graphical user interface (GUI) board.
  However, there are two important things to take into account when playing
  against Chess0 using an XBoard-compatible GUI: 1) Chess0 only supports SAN
  notation and XBoard protocol v2; and 2) time controls are not yet implemented in
  Chess0. Regarding point 1), Chess0 is not supported by Cutechess for instance,
  which relies on XBoard protocol v1 and ignores SAN notation. In addition to
  this, Chess0 does not support ICS protocol yet, meaning that you cannot use
  Chess0 on an Internet Chess Server to play against others.

- **Opening book:** Chess0 comes with a built-in openings book (currently about
  1000 learned theory lines). The book is always in use by default, however you
  can disable it with the command 'book off'.


## Useful commands
- **cache**: Let the computer use the transposition tables to find previously
  searched positions faster. This typically makes the engine more powerful in
  middle and end-game positions.  Please note that using transposition tables
  can take a few hundreds of Megabytes for a ~1h game.

- **edit**: Enter in position editing mode. The program will first wipe all
  the pieces from the board and ask you for entering the white pieces. These
  pieces are entered one by one (separeted by pressing Enter) and according
  to the format PIECE+COLUMN+ROW (e.g. Ke2). When the white pieces are done,
  then enter '.' (dot) and press Enter, so the black pieces are asked to be
  entered. When the black pieces are entered, then enter '#' (hash) and
  press Enter. After that, you will be asked whose turn is to move (white or
  black). Then press Enter once again to exit from the position editing mode.

- **info**: Display some useful information about the current game, including
  the phase of the game, the side to move, the last move on the board, the
  overall evaluation and the material balance.

- **save/load**: save or load the current board to/from a Chess0 Board Position
  file (.c0b). These commands are very useful to debug or examine a certain board
  position that is interesting. Please note that the position file .c0b doesn't
  know the moves by which the position was reached, nor castling rights nor
  empassants.

- **log**: Enable or disable logging to a disk file. By issuing this command
  without parameters, chess0 will display the current status of the logging
  setting. If you specify a parameter different than 'off', Chess0 will start
  writing log output to a file with the name given in the parameter. On the
  other hand, if you give the parameter 'off', the logging support will be
  disabled.

- **solve**: Start thinking how to solve the current board. This mode puts
  the computer to play both sides and makes it try to solve the current
  situation on the board up to some depth. If no depth is given, the computer
  will search the solution forever (unless it finds it). Otherwise, it will try
  to solve the problem and it will give up when it reaches the given depth.

- **test**: Test either the number of moves that can be done and undone per
  second (without calling evaluation), the number of nodes that can be
  evaluated per second, and perform a Perft() test which is a standard moves
  test for computer chess programs to test that the move generator works
  correctly. If no argument is given, all three tests are performed.


## Further Development
Chess0 is a working prototype that follows all the actual chess rules, including
"empassant" pawn capture and the draw-by-repetition rules at the end of the
game. However, Chess0 does not play at a very good level, due to a very drafty
heuristic evaluation function. There are a few key areas where Chess0 needs
heavy development, in order to become a "better" chess player:

- Implement multi-thread: this feature will allow Chess0 to play 2-4x
  faster, depending on the number of cores available on the device. Currently,
  Chess0 is single-threaded and therefore it uses only one core on every device.

- Full Bitboard-based representation, move generation and evaluation.

- Think during opponent's time (ponering).

- PGN file support.

- Long-term learning support.


## Bonus: How to Develop a Custom AI Engine for Chess0
TBD: Show how to implement a really simple custom AI engine for Chess0, which
simply returns a random move every time it is asked.
