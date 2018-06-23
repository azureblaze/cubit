#pragma once
#include <string_view>

class Window;

namespace cubit {
class Os {
 public:
  virtual ~Os() = default;

  virtual void messageBox(
      std::string_view title,
      std::string_view message,
      Window* window) = 0;
};
}  // namespace cubit