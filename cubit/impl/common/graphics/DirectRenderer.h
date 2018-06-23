#pragma once
#include <cubit/graphics/Renderer.h>

#include <boost/di.hpp>
#include <boost/di/extension/injections/assisted_injection.hpp>

#include "common/graphics/RenderEngine.h"

namespace cubit {
namespace impl {
class RenderEngine;
class DirectRenderer : public Renderer {
 public:
  BOOST_DI_INJECT(
      DirectRenderer,
      (named = boost::di::extension::assisted) RenderEngine* renderEngine);

  virtual void render() override;

 private:
  std::unique_ptr<RenderEngine> renderEngine;
};

}  // namespace impl
}  // namespace cubit
