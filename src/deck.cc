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

    std::array<card_t, 8> draw()
    {
      if (_cartes.size() < 8)
        throw std::runtime_error("Pioche une carte quand le deck est vide.");

      std::array<card_t, 8> result;
      for (int i = 0; i < 8; i++)
      {
        auto card = _cartes.back();
        _cartes.pop_back();
        result[i] = card;
      }
      return result;
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
