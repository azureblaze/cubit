#pragma once
#include <cubit/core/Window.h>
#include <cubit/graphics/renderer.h>

#include <memory>
#include <string>

#include <boost/di.hpp>
#include <boost/di/extension/injections/assisted_injection.hpp>

#include "win64/graphics/Win64Renderer.h"
#include "win64/graphics/dx11/dx11GraphicComponent.h"

using namespace std;

namespace cubit {
class Config;
class Win64Renderer;
namespace impl {
class Win64Application;
class Win64Input;
class Win64Window : public Window {
 public:
  struct Spec {
    std::string windowClass;
    intptr_t applicationInstance;
    Win64Application* application;
  };

  BOOST_DI_INJECT(
      Win64Window,
      (named = boost::di::extension::assisted) const Spec& spec,
      Config& config,
      Win64Renderer& renderer,
      Win64Input& input);
  ~Win64Window();

  virtual void setSize(int width, int height) override {
    this->width = width;
    this->height = height;
  }

  virtual int getWidth() override { return width; };
  virtual int getHeight() override { return height; };
  virtual void show() override;

  intptr_t getHandle() { return handle; }

  virtual RenderTarget& getRenderTarget() override;

  virtual void present() override;

 private:
  friend Win64Application;
  const Spec spec;

  Win64Renderer& renderer;
  Win64Input& input;

  intptr_t handle;

  std::unique_ptr<RenderTarget> renderTarget;

  int width;
  int height;

  intptr_t initialize();

  intptr_t onWindowProc(uint32_t message, intptr_t wParam, intptr_t lParam);
};
using Win64WindowFactory =
    std::function<std::unique_ptr<Win64Window>(Win64Window::Spec)>;
}  // namespace impl
}  // namespace cubit
