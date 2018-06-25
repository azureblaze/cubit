#pragma once
#include <cubit/graphics/VertexShader.h>

#include <string>

#include <wrl.h>

struct ID3D11VertexShader;
struct ID3D11Device;

namespace cubit {
namespace impl {
class Dx11VertexShader : public VertexShader {
  Microsoft::WRL::ComPtr<ID3D11VertexShader> shader;
  ID3D11Device* device;

 public:
  Dx11VertexShader(const Shader::Spec& spec, ID3D11Device* device);

  virtual void activate() override;
};

}  // namespace impl
}  // namespace cubit
