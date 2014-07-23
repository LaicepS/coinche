#include "cards.h"
#include <cstddef> // size_t

template<class Card>
struct IDeck
{
	virtual void shuffle() = 0;
	virtual void cut() = 0;
	virtual Card draw() = 0;
	virtual size_t size() = 0;

	virtual ~IDeck() {}
};

IDeck<coinche::Carte> * NewDeckCoinche();
