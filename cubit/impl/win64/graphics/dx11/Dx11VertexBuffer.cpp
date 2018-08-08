#include "Dx11VertexBuffer.h"

#include <d3d11.h>

#include "Dx11VertexShader.h"
#include "DxResult.h"

namespace cubit {
namespace impl {
Dx11VertexBuffer::Dx11VertexBuffer(Dx11Device* device, size_t size)
    : device(device), size(size), vertices(size, Dx11Vertex{}) {
  D3D11_BUFFER_DESC bufferDescription{};

  bufferDescription.Usage = D3D11_USAGE_DYNAMIC;
  bufferDescription.ByteWidth = sizeof(Dx11Vertex) * size;
  bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

  device->getDevice().CreateBuffer(
      &bufferDescription, NULL, buffer.GetAddressOf());
}

Dx11VertexBuffer::~Dx11VertexBuffer() {}

void Dx11VertexBuffer::map() {
  D3D11_MAPPED_SUBRESOURCE mappedSubresouce;
  checkResult(device->getDeviceContext().Map(
      buffer.Get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mappedSubresouce));
  memcpy(mappedSubresouce.pData, vertices.data(), sizeof(Dx11Vertex) * size);
  device->getDeviceContext().Unmap(buffer.Get(), NULL);
}

static D3D11_INPUT_ELEMENT_DESC desc[] = {
    {"POSITION",
     0,
     DXGI_FORMAT_R32G32B32_FLOAT,
     0,
     0,
     D3D11_INPUT_PER_VERTEX_DATA,
     0},
    {"COLOR",
     0,
     DXGI_FORMAT_R32G32B32A32_FLOAT,
     0,
     12,
     D3D11_INPUT_PER_VERTEX_DATA,
     0},
};

Dx11InputLayout Dx11Vertex::getLayout() {
  return Dx11InputLayout{desc, sizeof(desc) / sizeof(D3D11_INPUT_ELEMENT_DESC)};
}

}  // namespace impl
}  // namespace cubit
