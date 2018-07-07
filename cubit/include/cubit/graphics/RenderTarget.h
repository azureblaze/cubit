#pragma once

namespace cubit {
struct Color;
class RenderTarget {
 public:
  virtual void clear(Color color) = 0;

  virtual void bind() = 0;
};
}  // namespace cubit
