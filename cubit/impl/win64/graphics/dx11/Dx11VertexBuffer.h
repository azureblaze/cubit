#pragma once
#include <memory.h>
#include <functional>
#include <vector>

#include <fruit/fruit.h>

#include <cubit/inject/Factory.h>

#include "ComPtr.h"
#include "Dx11Device.h"

struct ID3D11Buffer;
struct D3D11_INPUT_ELEMENT_DESC;

namespace cubit {
namespace impl {

struct Dx11InputLayout {
  D3D11_INPUT_ELEMENT_DESC* desc;
  size_t size;
};

struct Dx11Vertex {
  float postion[3];
  float color[4];

  static Dx11InputLayout getLayout();
};

class Dx11VertexBuffer {
  ComPtr<ID3D11Buffer> buffer;

  std::vector<Dx11Vertex> vertices;

  Dx11Device device;
  Dx11DeviceContext deviceContext;
  size_t size;

 public:
  INJECT(Dx11VertexBuffer(
      Dx11Device device,
      Dx11DeviceContext deviceContext,
      ASSISTED(size_t) size));

  ~Dx11VertexBuffer();

  void set(size_t index, const Dx11Vertex& vertex) {
    vertices[index] = vertex;
  };

  size_t getSize() { return size; };

  ID3D11Buffer* getBuffer() { return buffer.Get(); }

  void map();
};

using Dx11VertexBufferFactory = Factory<Dx11VertexBuffer, size_t>;
}  // namespace impl
}  // namespace cubit
