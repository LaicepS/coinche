#include <cassert>
#include <memory>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

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
      : bids(bids)
  {
  }

  bid_t bid(raise_t min_raise) override
  {
    bid_arg.emplace_back(min_raise);
    bid_calls++;
    if (bid_calls <= bids.size())
      return bids[bid_calls - 1];
    else
      return pass_t{};
  }

  void on_other_bid(bid_t const& bid) override
  {
    other_bids.emplace_back(bid);
  }

  bool coinche(raise_t const& raise) override
  {
    coinche_arg = raise;
    return _coinche;
  }

  bool surcoinche() override
  {
    _surcoinche_calls++;
    return false;
  }

  carte_t pick_card()
  {
    auto top = _hand.back();
    _hand.pop_back();
    return top;
  }

  hand_t _hand;

  size_t bid_calls = 0;
  std::vector<bid_t> bids;
  std::vector<raise_t> bid_arg;
  std::vector<bid_t> other_bids;
  raise_t coinche_arg;
  bool _coinche = false;
  int _surcoinche_calls = 0;
};

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

struct mock_player : player_t
{
  MOCK_METHOD(bid_t, bid, (raise_t min_raise), (override));
  MOCK_METHOD(void, on_other_bid, (bid_t const& bid), (override));
  MOCK_METHOD(bool, coinche, (raise_t const& last_raise), (override));
  MOCK_METHOD(bool, surcoinche, (), (override));
};

unittest(players_can_bid)
{
  std::vector<NiceMock<mock_player>> players(4);

  EXPECT_CALL(players[0], bid(_))
    .Times(2)
    .WillOnce(Return(R80_COEUR))
    .WillOnce(Return(pass_t{}));

  EXPECT_CALL(players[1], bid(_)).Times(1).WillOnce(Return(pass_t{}));
  EXPECT_CALL(players[2], bid(_)).Times(1).WillOnce(Return(pass_t{}));
  EXPECT_CALL(players[3], bid(_)).Times(1).WillOnce(Return(pass_t{}));

  auto coinche_game =
    make_coinche_game(&players[0], &players[1], &players[2], &players[3]);

  coinche_game->run_turn();
}

unittest(bid_resume_after_raise)
{
  std::vector<NiceMock<mock_player>> players(4);
  EXPECT_CALL(players[0], bid(_)).Times(2).WillRepeatedly(Return(pass_t{}));
  EXPECT_CALL(players[1], bid(_)).Times(2).WillRepeatedly(Return(pass_t{}));
  EXPECT_CALL(players[2], bid(_)).Times(2).WillRepeatedly(Return(pass_t{}));
  EXPECT_CALL(players[3], bid(_))
    .Times(2)
    .WillOnce(Return(R80_COEUR))
    .WillOnce(Return(pass_t{}));

  auto coinche_game =
    make_coinche_game(&players[0], &players[1], &players[2], &players[3]);

  coinche_game->run_turn();
}

unittest(raising_updates_minimum_raise)
{
  std::vector<NiceMock<mock_player>> players(4);

  EXPECT_CALL(players[0], bid(R80_COEUR)).Times(1).WillOnce(Return(R80_COEUR));
  EXPECT_CALL(players[1], bid(R90_COEUR)).Times(1).WillOnce(Return(pass_t{}));

  EXPECT_CALL(players[1], bid(R90_COEUR)).Times(1).WillOnce(Return(pass_t{}));
  EXPECT_CALL(players[2], bid(R90_COEUR)).Times(1).WillOnce(Return(pass_t{}));
  EXPECT_CALL(players[3], bid(R90_COEUR)).Times(1).WillOnce(Return(pass_t{}));

  auto coinche_game =
    make_coinche_game(&players[0], &players[1], &players[2], &players[3]);

  coinche_game->run_turn();
}

unittest(players_get_notified_of_bids)
{
  std::vector<mock_player_t> players(4);
  auto coinche_game =
    make_coinche_game(&players[0], &players[1], &players[2], &players[3]);

  coinche_game->run_turn();

  for (int i = 0; i < 4; i++)
  {
    assert(players[i].other_bids.size() == 3);
    assert(std::holds_alternative<pass_t>(players[i].other_bids[0]));
  }
}

unittest(no_more_bids_after_capot)
{
  std::vector<mock_player_t> players(4);
  players[1].bids.emplace_back(R250_PIQUE);

  auto coinche_game =
    make_coinche_game(&players[0], &players[1], &players[2], &players[3]);

  coinche_game->run_turn();
  assert(players[2].bid_arg.size() == 0);
  assert(players[3].bid_arg.size() == 0);
  assert(players[0].bid_arg.size() == 1);
}

unittest(other_players_can_coinche_a_raise)
{
  std::vector<mock_player_t> players(4);
  players[1].bids.emplace_back(R130_TREFLE);

  auto coinche_game =
    make_coinche_game(&players[0], &players[1], &players[2], &players[3]);

  coinche_game->run_turn();

  assert(players[2].coinche_arg == R130_TREFLE);
  assert(players[0].coinche_arg == R130_TREFLE);
}

unittest(coinche_stops_raises)
{
  std::vector<mock_player_t> players(4);

  players[0].bids.emplace_back(R80_PIQUE);
  players[3]._coinche = true;

  auto coinche_game =
    make_coinche_game(&players[0], &players[1], &players[2], &players[3]);
  coinche_game->run_turn();

  assert(players[0].bid_calls == 1);
  assert(players[1].bid_calls == 0);
  assert(players[2].bid_calls == 0);
  assert(players[3].bid_calls == 0);
  assert(players[1].coinche_arg == R80_PIQUE);
  assert(players[1].coinche_arg == R80_PIQUE);
}

unittest(coinche_allow_for_surcoinche)
{
  std::vector<mock_player_t> players(4);

  players[0].bids.emplace_back(R80_PIQUE);
  players[3]._coinche = true;

  auto coinche_game =
    make_coinche_game(&players[0], &players[1], &players[2], &players[3]);
  coinche_game->run_turn();

  assert(players[0]._surcoinche_calls == 1);
  assert(players[2]._surcoinche_calls == 1);
}

int main()
{
  coinche::tester::instance().run_tests();
  return 0;
}
