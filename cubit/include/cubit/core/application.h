#pragma once
#include <functional>
#include <memory>
#include "Window.h"
namespace cubit {
class Window;
class Application {
 public:
  virtual ~Application() = default;
  virtual void initialize() = 0;
  virtual int start(std::function<void()> update) = 0;
  virtual void quit() = 0;
  virtual std::unique_ptr<Window> createWindow() = 0;
};
}  // namespace cubit
