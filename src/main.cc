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

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Truly;

struct mock_player_t : player_t
{
  MOCK_METHOD(bid_t, bid, (raise_t min_raise), (override));
  MOCK_METHOD(void, on_bid, (bid_t const& bid), (override));
  MOCK_METHOD(bool, coinche, (raise_t const& last_raise), (override));
  MOCK_METHOD(bool, surcoinche, (), (override));
  MOCK_METHOD(void, on_coinche, (raise_t const&, int player_idx), (override));
  MOCK_METHOD(void, on_surcoinche, (int player_idx), (override));
};

unittest(players_can_bid)
{
  std::vector<NiceMock<mock_player_t>> players(4);

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
  std::vector<NiceMock<mock_player_t>> players(4);
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
  std::vector<NiceMock<mock_player_t>> players(4);

  EXPECT_CALL(players[0], bid(R80_COEUR)).Times(1).WillOnce(Return(R80_COEUR));
  EXPECT_CALL(players[0], bid(R90_COEUR)).Times(1).WillOnce(Return(pass_t{}));

  EXPECT_CALL(players[1], bid(R90_COEUR)).Times(1).WillOnce(Return(pass_t{}));
  EXPECT_CALL(players[2], bid(R90_COEUR)).Times(1).WillOnce(Return(pass_t{}));
  EXPECT_CALL(players[3], bid(R90_COEUR)).Times(1).WillOnce(Return(pass_t{}));

  auto coinche_game =
    make_coinche_game(&players[0], &players[1], &players[2], &players[3]);

  coinche_game->run_turn();
}

unittest(players_get_notified_of_bids)
{
  auto isPass = [](bid_t const& bid) {
    return std::holds_alternative<pass_t>(bid);
  };

  std::vector<NiceMock<mock_player_t>> players(4);

  for (int i = 0; i < 4; i++)
    ON_CALL(players[i], bid(_)).WillByDefault(Return(pass_t{}));

  EXPECT_CALL(players[0], on_bid(Truly(isPass))).Times(3);
  EXPECT_CALL(players[1], on_bid(Truly(isPass))).Times(3);
  EXPECT_CALL(players[2], on_bid(Truly(isPass))).Times(3);
  EXPECT_CALL(players[3], on_bid(Truly(isPass))).Times(3);

  auto coinche_game =
    make_coinche_game(&players[0], &players[1], &players[2], &players[3]);

  coinche_game->run_turn();
}

unittest(no_more_bids_after_capot)
{
  std::vector<NiceMock<mock_player_t>> players(4);
  ON_CALL(players[0], bid(_)).WillByDefault(Return(pass_t{}));
  ON_CALL(players[0], bid(_)).WillByDefault(Return(R250_PIQUE));
  EXPECT_CALL(players[2], bid(_)).Times(0);
  EXPECT_CALL(players[3], bid(_)).Times(0);

  auto coinche_game =
    make_coinche_game(&players[0], &players[1], &players[2], &players[3]);

  coinche_game->run_turn();
}

unittest(other_players_can_coinche_a_raise)
{
  std::vector<NiceMock<mock_player_t>> players(4);
  ON_CALL(players[0], bid(_)).WillByDefault(Return(pass_t{}));
  ON_CALL(players[1], bid(_)).WillByDefault(Return(R130_TREFLE));

  EXPECT_CALL(players[2], coinche(R130_TREFLE))
    .Times(1)
    .WillOnce(Return(false));

  EXPECT_CALL(players[0], coinche(R130_TREFLE)).Times(1).WillOnce(Return(true));

  auto coinche_game =
    make_coinche_game(&players[0], &players[1], &players[2], &players[3]);

  coinche_game->run_turn();
}

unittest(coinche_stops_raises)
{
  std::vector<NiceMock<mock_player_t>> players(4);

  ON_CALL(players[0], bid(_)).WillByDefault(Return(R80_PIQUE));
  ON_CALL(players[3], coinche(R80_PIQUE)).WillByDefault(Return(true));

  EXPECT_CALL(players[1], bid(_)).Times(0);
  EXPECT_CALL(players[2], bid(_)).Times(0);
  EXPECT_CALL(players[3], bid(_)).Times(0);
  EXPECT_CALL(players[1], coinche(R80_PIQUE)).Times(1).WillOnce(Return(false));

  auto coinche_game =
    make_coinche_game(&players[0], &players[1], &players[2], &players[3]);
  coinche_game->run_turn();
}

unittest(coinche_allows_for_surcoinche)
{
  std::vector<NiceMock<mock_player_t>> players(4);

  ON_CALL(players[0], bid(_)).WillByDefault(Return(R80_PIQUE));
  ON_CALL(players[3], coinche(_)).WillByDefault(Return(true));

  EXPECT_CALL(players[0], surcoinche()).Times(1).WillOnce(Return(false));
  EXPECT_CALL(players[2], surcoinche()).Times(1);

  auto coinche_game =
    make_coinche_game(&players[0], &players[1], &players[2], &players[3]);
  coinche_game->run_turn();
}

unittest(coinche_is_notified)
{
  std::vector<NiceMock<mock_player_t>> players(4);
  ON_CALL(players[0], bid(_)).WillByDefault(Return(R100_PIQUE));
  ON_CALL(players[3], coinche(R100_PIQUE)).WillByDefault(Return(true));

  for (int i = 0; i < 3; i++)
    EXPECT_CALL(players[i], on_coinche(R100_PIQUE, 3)).Times(1);

  auto coinche_game =
    make_coinche_game(&players[0], &players[1], &players[2], &players[3]);
  coinche_game->run_turn();
}

unittest(surcoinche_is_notified)
{
  std::vector<NiceMock<mock_player_t>> players(4);
  ON_CALL(players[0], bid(_)).WillByDefault(Return(pass_t{}));
  ON_CALL(players[1], bid(_)).WillByDefault(Return(R80_TREFLE));
  ON_CALL(players[2], coinche(R80_TREFLE)).WillByDefault(Return(false));
  ON_CALL(players[0], coinche(R80_TREFLE)).WillByDefault(Return(true));
  ON_CALL(players[1], surcoinche()).WillByDefault(Return(false));
  ON_CALL(players[3], surcoinche()).WillByDefault(Return(true));

  EXPECT_CALL(players[0], on_surcoinche(3)).Times(1);
  EXPECT_CALL(players[1], on_surcoinche(3)).Times(1);
  EXPECT_CALL(players[2], on_surcoinche(3)).Times(1);

  auto coinche_game =
    make_coinche_game(&players[0], &players[1], &players[2], &players[3]);
  coinche_game->run_turn();
}

int main()
{
  coinche::tester::instance().run_tests();
  return 0;
}
