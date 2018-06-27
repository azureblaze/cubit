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
class Win64Window;
class Dx11RenderTarget;
class Dx11VertexShader;
class Dx11PixelShader;
class Dx11VertexBuffer;
class Dx11Renderer : public Win64Renderer {
  struct Impl;
  std::unique_ptr<Impl> impl;

 public:
  BOOST_DI_INJECT(
      Dx11Renderer,
      (named = di::extension::assisted) Win64Window* window,
      Config& config,
      Logger& logger);

  ~Dx11Renderer();

  virtual RenderTarget& getBackBufferTarget() override;

  void drawTriangles(Dx11VertexBuffer& buffer);

  virtual void present() override;
};
}  // namespace impl
}  // namespace cubit
