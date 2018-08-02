#include "DebugAxis.h"

#include <cubit/graphics/Instance.h>

#include "../Dx11Device.h"
#include "../Dx11Material.h"
#include "../Dx11Resources.h"
#include "../Dx11VertexBuffer.h"

#include <d3d11.h>

namespace cubit {
namespace impl {

DebugAxis::DebugAxis(
    Dx11Resources* resources,
    Dx11VertexBufferFactory vertexBufferfactory,
    Dx11Device device,
    Dx11DeviceContext deviceContext)
    : device(device), deviceContext(deviceContext) {
  material = (Dx11Material*)resources->getMaterial("");
  vertices = vertexBufferfactory(18);
  vertices->set(0, {{0, 0, 0}, {1, 0, 0, 1}});
  vertices->set(1, {{1, 0, 0}, {1, 0, 0, 1}});
  vertices->set(2, {{1, 0, 0}, {1, 0, 0, 1}});
  vertices->set(3, {{0.95f, 0.05f, 0}, {1, 0, 0, 1}});
  vertices->set(4, {{1, 0, 0}, {1, 0, 0, 1}});
  vertices->set(5, {{0.95f, 0, 0.05f}, {1, 0, 0, 1}});

  vertices->set(6, {{0, 0, 0}, {0, 1, 0, 1}});
  vertices->set(7, {{0, 1, 0}, {0, 1, 0, 1}});
  vertices->set(8, {{0, 1, 0}, {0, 1, 0, 1}});
  vertices->set(9, {{0.05f, 0.95f, 0}, {0, 1, 0, 1}});
  vertices->set(10, {{0, 1, 0}, {0, 1, 0, 1}});
  vertices->set(11, {{0, 0.95f, 0.05f}, {0, 1, 0, 1}});

  vertices->set(12, {{0, 0, 0}, {0, 0, 1, 1}});
  vertices->set(13, {{0, 0, 1}, {0, 0, 1, 1}});
  vertices->set(14, {{0, 0, 1}, {0, 0, 1, 1}});
  vertices->set(15, {{0, 0.05f, 0.95f}, {0, 0, 1, 1}});
  vertices->set(16, {{0, 0, 1}, {0, 0, 1, 1}});
  vertices->set(17, {{0.05f, 0, 0.95f}, {0, 0, 1, 1}});
  vertices->map();
}

DebugAxis::~DebugAxis() {}

cubit::Material* DebugAxis::getMaterial() const { return material; }

void DebugAxis::drawPrimitives(const std::set<Instance*>& instances) const {
  ID3D11Buffer* d3dBuffer = vertices->getBuffer();
  uint32_t size = sizeof(Dx11Vertex);
  uint32_t offset = 0;
  deviceContext->IASetVertexBuffers(0, 1, &d3dBuffer, &size, &offset);
  deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
  deviceContext->Draw(vertices->getSize(), 0);
}

class DebugAxisInstance : public Instance {
  const DebugAxis* model;

 public:
  DebugAxisInstance(const DebugAxis* model) : model(model) {}

  virtual const Model* getModel() const override { return model; }
};

std::unique_ptr<cubit::Instance> DebugAxis::createInstance() const {
  return std::make_unique<DebugAxisInstance>(this);
}

}  // namespace impl
}  // namespace cubit
