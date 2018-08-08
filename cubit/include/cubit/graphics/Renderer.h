#pragma once
#include <functional>
#include <memory>
#include <string>

namespace cubit {
class RenderTarget;
class Resources;
namespace impl {
class RenderEngine;
}  // namespace impl
class Texture2D;
class Renderer {
 public:
  virtual ~Renderer() = default;

  virtual Resources& getResources() = 0;
};

using RendererFactory =
    std::function<std::unique_ptr<Renderer>(impl::RenderEngine*)>;

}  // namespace cubit
