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

const char* famille_string[] = {"pique", "coeur", "carreau", "trefle"};
const char* hauteur_string[] =
  {"sept", "huit", "neuf", "dix", "valet", "dame", "roi", "as"};

void print_hand(carte_t* hand)
{
  for (int i = 0; i < 8; i++)
  {
    printf("Carte %d: %s, %s\n",
           i + 1,
           hauteur_string[hand[i].hauteur],
           famille_string[hand[i].famille]);
  }
}

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

  int num_hands = 10'000'000;
  for (int i = 0; i < num_hands; i++)
  {
    std::shuffle(std::begin(deck), std::end(deck), rd);
    bool familles[4] = {};

    for (int i = 0; i < 8; i++)
    {
      familles[deck[i].famille] |= true;
    }

    int num_colors =
      std::accumulate(std::begin(familles), std::end(familles), 0);
    colors_count[num_colors]++;
  }

  printf("Mono: %d, %f\n",
         colors_count[1],
         colors_count[1] / static_cast<float>(num_hands));
  printf("Bico: %d, %f\n",
         colors_count[2],
         colors_count[2] / static_cast<float>(num_hands));
  printf("Trico: %d, %f\n",
         colors_count[3],
         colors_count[3] / static_cast<float>(num_hands));
  printf("Quadro: %d, %f\n",
         colors_count[4],
         colors_count[4] / static_cast<float>(num_hands));

  return 0;
}
