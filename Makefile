CC        = g++

PROG      = coinche

CPPFLAGS  = -std=c++0x

all: $(PROG)


cards.o: cards.cpp
	$(CC) $(CPPFLAGS) -o cards.o -c cards.cpp

deck.o: deck.cpp cards.o
	$(CC) $(CPPFLAGS) -o deck.o -c deck.cpp cards.o

main.o: main.cpp deck.o
	$(CC) $(CPPFLAGS) -o main.o -c main.cpp deck.o
	
$(PROG):  main.o 
	$(CC) $(CPPFLAGS) -o coinche main.o deck.o cards.o

