#include <iostream>
#include <stdexcept>
#include <vector>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "deck.hh"

namespace coinche
{
  class coinche_deck_t : public deck_t
  {
  public:
    coinche_deck_t()
    {
      for (int couleur = Coeur; couleur < LastCouleur; couleur++)
      {
        for (int figure = As; figure < LastFigure; figure++)
        {
          m_cartes.push_back({Figure(figure), Couleur(couleur)});
        }
      }
      assert(m_cartes.size() == LastFigure * LastCouleur);

      shuffle();
      }

      void shuffle()
      {
	srand(time(NULL));
	for (int i = 0; i < 1000; i++)
	{
	  swap(rand() % m_cartes.size(), rand() % m_cartes.size());
	}
      }

      void cut()
      {
	srand(time(NULL));
	size_t cutIdx = rand() % m_cartes.size();
	decltype(m_cartes) lowerCut = decltype(m_cartes)(m_cartes.begin(), m_cartes.begin() + cutIdx);
	decltype(m_cartes) upperCut = decltype(m_cartes)(m_cartes.begin() + cutIdx, m_cartes.end());
	assert(lowerCut.size() + upperCut.size() == m_cartes.size());
	m_cartes.insert(m_cartes.begin(),upperCut.begin(), upperCut.end());
	m_cartes.insert(m_cartes.begin() + cutIdx, lowerCut.begin(), lowerCut.end());
      }

      carte_t draw()
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
      void swap(size_t idx1, size_t idx2)
      {
	auto temp = m_cartes.at(idx1);
	m_cartes[idx1] = m_cartes.at(idx2);
	m_cartes[idx2] = temp;
      }
      std::vector<carte_t> m_cartes;
  };

  std::unique_ptr<deck_t> make_coinche_deck()
  {
    return std::make_unique<coinche_deck_t>();
  }


}
