#pragma once
#include <memory>

#include <boost/di.hpp>
#include <boost/di/extension/injections/assisted_injection.hpp>

#include <cubit/graphics/Renderer.h>

#include "win64/graphics/Win64Renderer.h"

struct Foo {};
namespace cubit {
namespace impl {
boost::di::injector<Win64RendererFactory> getDx11GraphicsComponent();
}  // namespace impl
}  // namespace cubit
