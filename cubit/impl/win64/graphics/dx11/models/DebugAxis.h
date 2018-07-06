#pragma once
#include "../Dx11Model.h"

#include <memory>

#include "../Dx11VertexBuffer.h"

namespace cubit {
namespace impl {

class Dx11Material;

class DebugAxis : public Dx11Model {
  Dx11Device device;
  Dx11DeviceContext deviceContext;
  std::unique_ptr<Dx11Material> material;

 public:
  DebugAxis(
      Dx11VertexBufferFactory vertexBufferfactory,
      Dx11Device device,
      Dx11DeviceContext deviceContext,
      std::unique_ptr<Dx11Material> material);

  ~DebugAxis();

  virtual Material* getMaterial() const override;

  virtual void drawPrimitives(
      const std::set<Instance*>& instances) const override;

  virtual std::unique_ptr<Instance> createInstance() const override;
};
}  // namespace impl
}  // namespace cubit
