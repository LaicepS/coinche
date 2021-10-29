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
  mock_player_t(std::vector<bid_t> const& bids = {})
      : _bids(bids)
  {
  }

  bid_t bid(std::optional<raise_t> min_raise) override
  {
    _bid_arg.emplace_back(min_raise);
    bid_calls++;
    if (bid_calls <= _bids.size())
      return _bids[bid_calls - 1];
    else
      return pass_t{};
  }

  void on_other_bid(bid_t const& bid) override
  {
    _other_bids.emplace_back(bid);
  }

  bool coinche(raise_t const& raise) override
  {
    _coinche_arg = raise;
    return _coinche;
  }

  carte_t pick_card()
  {
    auto top = _hand.back();
    _hand.pop_back();
    return top;
  }

  hand_t _hand;

  size_t bid_calls = 0;
  std::vector<bid_t> _bids;
  std::vector<std::optional<raise_t>> _bid_arg;
  std::vector<bid_t> _other_bids;
  raise_t _coinche_arg;
  bool _coinche = false;
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
  std::vector<mock_player_t> players(4);
  players[3]._bids.emplace_back(R80_COEUR);

  auto coinche_game =
    make_coinche_game(&players[0], &players[1], &players[2], &players[3]);

  coinche_game->run_turn();

  assert(players[0].bid_calls == 2);
  assert(players[1].bid_calls == 2);
  assert(players[2].bid_calls == 2);
  assert(players[3].bid_calls == 2);
}

unittest(raising_updates_minimum_raise)
{
  std::vector<mock_player_t> players(4);
  players[0]._bids.emplace_back(R80_COEUR);
  players[0]._bids.emplace_back(pass_t{});

  auto coinche_game =
    make_coinche_game(&players[0], &players[1], &players[2], &players[3]);

  coinche_game->run_turn();

  assert(players[0]._bid_arg[0] == std::optional<raise_t>{});
  assert(players[0]._bid_arg[1] == R90_COEUR);
  assert(players[1]._bid_arg[0] == R90_COEUR);
}

unittest(players_get_notified_of_bids)
{
  std::vector<mock_player_t> players(4);
  auto coinche_game =
    make_coinche_game(&players[0], &players[1], &players[2], &players[3]);

  coinche_game->run_turn();

  for (int i = 0; i < 4; i++)
  {
    assert(players[i]._other_bids.size() == 3);
    assert(std::holds_alternative<pass_t>(players[i]._other_bids[0]));
  }
}

unittest(no_more_bids_after_capot)
{
  std::vector<mock_player_t> players(4);
  players[1]._bids.emplace_back(R250_PIQUE);

  auto coinche_game =
    make_coinche_game(&players[0], &players[1], &players[2], &players[3]);

  coinche_game->run_turn();
  assert(players[2]._bid_arg.size() == 0);
  assert(players[3]._bid_arg.size() == 0);
  assert(players[0]._bid_arg.size() == 1);
}

unittest(other_players_can_coinche_a_raise)
{
  std::vector<mock_player_t> players(4);
  players[1]._bids.emplace_back(R130_TREFLE);

  auto coinche_game =
    make_coinche_game(&players[0], &players[1], &players[2], &players[3]);

  coinche_game->run_turn();

  assert(players[2]._coinche_arg == R130_TREFLE);
  assert(players[0]._coinche_arg == R130_TREFLE);
}

unittest(coinche_stops_raises)
{
  std::vector<mock_player_t> players(4);

  players[0]._bids.emplace_back(R80_PIQUE);
  players[1]._coinche = true;

  auto coinche_game =
    make_coinche_game(&players[0], &players[1], &players[2], &players[3]);
  coinche_game->run_turn();

  assert(players[0].bid_calls == 1);
  assert(players[1].bid_calls == 0);
  assert(players[2].bid_calls == 0);
  assert(players[3].bid_calls == 0);
  assert(players[1]._coinche_arg == R80_PIQUE);
}

int main()
{
  coinche::tester::instance().run_tests();
  return 0;
}
