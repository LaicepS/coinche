#include <algorithm>
#include <cstdio>
#include <random>

enum famille_t
{
  pique,
  coeur,
  carreau,
  trefle,
};

enum hauteur_t
{
  sept,
  huit,
  neuf,
  dix,
  valet,
  dame,
  roi,
  as
};

struct carte_t
{
  famille_t famille;
  hauteur_t hauteur;
};

int main()
{
  carte_t deck[] = {
    {pique, sept},    {pique, huit},   {pique, neuf},   {pique, dix},
    {pique, valet},   {pique, dame},   {pique, roi},    {pique, as},
    {coeur, sept},    {coeur, huit},   {coeur, neuf},   {coeur, dix},
    {coeur, valet},   {coeur, dame},   {coeur, roi},    {coeur, as},
    {carreau, sept},  {carreau, huit}, {carreau, neuf}, {carreau, dix},
    {carreau, valet}, {carreau, dame}, {carreau, roi},  {carreau, as},
    {trefle, sept},   {trefle, huit},  {trefle, neuf},  {trefle, dix},
    {trefle, valet},  {trefle, dame},  {trefle, roi},   {trefle, as},

  };

  std::random_device rd;

  int colors_count[5] =
    {}; // compte le nombre bicolores, tricolores, quadricolores...

  for (int i = 0; i < 1000'000; i++)
  {
    std::shuffle(std::begin(deck), std::end(deck), rd);
    bool colors[4] = {};

    for (int i = 0; i < 8; i++)
    {
      colors[deck[i].famille] |= true;
    }

    int num_colors = std::accumulate(std::begin(colors), std::end(colors), 0);
    colors_count[num_colors]++;
  }

  printf("Mono: %d\n", colors_count[1]);
  printf("Bico: %d\n", colors_count[2]);
  printf("Trico: %d\n", colors_count[3]);
  printf("Quadro: %d\n", colors_count[4]);

  return 0;
}
