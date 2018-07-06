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

namespace cubit {
namespace impl {

struct ConstBuffer {
  Matrix4 viewProjection;
};

static ID3D11Buffer* constBuffer;

Dx11Material::Dx11Material(
    Dx11Device device,
    Dx11DeviceContext deviceContext,
    Dx11VertexShaderFactory vertexShaderFactory,
    Dx11PixelShaderFactory pixelShaderFactory)
    : device(device), deviceContext(deviceContext) {
  vertexShader =
      vertexShaderFactory(Shader::Spec{"data/debug.hlsl", "vertexMain"});

  pixelShader =
      pixelShaderFactory(Shader::Spec{"data/debug.hlsl", "pixelMain"});

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
                              .getViewProjection(0.1920, 0.1080, 0.1, 1000)
                              .transpose();
  /*
    buffer.viewProjection =
        (Matrix4::translate(Vector3(-5, -5, -5)) *
         (Quaternion::lookAt(Vector3(-1, -1, -1), Vector3(0, 1, 0)) *
          Quaternion::fromAxis(Vector3(0, 1, 0), PI_2))
             .inverse()
             .toMatrix() *
         Matrix4::perspectiveProjection(0.1920, 0.1080, 0.1, 1000))
            .transpose();*/

  Vector3 v0(0, 0, 0);
  v0 = v0.transformAsPoint(buffer.viewProjection.transpose());

  Vector3 v1(1, 0, 0);
  v1 = v1.transformAsPoint(buffer.viewProjection.transpose());

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
