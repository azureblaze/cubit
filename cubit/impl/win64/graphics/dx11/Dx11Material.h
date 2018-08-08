#pragma once
#include <cubit/graphics/Material.h>

#include <functional>
#include <memory>

#include <fruit/fruit.h>

#include "Dx11PixelShader.h"
#include "Dx11VertexShader.h"

#include "Dx11Device.h"

namespace cubit {
namespace impl {

class Dx11Resources;
class Dx11Material : public Material {
  Dx11Device* device;
  Dx11Resources& resources;

  const Dx11VertexShader* vertexShader;
  const Dx11PixelShader* pixelShader;

 public:
  INJECT(Dx11Material(Dx11Device* device, ASSISTED(Dx11Resources*) resources));

  virtual void begin(const Scene& scene) override;

  virtual void end() override {}
};
}  // namespace impl
}  // namespace cubit
