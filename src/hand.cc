#include <stdexcept>
#include <vector>

#include "hand.hh"

namespace coinche
{
	class Hand : public IHand<Carte>
	{
		public:
			Hand() {}

			void add(Carte const & card)
			{
				m_cards.push_back(card);
			}

			void play(Carte const &) 
			{
				if (m_cards.size() <= 0)
					throw std::runtime_error("Can not play a card on an empty hand");
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
