#pragma once
#include "win64/graphics/Win64Renderer.h"

#include <memory>

#include <fruit/fruit.h>

#include <cubit/graphics/Renderer.h>

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;

namespace cubit {

class Logger;
class RenderTarget;
class Config;

namespace impl {
class Dx11Device;
class Dx11RenderTarget;
class Dx11Renderer : public Win64Renderer {
  struct Impl;
  std::unique_ptr<Impl> impl;

 public:
  INJECT(Dx11Renderer(Config& config, Logger& logger));

  ~Dx11Renderer();

  virtual Resources& resources() override;

  virtual std::unique_ptr<RenderTarget> createTarget(
      Win64Window& window) override;

  virtual void present(Win64Window& window) override;
};
}  // namespace impl
}  // namespace cubit
