#include "Win64Window.h"

#include <cubit/core/config.h>
#include <sstream>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "Win64Application.h"
#include "Win64Util.h"

using namespace std;

namespace cubit {
namespace impl {
Win64Window::Win64Window(const Spec& spec, shared_ptr<Config> config)
    : spec(spec) {
  width = config->get<int>("default_window_width");
  height = config->get<int>("default_window_height");
}

intptr_t Win64Window::initialize() {
  RECT windowSize{0, 0, width, height};
  AdjustWindowRect(&windowSize, WS_OVERLAPPEDWINDOW, FALSE);

  handle = (intptr_t)CreateWindowExW(
      0,
      Win64Util::utf8ToWchar(spec.windowClass).c_str(),
      nullptr,
      WS_OVERLAPPEDWINDOW,
      0,
      0,
      windowSize.right - windowSize.left,
      windowSize.bottom - windowSize.top,
      nullptr,
      nullptr,
      (HINSTANCE)spec.applicationInstance,
      nullptr);
  return handle;
}

Win64Window::~Win64Window() { spec.application->removeWindow(handle); }

void Win64Window::show() { ShowWindow((HWND)handle, SW_SHOW); }

intptr_t
Win64Window::onWindowProc(uint32_t message, intptr_t wParam, intptr_t lParam) {
  // sort through and find what code to run for the message given
  switch (message) {
    // this message is read when the window is closed
    case WM_DESTROY: {
      // close the application entirely
      PostQuitMessage(0);
      return 0;
    } break;
  }

  // Handle any messages the switch statement didn't
  return DefWindowProc((HWND)handle, message, wParam, lParam);
}
}  // namespace impl
}  // namespace cubit
