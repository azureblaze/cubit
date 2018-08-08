#pragma once
#include <cubit/graphics/VertexShader.h>

#include <functional>
#include <memory>

#include <fruit/fruit.h>

#include <cubit/inject/Factory.h>

#include "ComPtr.h"
#include "Dx11Device.h"

struct ID3D11VertexShader;
struct ID3D11InputLayout;

namespace cubit {
namespace impl {
class Dx11VertexShader : public VertexShader {
  ComPtr<ID3D11VertexShader> shader;
  ComPtr<ID3D11InputLayout> layout;
  Dx11Device* device;

 public:
  INJECT(
      Dx11VertexShader(Dx11Device* device, ASSISTED(const ShaderSpec&) spec));

  ~Dx11VertexShader();

  virtual void activate() const override;
};

using Dx11VertexShaderFactory = Factory<Dx11VertexShader, const ShaderSpec&>;

}  // namespace impl
}  // namespace cubit
