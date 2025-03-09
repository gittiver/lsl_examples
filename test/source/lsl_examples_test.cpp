#include "lib.hpp"

auto main() -> int
{
  auto const lib = library {};

  return lib.name == "lsl_examples" ? 0 : 1;
}
