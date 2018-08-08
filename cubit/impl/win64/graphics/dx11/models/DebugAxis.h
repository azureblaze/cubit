#pragma once
#include "../Dx11Model.h"

#include <memory>

#include <fruit/fruit.h>

#include <cubit/inject/Factory.h>

#include "../Dx11VertexBuffer.h"

namespace cubit {
namespace impl {

class Dx11Material;
class Dx11Resources;

class DebugAxis : public Dx11Model {
  Dx11Device* device;
  Dx11Material* material;

 public:
  INJECT(DebugAxis(
      ASSISTED(Dx11Resources*) resources,
      Dx11VertexBufferFactory vertexBufferfactory,
      Dx11Device* device));

  ~DebugAxis();

  virtual Material* getMaterial() const override;

  virtual void drawPrimitives(
      const std::set<Instance*>& instances) const override;

  virtual std::unique_ptr<Instance> createInstance() const override;
};

using DebugAxisFactory = Factory<DebugAxis>;
}  // namespace impl
}  // namespace cubit
