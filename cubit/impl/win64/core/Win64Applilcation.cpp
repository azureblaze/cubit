#include "Win64Application.h"

#include <cassert>
#include <sstream>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <Mmsystem.h>

#include <cubit/core/Logger.h>
#include <boost/di/extension/injections/factory.hpp>
#include "Win64Util.h"

using namespace std;
using namespace cubit;
namespace di = boost::di;

static const char* windowClassName = "WindowClass1";
static const wchar_t* windowClassNameW = L"WindowClass1";

namespace cubit {
namespace impl {
static Win64Application* instance = nullptr;

Win64Application::Win64Application(
    const Spec& spec,
    const di::extension::ifactory<Win64Window, Win64Window::Spec>&
        windowFactory,
    Config& config,
    Logger& logger,
    const TimerFactory& timerFactory,
    std::unique_ptr<FrameRateGovernor> frameRateGovernor)
    : spec(spec),
      windowFactory(windowFactory),
      config(config),
      logger(logger),
      timerFactory(timerFactory),
      frameRateGovernor(move(frameRateGovernor)) {}

void Win64Application::initialize() {
  assert(instance == nullptr);
  instance = this;
  registerWindowClass();
}

intptr_t __stdcall Win64Application::WindowProc(
    intptr_t hWnd,
    uint32_t message,
    intptr_t wParam,
    intptr_t lParam) {
  if (instance->windows.find(hWnd) != instance->windows.end()) {
    return instance->windows[hWnd]->onWindowProc(message, wParam, lParam);
  }
  return DefWindowProc((HWND)hWnd, message, wParam, lParam);
}

void Win64Application::registerWindowClass() {
  WNDCLASSEX windowClass{0};
  windowClass.cbSize = sizeof(WNDCLASSEX);
  windowClass.style = CS_HREDRAW | CS_VREDRAW;
  windowClass.lpfnWndProc = (WNDPROC)Win64Application::WindowProc;
  windowClass.hInstance = (HINSTANCE)spec.applicationInstance;
  windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
  windowClass.lpszClassName = windowClassNameW;

  RegisterClassEx(&windowClass);
}

int Win64Application::start(std::function<void()> update) {
  auto window = createWindow();
  window->show();

  MSG message;
  timeBeginPeriod(1);
  frameRateGovernor->start();
  while (isRunning) {
    while (PeekMessage(&message, 0, 0, 0, PM_REMOVE)) {
      TranslateMessage(&message);
      DispatchMessage(&message);

      if (message.message == WM_QUIT) {
        quit();
      }
    }
    update();
    frameRateGovernor->nextFrame();
  }
  timeEndPeriod(1);
  return (int)message.wParam;
}

unique_ptr<Window> Win64Application::createWindow() {
  unique_ptr<Win64Window> window = windowFactory.create(
      Win64Window::Spec{windowClassName, spec.applicationInstance, this});
  windows[window->initialize()] = window.get();
  return window;
}
}  // namespace impl
}  // namespace cubit
