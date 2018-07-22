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

#include <cubit/input/Input.h>
#include <cubit/math/math.h>
#include <cubit/os/logger.h>
using namespace cubit;
using namespace std;

namespace di = boost::di;
class Game {
  Logger &logger;
  Renderer &renderer;
  Input &input;
  int i = 0;
  unique_ptr<Window> window;

  Scene scene;
  Camera camera;

  Instance *instance;

  float pitch = 0;
  float yaw = 0;

 public:
  Game(
      Application &application,
      Logger &logger,
      Renderer &renderer,
      Input &input)
      : logger(logger), renderer(renderer), input(input) {
    window = application.createWindow();
    window->show();

    const Model *model = renderer.resources().getModel("debug:axis");
    instance = scene.addInstance(*model);

    camera.getTransform().setPosition(Vector3(5, 5, 5));

    yaw = Vector2(-1, 1).angle();
    pitch = Vector2(sqrtf(2), -1).angle();

    input.setCaptureMouse(window.get());
  }
  void update() {
    window->getRenderTarget().clear(Color{0, 0, 0, 0});

    float v = 0.05;

    Vector3 cameraForward =
        Vector3(1, 0, 0).rotate(camera.getTransform().getRotation());

    Vector3 cameraRight = Vector3(0, 1, 0).cross(cameraForward);
    cameraRight[1] = 0;
    cameraRight = cameraRight.normalize();

    Vector2 mouseDelta = input.getMousePosition();
    float t = 200.f;

    if (i > 0) {
      yaw = normalizeAngle(yaw + mouseDelta[0] / t);
      pitch = clamp(pitch - mouseDelta[1] / t, -PI_2, PI_2);
      camera.getTransform().setRotation(Quaternion::euler(yaw, pitch, 0));
    }

    Vector3 p = camera.getTransform().getPosition();
    if (input.getKeyState(Keys::W)) {
      p += cameraForward * v;
    }

    if (input.getKeyState(Keys::S)) {
      p -= cameraForward * v;
    }

    if (input.getKeyState(Keys::D)) {
      p += cameraRight * v;
    }

    if (input.getKeyState(Keys::A)) {
      p -= cameraRight * v;
    }

    if (input.getKeyState(Keys::SPACE)) {
      p += Vector3(0, 1, 0) * v;
    }

    if (input.getKeyState(Keys::SHIFT)) {
      p -= Vector3(0, 1, 0) * v;
    }

    camera.getTransform().setPosition(p);

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
