#include <iostream>
#include <memory>
#include <vector>

#include "cards.hh"
#include "deck.hh"

using namespace std;
using namespace coinche;

bool is_better(carte_t c0, carte_t c1)
{
  if (c0.figure > c1.figure)
    return true;
  else if (c0.figure < c1.figure)
    return false;

  return c0.color > c1.color;
}

typedef std::pair<carte_t, carte_t> Fold;

int computeScores(vector<Fold> const & folds) {
  int score = 0;

  auto foldScore = [] (Fold const & f) {
    return f.first.figure + f.second.figure; 
  };

  for(auto f: folds)
    score += foldScore(f);

  return score;
}

typedef vector<carte_t> Hand;
struct player_t
{
  player_t(Hand const& startingHand)
      : hand(startingHand)
  {
  }

  carte_t pickCard()
  {
    auto top = hand.back();
    hand.pop_back();
    return top;
  }

  Hand hand;

  vector<Fold> folds;
};

int main()
{
  auto deck = coinche::make_coinche_deck();

  auto draw_hand = [&]() {
    std::vector<carte_t> hand;
    for(int i = 0; i < 10; i++)
      hand.push_back(deck->draw());
    return hand;
  };

  vector<player_t> players = {draw_hand(), draw_hand()};

  for(int i = 0; i < 10; i++) {
    auto cart0 = players[0].pickCard();
    auto cart1 = players[1].pickCard();
    auto best_player = is_better(cart0, cart1) ? 0 : 1;
    players[best_player].folds.push_back({cart0, cart1});
  }

  vector<int> scores = { computeScores(players[0].folds), computeScores(players[1].folds) };
  if (scores[0] > scores[1])
    cout << "Player0 won" << endl;
  else if (scores[0] < scores[1])
    cout << "Player1 won" << endl;
  else
    cout << "Draw" << endl;

  return 0;
}
