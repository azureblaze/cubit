#pragma once
#include <cubit/graphics/Resources.h>

#include <functional>
#include <memory>

namespace cubit {
namespace impl {

struct Dx11Device;
struct Dx11DeviceContext;

class DebugAxis;
using DebugAxisFactory = std::function<std::unique_ptr<DebugAxis>()>;

class Dx11Resources : public Resources {
  struct Impl;

  std::unique_ptr<Impl> impl;

 public:
  Dx11Resources(
      Dx11Device device,
      Dx11DeviceContext deviceContext,
      DebugAxisFactory debugAxisFactory);
  ~Dx11Resources();

  virtual const Model* getModel(const std::string& name) override;
};
}  // namespace impl
}  // namespace cubit
