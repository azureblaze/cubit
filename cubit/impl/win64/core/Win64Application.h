#pragma once
#include <map>
#include <memory>
#include <string_view>

#include <fruit/fruit.h>

#include <cubit/core/application.h>
#include <cubit/inject/Factory.h>
#include <cubit/os/Timer.h>

#include "Win64Window.h"
#include "common/core/FrameRateGovernor.h"

namespace cubit {
class Logger;
class Input;
namespace impl {
class Win64Application : public Application {
 public:
  struct Spec {
    intptr_t applicationInstance;
    std::string_view commandLineArgs;
  };

  INJECT(Win64Application(
      ASSISTED(const Spec&) spec,
      Win64WindowFactory windowFactory,
      Config* config,
      Logger* logger,
      Input* input,
      Factory<FrameRateGovernor> frameRateGovernor));
  void initialize() override;
  int start(std::function<void()> update) override;
  void quit() override { isRunning = false; };
  std::unique_ptr<Window> createWindow();

  friend Win64Window;

 private:
  const Spec spec;
  Win64WindowFactory windowFactory;
  const Config& config;
  Logger& logger;
  Input& input;
  std::unique_ptr<FrameRateGovernor> frameRateGovernor;

  bool isRunning = true;
  std::map<intptr_t, Win64Window*> windows;

  void registerWindowClass();

  void removeWindow(intptr_t handle) { windows.erase(handle); }

  static intptr_t __stdcall WindowProc(
      intptr_t hWnd,
      uint32_t message,
      intptr_t wParam,
      intptr_t lParam);
};
}  // namespace impl
}  // namespace cubit
