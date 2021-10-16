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
          _cartes.push_back({Figure(figure), Couleur(couleur)});

      shuffle();
    }

    void shuffle()
    {
      srand(time(NULL));
      int num_cards = _cartes.size();
      for (int i = 0; i < num_cards; i++)
      {
        auto target_idx = i + (rand() % (num_cards - i));
        std::swap(_cartes[i], _cartes[target_idx]);
      }
    }

    void cut()
    {
      srand(time(NULL));
      size_t cutIdx = rand() % _cartes.size();
      decltype(_cartes) lowerCut =
        decltype(_cartes)(_cartes.begin(), _cartes.begin() + cutIdx);
      decltype(_cartes) upperCut =
        decltype(_cartes)(_cartes.begin() + cutIdx, _cartes.end());
      assert(lowerCut.size() + upperCut.size() == _cartes.size());
      _cartes.insert(_cartes.begin(), upperCut.begin(), upperCut.end());
      _cartes.insert(_cartes.begin() + cutIdx,
                     lowerCut.begin(),
                     lowerCut.end());
    }

    carte_t draw()
    {
      if (_cartes.empty())
        throw std::runtime_error("Pioche une carte quand le deck est vide.");

      auto res = _cartes.back();
      _cartes.pop_back();
      return res;
    }

    size_t size()
    {
      return _cartes.size();
    }

    std::vector<carte_t> _cartes;
  };

  std::unique_ptr<coinche_deck_t> make_coinche_deck()
  {
    return std::make_unique<coinche_deck>();
  }


}
