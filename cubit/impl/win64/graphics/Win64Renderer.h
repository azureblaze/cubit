#pragma once
#include <cubit/graphics/Renderer.h>

#include <functional>
#include <memory>

namespace cubit {
class Renderer;
namespace impl {
class Win64Window;
class Win64Renderer : public Renderer {
 public:
  virtual std::unique_ptr<RenderTarget> createTarget(Win64Window& window) = 0;

  virtual void present(Win64Window& window) = 0;
};
}  // namespace impl
}  // namespace cubit
