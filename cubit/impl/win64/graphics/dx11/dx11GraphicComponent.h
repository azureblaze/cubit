#pragma once
#include <memory>

#include <boost/di.hpp>
#include <boost/di/extension/injections/assisted_injection.hpp>

#include <cubit/graphics/Renderer.h>

#include "win64/graphics/dx11/Dx11Renderer.h"

struct Foo {};
namespace cubit {
namespace impl {
boost::di::injector<Win64Renderer&, Renderer&> getDx11GraphicsComponent();
}  // namespace impl
}  // namespace cubit
