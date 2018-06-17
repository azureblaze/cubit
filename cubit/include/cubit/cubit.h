#pragma once
#ifdef EXPORT_CUBIT_DLL
#define CUBIT_EXPORT __declspec(dllexport)
#else
#define CUBIT_EXPORT
#endif

#include <cubit/core/application.h>
#include <memory>
#include <string_view>

namespace cubit {
CUBIT_EXPORT std::shared_ptr<Application> createWin64Application(void *instance, std::string_view commandLine);
}