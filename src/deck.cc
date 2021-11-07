#include <algorithm>
#include <stdexcept>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "deck.hh"

namespace coinche
{
  struct deck : deck_t
  {
    deck()
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

    card_t draw()
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

    std::vector<card_t> _cartes;
  };

  std::unique_ptr<deck_t> make_coinche_deck()
  {
    return std::make_unique<deck>();
  }
}
