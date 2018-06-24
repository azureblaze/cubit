#pragma once
namespace cubit {
class Renderer;
class Window {
 public:
  virtual ~Window() = default;

  virtual void setSize(int width, int height) = 0;

  virtual void show() = 0;

  virtual int getWidth() = 0;
  virtual int getHeight() = 0;

  virtual Renderer& getRenderer() = 0;
};
}  // namespace cubit
