﻿#include "Dx11VertexShader.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#include "Dx11ShaderCompiler.h"
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
    const Shader::Spec& spec)
    : device(device), deviceContext(deviceContext) {
  ComPtr<ID3DBlob> blob =
      Dx11ShaderCompiler::compile(spec.file, spec.entryPoint, "vs_4_0");

  device->CreateVertexShader(
      blob->GetBufferPointer(),
      blob->GetBufferSize(),
      NULL,
      shader.GetAddressOf());
}

void Dx11VertexShader::activate() {
  deviceContext->VSSetShader(shader.Get(), 0, 0);
}

Dx11VertexShader::~Dx11VertexShader() {}

}  // namespace impl
}  // namespace cubit