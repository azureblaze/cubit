#pragma once
#include "../Dx11Model.h"

#include <memory>

#include <cubit/inject/Factory.h>

#include "../Dx11VertexBuffer.h"

namespace cubit {
namespace impl {

class Dx11Material;
class Dx11Resources;

class DebugAxis : public Dx11Model {
  Dx11Device device;
  Dx11DeviceContext deviceContext;
  Dx11Material* material;

 public:
  BOOST_DI_INJECT(
      DebugAxis,
      Dx11Resources& resources,
      Dx11VertexBufferFactory vertexBufferfactory,
      Dx11Device device,
      Dx11DeviceContext deviceContext);

  ~DebugAxis();

  virtual Material* getMaterial() const override;

  virtual void drawPrimitives(
      const std::set<Instance*>& instances) const override;

  virtual std::unique_ptr<Instance> createInstance() const override;
};

using DebugAxisFactory = Factory<DebugAxis>;
}  // namespace impl
}  // namespace cubit
