#pragma once
#ifdef EXPORT_CUBIT_DLL
#define CUBIT_EXPORT __declspec(dllexport)
#else
#define CUBIT_EXPORT __declspec(dllimport)
#endif
#include <boost/di.hpp>
#include <memory>
#include <string_view>

namespace cubit {
class Application;
class Logger;
class Renderer;
class Input;

boost::di::injector<Application&, Logger&, Renderer&, Input&> getCubitInjector(
    intptr_t instance,
    std::string_view commandLine);
}  // namespace cubit
