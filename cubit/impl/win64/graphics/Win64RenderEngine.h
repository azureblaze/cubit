#pragma once
#include "common/graphics/RenderEngine.h"

#include <functional>
#include <memory>

namespace cubit {
class Renderer;
namespace impl {
class Win64Window;
class Win64RenderEngine : public RenderEngine {
 public:
};

using Win64RenderEngineFactory =
    std::function<std::unique_ptr<RenderEngine>(Win64Window*)>;
}  // namespace impl
}  // namespace cubit
