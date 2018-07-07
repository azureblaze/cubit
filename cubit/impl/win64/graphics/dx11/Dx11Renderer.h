#pragma once
#include "win64/graphics/Win64Renderer.h"

#include <boost/di/extension/injections/assisted_injection.hpp>
#include <memory>

#include <wrl/client.h>

#include <cubit/graphics/Renderer.h>

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;

namespace di = boost::di;

namespace cubit {

class Logger;
class RenderTarget;
class Config;

namespace impl {
class Dx11RenderTarget;
class Dx11Renderer : public Win64Renderer {
  struct Impl;
  std::unique_ptr<Impl> impl;

 public:
  BOOST_DI_INJECT(Dx11Renderer, Config& config, Logger& logger);

  ~Dx11Renderer();

  virtual Resources& resources() override;

  virtual std::unique_ptr<RenderTarget> createTarget(
      Win64Window& window) override;

  virtual void present(Win64Window& window) override;
};
}  // namespace impl
}  // namespace cubit
