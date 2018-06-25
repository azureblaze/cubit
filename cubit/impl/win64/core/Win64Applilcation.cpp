#include "Win64Application.h"

#include <cassert>
#include <sstream>

#include <boost/di/extension/injections/factory.hpp>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <Mmsystem.h>

#include <cubit/core/Exception.h>
#include <cubit/os/Logger.h>
#include "win64/os/Win64Util.h"

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
    Win64WindowFactory windowFactory,
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
  assert(instance == nullptr || instance == this);
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
  MSG message;
  timeBeginPeriod(1);
  frameRateGovernor->start();
  try {
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
  } catch (Exception e) {
  }
  return (int)message.wParam;
}

unique_ptr<Window> Win64Application::createWindow() {
  unique_ptr<Win64Window> window = windowFactory(
      Win64Window::Spec{windowClassName, spec.applicationInstance, this});
  windows[window->initialize()] = window.get();
  return window;
}
}  // namespace impl
}  // namespace cubit
