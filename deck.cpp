#include "deck.h"
#include <vector>
#include <stdexcept>

namespace coinche
{
	class CoincheDeck : public IDeck<Carte>
	{
		public: 
		CoincheDeck()
		{
		}
	
		void shuffle() 
		{
		}

		void cut() 
		{
		}

		Carte pioche() 
		{
			if (m_cartes.empty())
				throw std::runtime_error("Pioche une carte quand le deck est vide.");

			auto res = m_cartes.back();
			m_cartes.pop_back(); 
			return res;
		}

		size_t size() 
		{
			return m_cartes.size();
		}
		private:
		std::vector<Carte> m_cartes;
	};

	IDeck<Carte> * NewDeckCoinche()
	{
		return new CoincheDeck();
	}

}
