#include "Dx11VertexShader.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#include "Dx11ShaderCompiler.h"
#include "Dx11VertexBuffer.h"
#include "DxResult.h"
#include "win64/os/Win64Util.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using namespace Microsoft::WRL;

namespace cubit {
namespace impl {
Dx11VertexShader::Dx11VertexShader(
    Dx11Device device,
    Dx11DeviceContext deviceContext,
    const ShaderSpec& spec)
    : device(device), deviceContext(deviceContext) {
  ComPtr<ID3DBlob> blob =
      Dx11ShaderCompiler::compile(spec.file, spec.entryPoint, "vs_4_0");

  device->CreateVertexShader(
      blob->GetBufferPointer(),
      blob->GetBufferSize(),
      NULL,
      shader.GetAddressOf());

  Dx11InputLayout vertexLayout = Dx11Vertex::getLayout();
  device->CreateInputLayout(
      vertexLayout.desc,
      vertexLayout.size,
      blob->GetBufferPointer(),
      blob->GetBufferSize(),
      layout.GetAddressOf());
}

void Dx11VertexShader::activate() const {
  deviceContext->VSSetShader(shader.Get(), 0, 0);

  deviceContext->IASetInputLayout(layout.Get());
}

Dx11VertexShader::~Dx11VertexShader() {}

}  // namespace impl
}  // namespace cubit
