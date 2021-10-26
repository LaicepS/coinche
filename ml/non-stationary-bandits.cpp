#include <cassert>
#include <chrono>
#include <iostream>
#include <random>

struct bandit_estimation_t {
  double current_estimation = 0;
  int selected_count = 0;
};

using normal_distribution_t = std::normal_distribution<double>;

std::default_random_engine generator;

double epsilon = 0.1;

int choose_best_bandit(
  int bandit_count,
  std::vector<bandit_estimation_t> const& bandit_estimations)
{
  std::vector<int> best_bandits_indexes;
  double best_bandit_value = -1000;
  for (int i = 0; i < bandit_count; i++)
  {
    if (bandit_estimations[i].current_estimation > best_bandit_value)
    {
      best_bandit_value = bandit_estimations[i].current_estimation;
      best_bandits_indexes = std::vector<int>{i};
    }
    else if (bandit_estimations[i].current_estimation == best_bandit_value)
      best_bandits_indexes.push_back(i);

    if (best_bandits_indexes.size() == 1)
      return best_bandits_indexes.front();
    else
    {
      assert(best_bandits_indexes.size() > 1);
      std::uniform_int_distribution<int> referee(0,
                                                 best_bandits_indexes.size()
                                                   - 1);

      return best_bandits_indexes[referee(generator)];
    }
  }
}

int choose_bandit(std::uniform_real_distribution<double>& dice,
                  size_t bandit_count,
                  std::vector<bandit_estimation_t> const& bandit_estimations)
{
  auto choose_best_bandit = dice(generator) > epsilon;
  if (choose_best_bandit)
  {
    return choose_best_bandit(bandit_count, bandit_estimations);
  }
  else
  {
    std::uniform_int_distribution<int> referee(0, bandit_count - 1);
    return referee(generator);
  }
}

int main() {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  generator.seed(seed);

  std::vector<normal_distribution_t> bandits;
  std::vector<bandit_estimation_t> bandit_estimations;
  for (int i = -5; i < 5; i++) {
    bandits.emplace_back(i, 1);
    bandit_estimations.emplace_back();
  }

  std::uniform_real_distribution<double> dice(0., 1.);
  for (int i = 0; i < 10'000; i++) {
    auto bandit_idx = choose_bandit(dice, bandits.size(), bandit_estimations);

    auto reward = bandits[bandit_idx](generator);
    auto& curr_estimation = bandit_estimations[bandit_idx];
    curr_estimation.selected_count++;
    curr_estimation.current_estimation =
      curr_estimation.current_estimation
      + 1. / curr_estimation.selected_count
          * (reward - curr_estimation.current_estimation);
  }

  for (int i = 0; i < bandits.size(); i++)
  {
    std::cout << "est : " << i << " "
              << bandit_estimations[i].current_estimation << std::endl;
  }

  return 0;
}
