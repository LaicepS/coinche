CC        = g++

PROG      = coinche

CPPFLAGS  = -std=c++0x

all: $(PROG)

deck.o: deck.cpp
	$(CC) $(CPPFLAGS) -o deck.o -c deck.cpp

main.o: main.cpp deck.o
	$(CC) $(CPPFLAGS) -o main.o -c main.cpp deck.o
	
$(PROG):  main.o 
	$(CC) $(CPPFLAGS) -o coinche main.o deck.o

