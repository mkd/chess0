## Chess0 Makefile
## Claudio M. Camacho <claudiomkd@gmail.com>
## Revision: 20160428



# Global definitions
SRC     := src
WIN_EXT := .exe
DBG_EXT := .dbg



# Compiler
CC  := g++
WC  := i686-w64-mingw32-g++

gcc_ver := $(shell g++ --version | awk 'NR==1{print substr($$3,1,1)}')
ifeq ($(gcc_ver),4)
I := -iquote $(SRC)
else
I := -I$(SRC)
endif

CFLAGS  := $(I) -Wall -Ofast -pipe -fomit-frame-pointer -std=c++11
DFLAGS  := $(I) -Wall -O0 -g -DDEBUG



# Directories
INCLUDES := $(SRC)
DIRS     := $(SRC)/ai $(SRC)/application $(SRC)/game $(SRC)/game/board



# Sources
SOURCES   := $(foreach DIR,$(DIRS),$(wildcard $(DIR)/*.cpp))
HEADERS   := $(foreach DIR,$(DIRS),$(filter-out %.cpp,$(wildcard $(DIR)/*)))
OBJECTS   := $(SOURCES:.cpp=.o)
DOBJECTS  := $(SOURCES:.cpp=.dbo)
WOBJECTS  := $(SOURCES:.cpp=.obj)
DEPFILES  := $(SOURCES:.cpp=.d)
DEPFILES  += $(SRC)/utils.d $(SRC)/main.d
OBJECTS   += $(SRC)/utils.o $(SRC)/main.o
DOBJECTS  += $(SRC)/utils.dbo $(SRC)/main.dbo
WOBJECTS  += $(SRC)/utils.obj $(SRC)/main.obj



# Suffixes
.SUFFIXES:
.SUFFIXES: .d .cpp .o .dbo .obj

%.d: %.cpp
	@echo ' Generating deps   $@' && $(CC) $(I) -MM $< | \
	sed '1 s,^[^:]*,$@ $(@:.d=.o) $(@:.d=.dbo) $(@:.d=.obj),' > $@

%.o: %.cpp
	@echo ' Compiling         $@' && $(CC) $(CFLAGS) -c $< -o $@

%.dbo: %.cpp
	@echo ' Compiling [debug] $@' && $(CC) $(DFLAGS) -c $< -o $@

%.obj: %.cpp
	@echo ' Compiling [win32] $@' && $(WC) $(CFLAGS) -c $< -o $@

%:: ;



# Default target and aliases
all: chess0
debug: chess0$(DBG_EXT)
exe: chess0$(WIN_EXT)

chess0: $(OBJECTS)
	@echo ' Linking           $@'
	@$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

chess0$(DBG_EXT): $(DOBJECTS)
	@echo ' Linking   [debug] $@'
	@$(CC) -o $@ $(DOBJECTS)

chess0$(WIN_EXT): $(WOBJECTS)
	@echo ' Linking   [win32] $@'
	@$(WC) -o $@ $(WOBJECTS) $(LDFLAGS)



# Phony declarations
.PHONY: clean doc help



# Rules
doc:
	doxygen

clean:
	@echo -n 'Deleting object files: '
	@rm -fr $(OBJECTS) $(DOBJECTS) $(WOBJECTS) $(DEPFILES)
	@rm -fr chess0 configure-stamp chess0.exe chess0.dbg
	@echo 'done.'

help:
	@echo 'User targets:'; \
	echo ''; \
	echo ' all      - Default target.  Alias for "chess0".'; \
	echo ' chess0   - Build the binary.'; \
	echo ' exe      - Build the binary for Win2k architectures.'; \
	echo ' debug    - Build the debug binary.'; \
	echo ' clean    - Remove object files and binaries.'; \
	echo ''


# Generate dependencies except for these targets
NODEP_TARGETS := clean help

ifeq ($(filter $(NODEP_TARGETS),$(MAKECMDGOALS)),)
-include $(DEPFILES)
endif

