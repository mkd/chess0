# Chess0
Chess0 is a computer chess program developed in C++ and based on Winglet chess
by Stef Luijten.

Chess0 approximate ELO:
- Blitz (fast games, <30min) = 1465
- Standard (>30min) = 1590


## Download
Binaries are available for Chess0. By downloading the ZIP files below, you get
the binary version of the program, which can be run on 64-bit computers with Mac
OSX, GNU/Linux or Windows. The latest version is 0.6:
- [Chess0 v0.6 OS X 64-bit](https://db.tt/oDCSFVlg)
- [Chess0 v0.6 GNU/Linux 64-bit](https://db.tt/PySyL47x)
- [Chess0 v0.6 Windows 64-bit](https://db.tt/KohKED52)


## Implementation
Chess0 is fully implemented in C++. I used object orientation in the first
versions to make the code more readable, however C++ objects become a real
bottleneck as the search tree starts to grow (i.e., moves being implemented as
C++ objects create a huge bottleneck in performance). Therefore, the recent
versions of Chess0, although implemented in C++, use C-like structures and
functions whenever the execution can run faster that way.

Chess0's implementation is currently based on
[Winglet](http://aghaznawi.comuf.com/computer%20chess/winglet/) chess by Stef Luijten.



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

- **Principal Variation Search** TBD

- **Null Move Reductions** TBD

- **Trasnposition tables** TBD

- **Late Move Reductions** TBD

- **Cache (transposition tables)** TBD

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
