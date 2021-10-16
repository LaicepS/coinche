#include <iostream>
#include <stdexcept>
#include <vector>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "deck.hh"

namespace coinche
{
  struct coinche_deck : coinche_deck_t
  {
    coinche_deck()
    {
      for (int couleur = Coeur; couleur < LastCouleur; couleur++)
        for (int figure = As; figure < LastFigure; figure++)
          m_cartes.push_back({Figure(figure), Couleur(couleur)});

      shuffle();
    }

    void shuffle()
    {
      srand(time(NULL));
      int num_cards = m_cartes.size();
      for (int i = 0; i < num_cards; i++)
      {
        auto target_idx = i + (rand() % (num_cards - i));
        std::swap(m_cartes[i], m_cartes[target_idx]);
      }
    }

    void cut()
    {
      srand(time(NULL));
      size_t cutIdx = rand() % m_cartes.size();
      decltype(m_cartes) lowerCut =
        decltype(m_cartes)(m_cartes.begin(), m_cartes.begin() + cutIdx);
      decltype(m_cartes) upperCut =
        decltype(m_cartes)(m_cartes.begin() + cutIdx, m_cartes.end());
      assert(lowerCut.size() + upperCut.size() == m_cartes.size());
      m_cartes.insert(m_cartes.begin(), upperCut.begin(), upperCut.end());
      m_cartes.insert(m_cartes.begin() + cutIdx,
                      lowerCut.begin(),
                      lowerCut.end());
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

    std::vector<carte_t> m_cartes;
  };

  std::unique_ptr<coinche_deck_t> make_coinche_deck()
  {
    return std::make_unique<coinche_deck>();
  }


}
