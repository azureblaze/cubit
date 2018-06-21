#include <cubit/core/application.h>
#include <cubit/core/logger.h>
#include <cubit/cubit.h>
#include <boost/di.hpp>
#include <memory>
using namespace cubit;
namespace di = boost::di;
class Game {
  Logger &logger;
  int i = 0;

 public:
  Game(Logger &logger) : logger(logger) {}
  void update() { logger.stream() << i++ << "\n"; }
};

int __stdcall WinMain(
    void *hInstance,
    void *hPrevInstance,
    const char *lpCmdLine,
    int nCmdShow) {
  auto cubit = di::make_injector(
      cubit::getCubitInjector((intptr_t)hInstance, lpCmdLine));
  cubit.create<Application &>().initialize();

  Game game = cubit.create<Game>();
  return cubit.create<Application &>().start(std::bind(&Game::update, game));
}
