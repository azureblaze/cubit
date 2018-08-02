#pragma once

#include <memory>
#include <string_view>

#include <fruit/fruit.h>

namespace cubit {
class Application;
class Logger;
class Renderer;
class Input;

using CubitComponent = fruit::Component<Application, Logger, Renderer, Input>;
CubitComponent getCubitInjector(
    intptr_t applicationInstance,
    std::string_view commandLineArgs);
}  // namespace cubit
