#pragma once
#include <memory.h>
#include <functional>
#include <vector>

#include <boost/di.hpp>
#include <boost/di/extension/injections/assisted_injection.hpp>

#include <wrl/client.h>

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
  Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;

  std::vector<Dx11Vertex> vertices;

  Dx11Device device;
  Dx11DeviceContext deviceContext;
  size_t size;

 public:
  BOOST_DI_INJECT(
      Dx11VertexBuffer,
      Dx11Device device,
      Dx11DeviceContext deviceContext,
      (named = boost::di::extension::assisted) size_t size);

  ~Dx11VertexBuffer();

  void set(size_t index, const Dx11Vertex& vertex) {
    vertices[index] = vertex;
  };

  size_t getSize() { return size; };

  ID3D11Buffer* getBuffer() { return buffer.Get(); }

  void map();
};

using Dx11VertexBufferFactory =
    std::function<std::unique_ptr<Dx11VertexBuffer>(size_t)>;
}  // namespace impl
}  // namespace cubit
