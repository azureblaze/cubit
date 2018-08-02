#pragma once
#include <cubit/graphics/Model.h>

#include <memory>

namespace cubit {
namespace impl {
class Dx11VertexBuffer;
class Dx11Model : public Model {
 protected:
  std::unique_ptr<Dx11VertexBuffer> vertices;

 public:
  virtual ~Dx11Model();
  Dx11VertexBuffer *getVertexBuffer() { return vertices.get(); }
};
}  // namespace impl
}  // namespace cubit
