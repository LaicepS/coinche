#include "../inc/deck.h"
#include "../inc/cards.h"

#include <memory>
#include <vector>
#include<iostream>

using namespace std;
using namespace coinche;

bool isBetter(Carte c0, Carte c1) {

  if (c0.figure > c1.figure)
    return true;
  else if (c0.figure < c1.figure)
    return false;

  return c0.color > c1.color;
}

typedef std::pair<Carte, Carte> Fold;

int computeScores(vector<Fold> const & folds) {
  int score = 0;

  auto foldScore = [] (Fold const & f) {
    return f.first.figure + f.second.figure; 
  };

  for(auto f: folds)
    score += foldScore(f);

  return score;
}

typedef vector<Carte> Hand;
struct Player
{
  Player(Hand const & startingHand)
    : hand(startingHand) {
  }

  Carte pickCard() {
    auto top = hand.back();
    hand.pop_back();
    return top;
  }

  Hand hand;

  vector<Fold> folds;
};

int main()
{
  auto deck = coinche::NewDeckCoinche();

  auto draw_hand = [&] () {
    std::vector<Carte> h;
    for(int i = 0; i < 10; i++)
      h.push_back(deck->draw());
    return h;
  };

  vector<Player> players = { draw_hand(), draw_hand() };

  for(int i = 0; i < 10; i++) {
    auto cart0 = players[0].pickCard();
    auto cart1 = players[1].pickCard();
    auto bestPlayer = isBetter(cart0, cart1) ? 0 : 1;
    players[bestPlayer].folds.push_back({cart0, cart1});
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
