#pragma once
#include <cubit/core/application.h>

#include <fruit/fruit.h>

#include <string_view>

#include <cubit/inject/Factory.h>

namespace cubit {
class Logger;
class Config;
class Input;
namespace impl {
class FrameRateGovernor;
class Win64Input;
class Win64Renderer;
using Win64CoreComponent = fruit::Component<
    fruit::Required<
        Logger,
        Config,
        Input,
        Win64Input,
        Win64Renderer,
        Factory<FrameRateGovernor>>,
    Application>;

Win64CoreComponent getWin64CoreInjector(
    intptr_t applicationInstance,
    std::string_view commandLineArgs);
}  // namespace impl
}  // namespace cubit
