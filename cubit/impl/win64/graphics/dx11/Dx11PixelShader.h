#pragma once
#include <cubit/graphics/PixelShader.h>

#include <wrl/client.h>

struct ID3D11PixelShader;
struct ID3D11Device;
namespace cubit {
namespace impl {
class Dx11PixelShader : public PixelShader {
  Microsoft::WRL::ComPtr<ID3D11PixelShader> shader;
  ID3D11Device* device;

 public:
  Dx11PixelShader(const Shader::Spec& spec, ID3D11Device* device);

  virtual void activate() override;
};
}  // namespace impl
}  // namespace cubit
