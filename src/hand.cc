#include <stdexcept>
#include <vector>

#include "hand.hh"

namespace coinche
{
  class hand : public hand_t
  {
  public:
    hand() {}

    void add(carte_t const& card)
    {
      m_cards.push_back(card);
    }

    void play(carte_t const&)
    {
      if (m_cards.size() <= 0)
        throw std::runtime_error("Can not play a card on an empty hand");
    }

    size_t size() const
    {
      return m_cards.size();
    }

  private:
    std::vector<carte_t> m_cards;
  };

  std::unique_ptr<hand_t> GetCoincheHand()
  {
    return std::make_unique<hand>();
  }
} // namespace coinche
