#include <cassert>
#include <chrono>
#include <iostream>
#include <random>

struct bandit_estimation_t {
  double current_estimation = 0;
  int selected_count = 0;
};

using normal_distribution_t = std::normal_distribution<double>;

double epsilon = 0.1;

int main() {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);

  std::vector<std::normal_distribution<double>>
    bandits(10, std::normal_distribution<double>{0, 1});

  std::vector<normal_distribution_t> bandits;
  std::vector<bandit_estimation_t> bandit_estimations;
  for (int i = -5; i < 5; i++) {
    bandits.emplace_back(i, 1);
    bandit_estimations.emplace({});
  }

  std::uniform_real_distribution<double> dice(0., 1.);
  for (int i = 0; i < 10'000; i++) {
    auto choose_best_bandit = dice(generator) > epsilon;
    int bandit_idx = -1;
    if (choose_best_bandit) {
      std::vector<int> best_bandits_indexes;
      double best_bandit_value = -1000;
      for (int i = 0; i < bandits.size(); i++) {
        if (bandit_estimations[i].current_estimation > best_bandit_value) {
          best_bandit_value = bandit_estimations[i].current_estimation;
          best_bandits_indexes = std::vector<int>{i};
        } else if (bandit_estimations[i].current_estimation ==
                   best_bandit_value)
          best_bandits_indexes.push_back(i);

        if (best_bandits_indexes.size() == 1)
          bandit_idx = best_bandits_indexes.front();
        else {
          assert(best_bandits_indexes.size() > 1);
          std::uniform_int_distribution<int>
            referee(0, best_bandits_indexes.size());

          bandit_idx = referee(generator);
        }
      }
    } else {
      std::uniform_int_distribution<int> referee(0, bandits.size());
      bandit_idx = referee(generator);
    }

    auto reward = bandits[bandit_idx](generator);
    auto& curr_estimation = bandit_estimations[bandit_idx];
    curr_estimation.selected_count++;
    curr_estimation.current_estimation =
      curr_estimation.current_estimation
      + 1. / curr_estimation.selected_count
          * (reward - curr_estimation.current_estimation);
  }

  return 0;
}
