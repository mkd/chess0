# Chess0
Chess0 is a computer chess program developed in C++ and based on Winglet chess
by Stef Luijten. Chess0 is just an example of chess programming and it's
approximate ELO rating is around 1730, based on the BT2630 online ELO score test
(http://www.schachcomputer.at/bt2630.htm).

Two main features are still missing or partially implemented:
- Proper cache (using transposition tables)
- Lazy SMP (for parallel search on multi-threaded environments)


## Download
Binaries are available for Chess0. By downloading the ZIP files below, you get
the binary version of the program, which can be run on 64-bit computers with Mac
OSX, GNU/Linux or Windows. The latest version is 1.0-alpha:
- [Chess0 v1.0-alpha OS X 64-bit](https://db.tt/oDCSFVlg)
- [Chess0 v1.0-alpha GNU/Linux 64-bit](https://db.tt/PySyL47x)
- [Chess0 v1.0-alpha Windows 64-bit](https://db.tt/KohKED52)


## Implementation
Chess0 is fully implemented in C++. I used object orientation in the first
versions to make the code more readable, however C++ objects become a real
bottleneck as the search tree starts to grow (i.e., moves being implemented as
C++ objects create a huge bottleneck in performance). Therefore, the recent
versions of Chess0, although implemented in C++, use C-like structures and
functions whenever the execution can run faster that way.

Chess0's implementation is currently based on
[Winglet](http://aghaznawi.comuf.com/computer%20chess/winglet/) chess by Stef Luijten.



## Features
- **Bitboards:** 
  https://en.wikipedia.org/wiki/Bitboard

- **Principal Variation Search** 
  https://en.wikipedia.org/wiki/Principal_variation_search

- **Iterative Deepening**:
  https://en.wikipedia.org/wiki/Iterative_deepening_depth-first_search

- **Alpha-beta pruning:**
  https://en.wikipedia.org/wiki/Alpha–beta_pruning
 
- **Quiescence search:**
  https://en.wikipedia.org/wiki/Quiescence_search

- **Null Move Reductions** 
  https://en.wikipedia.org/wiki/Null-move_heuristic

- **Trasnposition tables** 
  https://en.wikipedia.org/wiki/Transposition_table

- **Late Move Reductions** 
  https://en.wikipedia.org/wiki/Late_Move_Reductions

- **Winboard/XBoard support:** Chess0 supports the XBoard protocol version 2, which means
  that you can play against Chess0 using a graphical user interface (GUI) board.

- **Opening book:** Chess0 comes with a built-in openings book (currently about
  700 learned theory lines). The book is always in use by default, however you
  can disable it with the command 'book off'.
