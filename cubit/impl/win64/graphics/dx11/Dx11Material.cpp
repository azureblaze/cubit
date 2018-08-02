#include "Dx11Material.h"

#include "Dx11PixelShader.h"
#include "Dx11VertexShader.h"
#include "DxResult.h"

#include <d3d11.h>

#undef near
#undef far

#include <cubit/graphics/Camera.h>
#include <cubit/graphics/Scene.h>
#include <cubit/math/math.h>

#include "Dx11Resources.h"

namespace cubit {
namespace impl {

struct ConstBuffer {
  Matrix4 viewProjection;
};

static ID3D11Buffer* constBuffer;

Dx11Material::Dx11Material(
    Dx11Device device,
    Dx11DeviceContext deviceContext,
    Dx11Resources* resources)
    : device(device), deviceContext(deviceContext), resources(*resources) {
  vertexShader = (Dx11VertexShader*)resources->getVertexShader(
      ShaderSpec{"data/debug.hlsl", "vertexMain"});

  pixelShader = (Dx11PixelShader*)resources->getPixelShader(
      ShaderSpec{"data/debug.hlsl", "pixelMain"});

  D3D11_BUFFER_DESC constBufferDesc{};
  constBufferDesc.ByteWidth = sizeof(ConstBuffer);
  constBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
  constBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  constBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

  checkResult(device->CreateBuffer(&constBufferDesc, NULL, &constBuffer));
}

void Dx11Material::begin(const Scene& scene) {
  ConstBuffer buffer;
  buffer.viewProjection = scene.getCamera()
                              .getViewProjection(0.1920f, 0.1080f, 0.1f, 1000)
                              .transpose();

  D3D11_MAPPED_SUBRESOURCE mappedSubresouce;
  deviceContext->Map(
      constBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedSubresouce);
  memcpy(mappedSubresouce.pData, &buffer, sizeof(ConstBuffer));
  deviceContext->Unmap(constBuffer, NULL);

  deviceContext->VSSetConstantBuffers(0, 1, &constBuffer);

  vertexShader->activate();
  pixelShader->activate();
}

}  // namespace impl
}  // namespace cubit
