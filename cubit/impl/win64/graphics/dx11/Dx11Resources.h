#pragma once
#include <cubit/graphics/Resources.h>

#include <functional>
#include <memory>

#include <cubit/inject/Factory.h>

namespace cubit {
namespace impl {

struct Dx11Device;
struct Dx11DeviceContext;
class Dx11Material;

class Dx11VertexShader;
class Dx11PixelShader;

class DebugAxis;
using DebugAxisFactory = std::function<std::unique_ptr<DebugAxis>()>;
using Dx11MaterialFactory = std::function<std::unique_ptr<Dx11Material>()>;

class Dx11Resources : public Resources {
  struct Impl;

  std::unique_ptr<Impl> impl;

 public:
  Dx11Resources(
      Dx11Device device,
      Dx11DeviceContext deviceContext,
      Factory<Dx11VertexShader, const ShaderSpec&> vertexShaderFactory,
      Factory<Dx11PixelShader, const ShaderSpec&> pixelShaderFactory,
      Dx11MaterialFactory materialFacotry,
      DebugAxisFactory debugAxisFactory);
  ~Dx11Resources();

  virtual const Model* getModel(const std::string& name) override;

  virtual const Material* getMaterial(const std::string& name) override;

  virtual const VertexShader* getVertexShader(const ShaderSpec& spec) override;

  virtual const PixelShader* getPixelShader(const ShaderSpec& spec) override;
};
}  // namespace impl
}  // namespace cubit
