#pragma once
#include <cubit/input/Input.h>

#include <cstdint>

#include <cubit/math/Math.h>

namespace cubit {
class Window;

namespace impl {
class Win64Window;
class Win64Input : public Input {
  bool state[(int)Keys::keyCount];
  bool keyDown[(int)Keys::keyCount];
  bool keyUp[(int)Keys::keyCount];

  Vector2 mousePosition;

  bool mouseCaptured = false;

  Win64Window* window;

 public:
  Win64Input();

  virtual bool getKeyState(Keys key) override;

  virtual bool isKeyUp(Keys key) override;

  virtual bool isKeyDown(Keys key) override;

  virtual Vector2 getMousePosition() override;

  virtual void clearKeyState() override;

  virtual void resetFrame() override;

  virtual void setCaptureMouse(Window* window) override;

  void onKeyDown(int virtualKey);
  void onKeyUp(int virtualKey);
  void onMouseMove(uint64_t lparam);
};
}  // namespace impl
}  // namespace cubit
