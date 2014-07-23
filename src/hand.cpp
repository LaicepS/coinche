#include "../inc/hand.h"
#include <vector>

namespace coinche
{
	class Hand : public IHand<Carte>
	{
		public:
			Hand() {}

			void add(Carte card)
			{
				m_cards.push_back(card);
			}

			Carte play() 
			{
				return m_cards.front();
			}

			size_t size() const
			{
				return m_cards.size();
			}

		private:
			std::vector<Carte> m_cards;
	};
}

IHand<coinche::Carte> * GetCoincheHand()
{
	return new coinche::Hand();
}
