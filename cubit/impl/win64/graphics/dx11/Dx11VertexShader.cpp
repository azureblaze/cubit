#include "Dx11VertexShader.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#include "Dx11ShaderCompiler.h"
#include "Dx11VertexBuffer.h"
#include "DxResult.h"
#include "win64/os/Win64Util.h"

namespace cubit {
namespace impl {
Dx11VertexShader::Dx11VertexShader(Dx11Device* device, const ShaderSpec& spec)
    : device(device) {
  ComPtr<ID3DBlob> blob =
      Dx11ShaderCompiler::compile(spec.file, spec.entryPoint, "vs_4_0");

  device->getDevice().CreateVertexShader(
      blob->GetBufferPointer(),
      blob->GetBufferSize(),
      NULL,
      shader.GetAddressOf());

  Dx11InputLayout vertexLayout = Dx11Vertex::getLayout();
  device->getDevice().CreateInputLayout(
      vertexLayout.desc,
      vertexLayout.size,
      blob->GetBufferPointer(),
      blob->GetBufferSize(),
      layout.GetAddressOf());
}

void Dx11VertexShader::activate() const {
  device->getDeviceContext().VSSetShader(shader.Get(), 0, 0);

  device->getDeviceContext().IASetInputLayout(layout.Get());
}

Dx11VertexShader::~Dx11VertexShader() {}

}  // namespace impl
}  // namespace cubit
