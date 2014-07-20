CC        = g++
CPPFLAGS  = -std=c++0x -W -Wall -Werror
PROG      = coinche

SRCDIR=src
OBJDIR=obj
INCDIR=inc

SRC=$(wildcard $(SRCDIR)/*.cpp)
OBJ=$(SRC:.cpp=.o)

all: $(PROG)

#phony : always evaluated (even if the dependencies are up to date)
.PHONY: clean

%.o: %.cpp
	$(CC) $(CPPFLAGS) -o $@ -c $< 
	
$(PROG):  $(OBJ)
	$(CC) $(CPPFLAGS) -o $@ $^ 

clean:
	rm $(SRCDIR)/*.o
