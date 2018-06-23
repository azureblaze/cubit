#pragma once
#include <memory>

#include <boost/di.hpp>
#include <boost/di/extension/injections/assisted_injection.hpp>

#include <cubit/graphics/Renderer.h>

#include "win64/graphics/Win64RenderEngine.h"

struct Foo {};
namespace cubit {
namespace impl {
boost::di::injector<Win64RenderEngineFactory, RendererFactory>
getDx11GraphicsComponent();
}  // namespace impl
}  // namespace cubit
