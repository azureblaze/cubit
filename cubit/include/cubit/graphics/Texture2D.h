#pragma once

namespace cubit {
class Texture2D {
 public:
  virtual int getWidth() = 0;
  virtual int getHeight() = 0;
};
}  // namespace cubit
