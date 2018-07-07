#pragma once
namespace cubit {
class RenderTarget;
class Window {
 public:
  virtual ~Window() = default;

  virtual void setSize(int width, int height) = 0;

  virtual void show() = 0;

  virtual int getWidth() = 0;
  virtual int getHeight() = 0;

  virtual RenderTarget& getRenderTarget() = 0;

  virtual void present() = 0;
};
}  // namespace cubit
