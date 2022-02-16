# This file is part of Chess0, a computer chess program based on Winglet Chess
# by Stef Luijten.
#    
# Copyright (C) 2022 Claudio M. Camacho
#
# Chess0 is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Chess0 is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.



### Figure the operating system name
UNAME = $(shell uname)


### Executable name
APP = chess0


### Defone the path for installation
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin


############################
# SIMD flags
#--------------
# Disable/Add flags as needed
############################
DEFINES =
DEFINES += -DIS_64BIT
ifeq ($(COMP),$(filter $(COMP),gcc clang win icpc))
  DEFINES += -DUSE_AVX2 -mavx2
  DEFINES += -DUSE_SSE41 -msse4.1
  DEFINES += -DUSE_SSE3 -msse3
  DEFINES += -DUSE_SSE2 -msse2
  DEFINES += -DUSE_SSE -msse
endif


### Object files
OBJS = bit.o board.o book.o cache.o cmd.o data.o displaymove.o eval.o fen.o hash.o io.o main.o make.o move.o movgen.o nnue.o nnue_misc.o perft.o search.o see.o timer.o uci.o 


### Compilation flags
CXXFLAGS += -O3 -Ofast -Wall -Wcast-qual -std=c++17 -fno-exceptions -fno-rtti -m64 -mpopcnt -flto $(DEFINES)
DEPENDFLAGS += -std=c++17


### Build targets
#all: $(APP) .depend
all: $(APP)

clean:
	$(RM) $(APP) $(APP).exe *.o

$(APP): $(OBJS)
	$(CXX) -o $@ $(OBJS)
