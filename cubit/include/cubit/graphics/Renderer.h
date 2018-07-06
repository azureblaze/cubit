#pragma once
#include <boost/di/extension/injections/factory.hpp>

#include <functional>
#include <memory>
#include <string>

namespace cubit {
class RenderTarget;
class Model;
namespace impl {
class RenderEngine;
}  // namespace impl
class Texture2D;
class Renderer {
 public:
  virtual ~Renderer() = default;

  virtual RenderTarget& getBackBufferTarget() = 0;

  virtual Model* loadModel(const std::string& name) = 0;

  virtual void present() = 0;
};

using RendererFactory =
    std::function<std::unique_ptr<Renderer>(impl::RenderEngine*)>;

}  // namespace cubit
