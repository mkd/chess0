# Overview
Chess0 is a computer chess program developed in C++ and based on Winglet chess
by Stef Luijten. Chess0 is just an example of chess programming and it's
approximate ELO rating is around ~2200, based on the Elometer test (http://www.elometer.net).

Two main features are still missing or partially implemented:
- Proper cache (using transposition tables)
- Lazy SMP (for parallel search on multi-threaded environments)


# Files
This distribution of Chess0 consists of the following files:
- [README.md](https://github.com/mkd/chess0/blob/master/README.md), the file you are currently reading.
- [copying.txt](https://github.com/mkd/chess0/blob/master/copying.txt), a text file containing the GNU General Public License version 3.
- [TODO](https://github.com/mkd/chess0/blob/master/TODO), a list of improvements and future features (i.e., a backlog).
- [Changelog](https://github.com/mkd/chess0/blob/master/Changelog), a readable list of changes introduced in every version.
- [book_count.sh](https://github.com/mkd/chess0/blob/master/book_count.sh), a script to count the number of opening entries in the book.
- [lines.sh](https://github.com/mkd/chess0/blob/master/lines.sh), a script to count the number of lines in the source code.
- [src](https://github.com/mkd/chess0/blob/master/src), a subdirectory containing the full source code, including a Makefile that can be used to compile Chess0 on Unix-like systems.



# Building Chess0 for your own computer
The default [Makefile](https://github.com/mkd/chess0/blob/master/src/Makefile) in [src](https://github.com/mkd/chess0/blob/master/src)
contains heavy optimizations for Intel-based 64-bit CPUs.

In order to build Chess0 for your own specific CPU, just change the **-march=** setting to your specific CPU type.



# Implementation
Chess0 is fully implemented in C++. I used object orientation in the first
versions to make the code more readable, however C++ objects become a real
bottleneck as the search tree starts to grow (i.e., moves being implemented as
C++ objects create a huge bottleneck in performance). Therefore, the recent
versions of Chess0, although implemented in C++, use C-like structures and
functions whenever the execution can run faster that way.

Chess0's implementation is currently based on
[Winglet](http://aghaznawi.comuf.com/computer%20chess/winglet/) chess by Stef Luijten.



# Features
- **Bitboards:** 
  https://en.wikipedia.org/wiki/Bitboard

- **Principal Variation Search:** 
  https://en.wikipedia.org/wiki/Principal_variation_search

- **Iterative Deepening:**:
  https://en.wikipedia.org/wiki/Iterative_deepening_depth-first_search

- **Alpha-beta pruning:**
  https://en.wikipedia.org/wiki/Alpha–beta_pruning
 
- **Quiescence search:**
  https://en.wikipedia.org/wiki/Quiescence_search

- **Null Move Reductions:** 
  https://en.wikipedia.org/wiki/Null-move_heuristic

- **Trasnposition tables:** 
  https://en.wikipedia.org/wiki/Transposition_table

- **Late Move Reductions (LMR):** 
  https://www.chessprogramming.org/Late_Move_Reductions

- **Simple Machine Learning:** Chess0 can learn from won games on moves that
  actually work, and play them again if similar situations are found.

- **Opening book:** Chess0 comes with a built-in openings book (3500+
  positions). The book is always in use by default, however you can disable
  it with the command 'book off'.
