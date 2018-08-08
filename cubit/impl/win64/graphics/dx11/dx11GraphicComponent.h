#pragma once
#include <memory>

#include <fruit/fruit.h>

#include <cubit/graphics/Renderer.h>

#include "win64/graphics/dx11/Dx11Renderer.h"

namespace cubit {
class Config;
class Logger;
class FactoryRegistry;
namespace impl {
using Dx11GraphicComponent = fruit::Component<
    fruit::Required<Config, Logger, FactoryRegistry>,
    Renderer,
    Win64Renderer>;

Dx11GraphicComponent getDx11GraphicsComponent();
}  // namespace impl
}  // namespace cubit
