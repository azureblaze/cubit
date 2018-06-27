#pragma once
#include <cubit/graphics/VertexShader.h>

#include <functional>
#include <memory>

#include <wrl.h>

#include <boost/di.hpp>
#include <boost/di/extension/injections/assisted_injection.hpp>

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
      (named = boost::di::extension::assisted) const Shader::Spec& spec);

  ~Dx11VertexShader();

  virtual void activate() override;
};

using Dx11VertexShaderFactory =
    std::function<std::unique_ptr<Dx11VertexShader>(const Shader::Spec&)>;

}  // namespace impl
}  // namespace cubit
