#pragma once

#include <variant>

namespace coinche {
  struct pass_t{};
  struct raise_t{};

  using bid_t = std::variant<pass_t, raise_t>;
  ;
}
