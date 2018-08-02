#pragma once
#include <cubit/graphics/PixelShader.h>

#include <functional>
#include <memory>

#include <wrl/client.h>

#undef max

#include <fruit/fruit.h>

#include <cubit/inject/Factory.h>

#include "Dx11Device.h"

struct ID3D11PixelShader;
namespace cubit {
namespace impl {
class Dx11PixelShader : public PixelShader {
  Microsoft::WRL::ComPtr<ID3D11PixelShader> shader;
  Dx11Device device;
  Dx11DeviceContext deviceContext;

 public:
  INJECT(Dx11PixelShader(
      Dx11Device device,
      Dx11DeviceContext deviceContext,
      ASSISTED(const ShaderSpec&) spec));
  ~Dx11PixelShader();

  virtual void activate() const override;
};

using Dx11PixelShaderFactory = Factory<Dx11PixelShader, const ShaderSpec&>;
}  // namespace impl
}  // namespace cubit
