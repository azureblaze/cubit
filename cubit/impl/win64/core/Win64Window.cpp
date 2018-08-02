#include "Win64Window.h"

#include <cubit/config/config.h>
#include <cubit/graphics/RenderTarget.h>
#include <cubit/graphics/Renderer.h>
#include <sstream>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef near
#undef far

#include "Win64Application.h"
#include "win64/graphics/Win64Renderer.h "
#include "win64/input/Win64Input.h"
#include "win64/os/Win64Util.h"

using namespace std;

namespace cubit {
namespace impl {
Win64Window::Win64Window(
    const Spec& spec,
    Config* config,
    Win64Renderer* renderer,
    Win64Input* input)
    : spec(spec), renderer(*renderer), input(*input) {
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
  renderTarget = move(renderer.createTarget(*this));
  return handle;
}

Win64Window::~Win64Window() { spec.application->removeWindow(handle); }

void Win64Window::show() { ShowWindow((HWND)handle, SW_SHOW); }

cubit::RenderTarget& Win64Window::getRenderTarget() {
  return *renderTarget.get();
}

void Win64Window::present() { renderer.present(*this); }

intptr_t
Win64Window::onWindowProc(uint32_t message, intptr_t wParam, intptr_t lParam) {
  switch (message) {
    case WM_DESTROY: {
      PostQuitMessage(0);
      return 0;
      case WM_SYSKEYDOWN:
        if (wParam == VK_F4) {
          break;
        }
      case WM_KEYDOWN:
        input.onKeyDown(wParam);
        return 0;
      case WM_KEYUP:
      case WM_SYSKEYUP:
        input.onKeyUp(wParam);
        return 0;
      case WM_MOUSEMOVE:
        input.onMouseMove(lParam);
        return 0;
    } break;
  }
  return DefWindowProc((HWND)handle, message, wParam, lParam);
}
}  // namespace impl
}  // namespace cubit
