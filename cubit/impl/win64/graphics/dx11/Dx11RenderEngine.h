#pragma once
#include "win64/graphics/Win64RenderEngine.h"

#include <boost/di/extension/injections/assisted_injection.hpp>
#include <memory>

#include <cubit/graphics/Renderer.h>

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;

namespace di = boost::di;

namespace cubit {
class Logger;
namespace impl {
class Win64Window;
class Dx11RenderEngine : public Win64RenderEngine {
 public:
  BOOST_DI_INJECT(
      Dx11RenderEngine,
      Logger& logger,
      (named = di::extension::assisted) Win64Window* window);

  virtual void present() override;

 private:
  Logger& logger;
  Win64Window* window;

  IDXGISwapChain* swapChain;
  ID3D11Device* device;
  ID3D11DeviceContext* deviceContext;
};
}  // namespace impl
}  // namespace cubit
