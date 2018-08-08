#include "Dx11PixelShader.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#include "Dx11ShaderCompiler.h"
#include "DxResult.h"
#include "win64/os/Win64Util.h"

namespace cubit {
namespace impl {
Dx11PixelShader::Dx11PixelShader(Dx11Device* device, const ShaderSpec& spec)
    : device(device) {
  ComPtr<ID3DBlob> blob =
      Dx11ShaderCompiler::compile(spec.file, spec.entryPoint, "ps_4_0");

  device->getDevice().CreatePixelShader(
      blob->GetBufferPointer(),
      blob->GetBufferSize(),
      NULL,
      shader.GetAddressOf());
}

Dx11PixelShader::~Dx11PixelShader() {}

void Dx11PixelShader::activate() const {
  device->getDeviceContext().PSSetShader(shader.Get(), 0, 0);
}

}  // namespace impl
}  // namespace cubit
