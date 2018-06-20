#pragma once
#include <cubit/core/Window.h>
#include <memory>
#include <string>
using namespace std;

namespace cubit {
class Config;
namespace impl {
class Win64Application;

class Win64Window : public Window {
 public:
  struct Spec {
    std::string windowClass;
    intptr_t applicationInstance;
    Win64Application* application;
  };

  Win64Window(const Spec& spec, shared_ptr<Config> config);
  ~Win64Window();

  virtual void setSize(int width, int height) override {
    this->width = width;
    this->height = height;
  }

  virtual void show() override;

 private:
  friend Win64Application;
  const Spec spec;
  intptr_t handle;

  int width;
  int height;

  intptr_t initialize();

  intptr_t onWindowProc(uint32_t message, intptr_t wParam, intptr_t lParam);
};
}  // namespace impl
}  // namespace cubit
