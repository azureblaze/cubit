#pragma once
#include <cubit/graphics/PixelShader.h>

#include <functional>
#include <memory>

#include <wrl/client.h>

#include <boost/di.hpp>
#include <boost/di/extension/injections/assisted_injection.hpp>

#include "Dx11Device.h"

struct ID3D11PixelShader;
namespace cubit {
namespace impl {
class Dx11PixelShader : public PixelShader {
  Microsoft::WRL::ComPtr<ID3D11PixelShader> shader;
  Dx11Device device;
  Dx11DeviceContext deviceContext;

 public:
  BOOST_DI_INJECT(
      Dx11PixelShader,
      Dx11Device device,
      Dx11DeviceContext deviceContext,
      (named = boost::di::extension::assisted) const Shader::Spec& spec);
  ~Dx11PixelShader();

  virtual void activate() override;
};

using Dx11PixelShaderFactory =
    std::function<std::unique_ptr<Dx11PixelShader>(const Shader::Spec&)>;
}  // namespace impl
}  // namespace cubit
