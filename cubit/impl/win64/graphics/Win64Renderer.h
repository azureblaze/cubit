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
};

using Win64RendererFactory =
    std::function<std::unique_ptr<Renderer>(Win64Window*)>;
}  // namespace impl
}  // namespace cubit
