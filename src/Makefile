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


### Object files
OBJS = bit.o board.o cache.o cmd.o data.o displaymove.o hash.o make.o move.o movgen.o io.o perft.o main.o search.o fen.o eval.o book.o see.o timer.o uci.o nnue_misc.cpp nnue.cpp


### Compilation flags
#CXXFLAGS += -O3 -Ofast -Wall -Wcast-qual -std=c++17 -march=icelake-client -fno-exceptions -fno-rtti -m64 -mpopcnt -flto
CXXFLAGS += -Wall -fstrict-aliasing -fno-exceptions -fno-rtti  -Wno-unused-variable -Wno-unused-result -std=c++11 -Ofast -fomit-frame-pointer  -DIS_64BIT  -DUSE_AVX2 -mavx2 -DUSE_SSE41 -msse4.1 -DUSE_SSE3 -msse3 -DUSE_SSE2 -msse2 -DUSE_SSE -msse -c -fPIC 
DEPENDFLAGS += -std=c++17


### Build targets
#all: $(APP) .depend
all: $(APP)

install:
	-mkdir -p -m 755 $(BINDIR)
	-cp $(APP) $(BINDIR)
	-strip $(BINDIR)/$(APP)

clean:
	$(RM) $(APP) $(APP).exe *.o .depend *~ 

$(APP): $(OBJS)
	$(CXX) -o $@ $(OBJS)

#.depend:
#	-@$(CXX) $(DEPENDFLAGS) -MM $(OBJS:.o=.cpp) > $@ 2> /dev/null

#-include .depend
