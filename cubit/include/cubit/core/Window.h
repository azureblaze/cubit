#pragma once
namespace cubit {
class Window {
 public:
  virtual ~Window() = default;

  virtual void setSize(int width, int height) = 0;

  virtual void show() = 0;
};
}  // namespace cubit