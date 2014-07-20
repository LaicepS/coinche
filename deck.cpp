#include "deck.h"
#include <vector>
#include <stdexcept>
#include <iostream>
#include <assert.h>

namespace coinche
{
	class CoincheDeck : public IDeck<Carte>
	{
		public: 
			CoincheDeck()
			{
				for (int figure = As; figure < LastFigure; figure++)
				{
					for (int couleur = Coeur; couleur < LastCouleur; couleur++)
					{
						m_cartes.push_back(std::make_pair(Figure(figure), Couleur(couleur)));
					}
				}
				shuffle();
				assert(m_cartes.size() == 32);
				for (Carte carte : m_cartes)
				{
					std::cout << std::get<FIGURE>(carte) << " " << std::get<COULEUR>(carte) << std::endl;
				}
			}

			void shuffle() 
			{
			}

			void cut() 
			{
			}

			Carte draw() 
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
}

IDeck<coinche::Carte> * NewDeckCoinche()
{
	return new coinche::CoincheDeck();
}


