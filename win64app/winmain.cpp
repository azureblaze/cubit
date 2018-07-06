#include <boost/di.hpp>

#include <memory>

#include <cubit/core/application.h>
#include <cubit/core/window.h>
#include <cubit/cubit.h>
#include <cubit/graphics/Camera.h>
#include <cubit/graphics/Color.h>
#include <cubit/graphics/Instance.h>
#include <cubit/graphics/Model.h>
#include <cubit/graphics/RenderTarget.h>
#include <cubit/graphics/Renderer.h>
#include <cubit/graphics/Scene.h>

#include <cubit/math/math.h>
#include <cubit/os/logger.h>
using namespace cubit;
using namespace std;

namespace di = boost::di;
class Game {
  Logger &logger;
  int i = 0;
  unique_ptr<Window> window;

  Scene scene;
  Camera camera;

  Instance *instance;

 public:
  Game(Application &application, Logger &logger) : logger(logger) {
    window = application.createWindow();
    window->show();

    Model *model = window->getRenderer().loadModel("debug:axis");
    instance = scene.addInstance(*model);
  }
  void update() {
    window->getRenderer().getBackBufferTarget().clear(Color{0, 0, 0, 0});

    float t = (2.0f * PI * i / 60.0f);
    Vector3 p(5.0f * sinf(t), 5, 5.0f * cos(t));

    camera.getTransform().setPosition(p);
    camera.getTransform().setRotation(Quaternion::lookAt(-p, Vector3(0, 1, 0)));

    scene.setCamera(camera);

    scene.render(window->getRenderer().getBackBufferTarget());

    window->getRenderer().present();
    i++;
  }
};

int __stdcall WinMain(
    void *hInstance,
    void *hPrevInstance,
    const char *lpCmdLine,
    int nCmdShow) {
  auto cubit = di::make_injector(
      cubit::getCubitInjector((intptr_t)hInstance, lpCmdLine));
  cubit.create<Application &>().initialize();

  Game *game = cubit.create<Game *>();
  return cubit.create<Application &>().start(std::bind(&Game::update, game));
}
