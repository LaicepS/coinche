#include "cards.h"

template<class Card>
struct IDeck
{
	virtual void shuffle() = 0;
	virtual void cut() = 0;
	virtual Card pioche() = 0;
};

IDeck<coinche::Carte> * NewDeck();
