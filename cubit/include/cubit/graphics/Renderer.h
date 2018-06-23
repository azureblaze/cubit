#pragma once
#include <boost/di/extension/injections/factory.hpp>

#include <functional>
#include <memory>

namespace cubit {
namespace impl {
class RenderEngine;
}  // namespace impl
class Renderer {
 public:
  virtual ~Renderer() = default;
  virtual void present() = 0;
};

using RendererFactory =
    std::function<std::unique_ptr<Renderer>(impl::RenderEngine*)>;

}  // namespace cubit
