#pragma once
#include <cubit/graphics/Resources.h>

#include <functional>
#include <memory>

#include <fruit/fruit.h>

#include <cubit/inject/Factory.h>

namespace cubit {
namespace impl {
class Dx11Device;
class Dx11Material;

class Dx11VertexShader;
class Dx11PixelShader;
class DebugAxis;

class Dx11Resources : public Resources {
  struct Impl;

  std::unique_ptr<Impl> impl;

 public:
  INJECT(Dx11Resources(
      Dx11Device* device,
      Factory<Dx11VertexShader, const ShaderSpec&> vertexShaderFactory,
      Factory<Dx11PixelShader, const ShaderSpec&> pixelShaderFactory,
      Factory<Dx11Material, Dx11Resources*> materialFacotry,
      Factory<DebugAxis, Dx11Resources*> debugAxisFactory));
  ~Dx11Resources();

  virtual const Model* getModel(const std::string& name) override;

  virtual const Material* getMaterial(const std::string& name) override;

  virtual const VertexShader* getVertexShader(const ShaderSpec& spec) override;

  virtual const PixelShader* getPixelShader(const ShaderSpec& spec) override;
};
}  // namespace impl
}  // namespace cubit
