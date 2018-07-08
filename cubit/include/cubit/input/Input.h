#pragma once

#include "Keys.h"

namespace cubit {
class Vector2;
class Window;
class Input {
 public:
  virtual bool getKeyState(Keys key) = 0;
  virtual bool isKeyUp(Keys key) = 0;
  virtual bool isKeyDown(Keys key) = 0;

  virtual Vector2 getMousePosition() = 0;

  virtual void clearKeyState() = 0;
  virtual void resetFrame() = 0;

  virtual void setCaptureMouse(Window* window) = 0;
};
};  // namespace cubit
