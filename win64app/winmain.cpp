#include <boost/di.hpp>

#include <memory>

#include <cubit/core/application.h>
#include <cubit/core/window.h>
#include <cubit/cubit.h>
#include <cubit/graphics/Color.h>
#include <cubit/graphics/RenderTarget.h>
#include <cubit/graphics/Renderer.h>
#include <cubit/math/math.h>
#include <cubit/os/logger.h>
using namespace cubit;
namespace di = boost::di;
class Game {
  Logger &logger;
  int i = 0;
  std::unique_ptr<Window> window;

 public:
  Game(Application &application, Logger &logger) : logger(logger) {
    window = application.createWindow();
    window->show();
  }
  void update() {
    window->getRenderer().getBackBufferTarget().clear(
        Color{0, 0, sinf(i / 60.0f) / 2.f + 0.5f, 1});
    window->getRenderer().present();
    i++;
  }
};
static void foo() {
  Vector4 v(5, 2, 2, 2);
  Matrix4 m({{0, 2, 5, 2}, {.4f, 0, 0, 0}, {0, .5f, 0, 0}, {0, 0, .6f, 0}});

  Vector4 r = v * m;
}

int __stdcall WinMain(
    void *hInstance,
    void *hPrevInstance,
    const char *lpCmdLine,
    int nCmdShow) {
  auto cubit = di::make_injector(
      cubit::getCubitInjector((intptr_t)hInstance, lpCmdLine));
  cubit.create<Application &>().initialize();

  foo();

  Game game = cubit.create<Game>();
  return cubit.create<Application &>().start(std::bind(&Game::update, &game));
}
