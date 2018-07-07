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
#include <cubit/graphics/Resources.h>
#include <cubit/graphics/Scene.h>

#include <cubit/math/math.h>
#include <cubit/os/logger.h>
using namespace cubit;
using namespace std;

namespace di = boost::di;
class Game {
  Logger &logger;
  Renderer &renderer;
  int i = 0;
  unique_ptr<Window> window;

  Scene scene;
  Camera camera;

  Instance *instance;

 public:
  Game(Application &application, Logger &logger, Renderer &renderer)
      : logger(logger), renderer(renderer) {
    window = application.createWindow();
    window->show();

    const Model *model = renderer.resources().getModel("debug:axis");
    instance = scene.addInstance(*model);
  }
  void update() {
    window->getRenderTarget().clear(Color{0, 0, 0, 0});

    float t = (1.0f * PI * i / 60.0f);
    Vector3 p(5.0f * sinf(t), 5, 5.0f * cos(t));

    camera.getTransform().setPosition(p);
    camera.getTransform().setRotation(Quaternion::lookAt(
        -p + Vector3(0, 2 * sinf(t / 3), 0), Vector3(0, 1, 0)));

    scene.setCamera(camera);

    scene.render(window->getRenderTarget());

    window->present();
    i++;
  }
};

int __stdcall WinMain(
    void *hInstance,
    void *hPrevInstance,
    const char *lpCmdLine,
    int nCmdShow) {
  int result;
  {
    auto cubit = di::make_injector(
        cubit::getCubitInjector((intptr_t)hInstance, lpCmdLine));
    Application &application = cubit.create<Application &>();
    application.initialize();

    Game *game = cubit.create<Game *>();

    result = application.start(std::bind(&Game::update, game));
  }
  return result;
}
