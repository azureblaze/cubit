#pragma once
#include "../Dx11Model.h"

#include <memory>

#include "../Dx11VertexBuffer.h"

namespace cubit {
namespace impl {

class Dx11Material;
class Dx11Resources;

class DebugAxis : public Dx11Model {
  Dx11Device device;
  Dx11DeviceContext deviceContext;
  std::unique_ptr<Dx11Material> material;

 public:
  BOOST_DI_INJECT(
      DebugAxis,
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

using DebugAxisFactory = std::function<std::unique_ptr<DebugAxis>()>;
}  // namespace impl
}  // namespace cubit
