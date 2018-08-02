#pragma once

#include <memory>
#include <string_view>

#include <fruit/fruit.h>

namespace cubit {
class Application;
class Logger;
class Renderer;
class Input;

using CubitComponent = fruit::Component<
    std::function<std::unique_ptr<Application>(intptr_t, std::string_view)>,
    Logger,
    Renderer,
    Input>;
CubitComponent getCubitInjector();
}  // namespace cubit
