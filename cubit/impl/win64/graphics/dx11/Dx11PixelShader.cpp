#include "Dx11PixelShader.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#include "Dx11ShaderCompiler.h"
#include "DxResult.h"
#include "win64/os/Win64Util.h"

using namespace Microsoft::WRL;
namespace cubit {
namespace impl {
Dx11PixelShader::Dx11PixelShader(const Shader::Spec& spec, ID3D11Device* device)
    : device(device) {
  ComPtr<ID3DBlob> blob =
      Dx11ShaderCompiler::compile(spec.file, spec.entryPoint, "ps_4_0");

  device->CreatePixelShader(
      blob->GetBufferPointer(),
      blob->GetBufferSize(),
      NULL,
      shader.GetAddressOf());
}

void Dx11PixelShader::activate() {
  throw std::logic_error("The method or operation is not implemented.");
}

}  // namespace impl
}  // namespace cubit
