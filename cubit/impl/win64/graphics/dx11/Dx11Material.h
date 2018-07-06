#pragma once
#include <cubit/graphics/Material.h>

#include <functional>
#include <memory>

#include <boost/di.hpp>

#include "Dx11PixelShader.h"
#include "Dx11VertexShader.h"

#include "Dx11Device.h"

namespace cubit {
namespace impl {

class Dx11Material : public Material {
  Dx11Device device;
  Dx11DeviceContext deviceContext;
  std::unique_ptr<Dx11VertexShader> vertexShader;
  std::unique_ptr<Dx11PixelShader> pixelShader;

 public:
  BOOST_DI_INJECT(
      Dx11Material,
      Dx11Device device,
      Dx11DeviceContext deviceContext,
      Dx11VertexShaderFactory vertexShaderFactory,
      Dx11PixelShaderFactory pixelShaderFactory);

  virtual void begin(const Scene& scene) override;

  virtual void end() override {}
};

}  // namespace impl
}  // namespace cubit
