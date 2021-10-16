#include <memory>
#include <vector>

#include "cards.hh"
#include "deck.hh"

using namespace coinche;

typedef std::pair<carte_t, carte_t> fold_t;

typedef std::vector<carte_t> hand_t;

struct player_t
{
  player_t(hand_t const& hand)
      : _hand(hand)
  {
  }

  carte_t pick_card()
  {
    auto top = _hand.back();
    _hand.pop_back();
    return top;
  }

  hand_t _hand;

  std::vector<fold_t> folds;
};

int main()
{
  auto deck = coinche::make_coinche_deck();

  auto draw_hand = [&]() {
    std::vector<carte_t> hand;
    for (int i = 0; i < 8; i++)
      hand.push_back(deck->draw());
    return hand;
  };

  std::vector<player_t> players = {draw_hand(),
                                   draw_hand(),
                                   draw_hand(),
                                   draw_hand()};

  return 0;
}
