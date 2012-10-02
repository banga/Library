#include "skip_list.h"
#include <cstdlib>

namespace lib {

double Random() {
  return random() / static_cast<double>(RAND_MAX);
}

}  // namespace lib
