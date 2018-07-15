#pragma once
#include <cubit/graphics/VertexShader.h>

#include <functional>
#include <memory>

#include <wrl.h>

#include <boost/di.hpp>
#include <boost/di/extension/injections/assisted_injection.hpp>

#include <cubit/inject/Factory.h>

#include "Dx11Device.h"

struct ID3D11VertexShader;
struct ID3D11InputLayout;

struct ID3D11Device;

namespace cubit {
namespace impl {
class Dx11VertexShader : public VertexShader {
  Microsoft::WRL::ComPtr<ID3D11VertexShader> shader;
  Microsoft::WRL::ComPtr<ID3D11InputLayout> layout;
  Dx11Device device;
  Dx11DeviceContext deviceContext;

 public:
  BOOST_DI_INJECT(
      Dx11VertexShader,
      Dx11Device device,
      Dx11DeviceContext deviceContext,
      (named = boost::di::extension::assisted) const ShaderSpec& spec);

  ~Dx11VertexShader();

  virtual void activate() const override;
};

using Dx11VertexShaderFactory = Factory<Dx11VertexShader, const ShaderSpec&>;

}  // namespace impl
}  // namespace cubit
