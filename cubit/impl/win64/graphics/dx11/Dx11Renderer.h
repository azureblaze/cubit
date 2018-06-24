#pragma once
#include "win64/graphics/Win64Renderer.h"

#include <boost/di/extension/injections/assisted_injection.hpp>
#include <memory>

#include <cubit/graphics/Renderer.h>

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;

namespace di = boost::di;

namespace cubit {
class Logger;
class RenderTarget;
namespace impl {
class Win64Window;
class Dx11RenderTarget;
class Dx11Renderer : public Win64Renderer {
 public:
  BOOST_DI_INJECT(
      Dx11Renderer,
      Logger& logger,
      (named = di::extension::assisted) Win64Window* window);

  ~Dx11Renderer();

  virtual RenderTarget& getBackBufferTarget() override;

  virtual void present() override;

 private:
  Logger& logger;
  Win64Window* window;

  IDXGISwapChain* swapChain;
  ID3D11Device* device;
  ID3D11DeviceContext* deviceContext;

  std::unique_ptr<Dx11RenderTarget> backbufferTarget;
};
}  // namespace impl
}  // namespace cubit
