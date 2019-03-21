#include "../inc/deck.h"
#include <vector>
#include <stdexcept>
#include <iostream>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

namespace coinche
{
  class CoincheDeck : public Deck
  {
    public: 
      CoincheDeck()
      {
	for (int couleur = Coeur; couleur < LastCouleur; couleur++)
	{
	  for (int figure = As; figure < LastFigure; figure++)
	  {
	    m_cartes.push_back({Figure(figure), Couleur(couleur)});
	  }
	}
	assert(m_cartes.size() == LastFigure*LastCouleur);

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
      void swap(size_t idx1, size_t idx2)
      {
	auto temp = m_cartes.at(idx1);
	m_cartes[idx1] = m_cartes.at(idx2);
	m_cartes[idx2] = temp;
      }
      std::vector<Carte> m_cartes;
  };

  Deck * NewDeckCoinche()
  {
    return new CoincheDeck();
  }


}
