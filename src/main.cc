#include <cassert>
#include <memory>
#include <vector>

#include "cards.hh"
#include "deck.hh"
#include "game.hh"
#include "test.hh"

using namespace coinche;

typedef std::pair<carte_t, carte_t> fold_t;

typedef std::vector<carte_t> hand_t;

struct mock_player_t : player_t
{
  mock_player_t(std::vector<bid_t> const& bids = std::vector<bid_t>{pass_t{}})
      : _bids(bids)
  {
  }

  bid_t bid() override
  {
    return _bids[bid_calls++];
  }

  carte_t pick_card()
  {
    auto top = _hand.back();
    _hand.pop_back();
    return top;
  }

  hand_t _hand;

  std::vector<fold_t> folds;
  int bid_calls = 0;
  std::vector<bid_t> _bids;
};

unittest(players_can_bid)
{
  std::vector<mock_player_t> players(4);
  auto coinche_game =
    make_coinche_game(&players[0], &players[1], &players[2], &players[3]);

  coinche_game->run_turn();
  assert(players[0].bid_calls == 1);
  assert(players[1].bid_calls == 1);
  assert(players[2].bid_calls == 1);
  assert(players[3].bid_calls == 1);
}

unittest(bid_resume_after_raise)
{
  std::vector<mock_player_t> players;
  auto add_player = [&](std::vector<bid_t> const& bids) {
    players.emplace_back(bids);
  };

  add_player({pass_t{}, pass_t{}});
  add_player({pass_t{}, pass_t{}});
  add_player({pass_t{}, pass_t{}});
  add_player({raise_t{}, pass_t{}});

  auto coinche_game =
    make_coinche_game(&players[0], &players[1], &players[2], &players[3]);

  coinche_game->run_turn();

  assert(players[0].bid_calls == 2);
  assert(players[1].bid_calls == 2);
  assert(players[2].bid_calls == 2);
  assert(players[3].bid_calls == 2);
  }

int main()
{
  coinche::tester::instance().run_tests();
  return 0;
}
