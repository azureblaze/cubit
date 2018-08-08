#pragma once

#include <memory>
#include <string_view>

#include <fruit/fruit.h>

#include <cubit/inject/FactoryRegistry.h>

namespace cubit {
class Application;
class Logger;
class Renderer;
class Input;
class FactoryRegistry;

using CubitComponent =
    fruit::Component<Application, Logger, Renderer, Input, FactoryRegistry>;
CubitComponent getCubitInjector(
    intptr_t applicationInstance,
    std::string_view commandLineArgs);

template <class... Args>
void initializeInjector(fruit::Injector<Args...>& injector) {
  injector.get<FactoryRegistry&>().registerFactories(injector);
}

}  // namespace cubit
