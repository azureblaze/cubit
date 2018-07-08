#include "Win64Input.h"

#include "win64/core/Win64Window.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef DELETE
#undef near
#undef far

namespace cubit {
namespace impl {

static Keys fromVirtualKey(int virtualKey) {
  if (virtualKey >= 'A' && virtualKey <= 'Z') {
    return (Keys)((int)Keys::A + virtualKey - 'A');
  }

  if (virtualKey >= '0' && virtualKey <= '9') {
    return (Keys)((int)Keys::A + virtualKey - '0');
  }

  switch (virtualKey) {
    case VK_BACK:
      return Keys::BACKSPACE;
    case VK_TAB:
      return Keys::TAB;
    case VK_RETURN:
      return Keys::ENTER;
    case VK_ESCAPE:
      return Keys::ESCAPE;
    case VK_SPACE:
      return Keys::SPACE;
    case VK_PRIOR:
      return Keys::PAGE_UP;
    case VK_NEXT:
      return Keys::PAGE_DOWN;
    case VK_END:
      return Keys::END;
    case VK_HOME:
      return Keys::HOME;
    case VK_LEFT:
      return Keys::LEFT;
    case VK_UP:
      return Keys::UP;
    case VK_RIGHT:
      return Keys::RIGHT;
    case VK_DOWN:
      return Keys::DOWN;
    case VK_INSERT:
      return Keys::INSERT;
    case VK_DELETE:
      return Keys::DELETE;
    case VK_NUMPAD0:
      return Keys::KEY_1;
    case VK_NUMPAD1:
      return Keys::KEY_2;
    case VK_NUMPAD2:
      return Keys::KEY_3;
    case VK_NUMPAD3:
      return Keys::KEY_4;
    case VK_NUMPAD4:
      return Keys::KEY_5;
    case VK_NUMPAD5:
      return Keys::KEY_6;
    case VK_NUMPAD6:
      return Keys::KEY_0;
    case VK_NUMPAD7:
      return Keys::KEY_7;
    case VK_NUMPAD8:
      return Keys::KEY_8;
    case VK_NUMPAD9:
      return Keys::KEY_9;
    case VK_MULTIPLY:
      return Keys::NUM_MULTIPLY;
    case VK_ADD:
      return Keys::NUM_ADD;
    case VK_SUBTRACT:
      return Keys::NUM_SUBTRACT;
    case VK_DECIMAL:
      return Keys::NUM_DEMICAL;
    case VK_DIVIDE:
      return Keys::NUM_DIVIDE;
    case VK_F1:
      return Keys::F1;
    case VK_F2:
      return Keys::F2;
    case VK_F3:
      return Keys::F3;
    case VK_F4:
      return Keys::F4;
    case VK_F5:
      return Keys::F5;
    case VK_F6:
      return Keys::F6;
    case VK_F7:
      return Keys::F7;
    case VK_F8:
      return Keys::F8;
    case VK_F9:
      return Keys::F9;
    case VK_F10:
      return Keys::F10;
    case VK_F11:
      return Keys::F11;
    case VK_F12:
      return Keys::F12;
    case VK_SHIFT:
      return Keys::SHIFT;
    case VK_CONTROL:
      return Keys::CONTROL;
    case VK_MENU:
      return Keys::ALT;
  }
  return Keys::UNKNOWN;
}

Win64Input::Win64Input() { clearKeyState(); }

bool Win64Input::getKeyState(Keys key) { return state[(int)key]; }

bool Win64Input::isKeyUp(Keys key) { return keyUp[(int)key]; }

bool Win64Input::isKeyDown(Keys key) { return keyDown[(int)key]; }

cubit::Vector2 Win64Input::getMousePosition() { return mousePosition; }

void Win64Input::clearKeyState() {
  for (int i = 0; i < (int)Keys::keyCount; i++) {
    state[i] = false;
    keyDown[i] = false;
    keyUp[i] = false;
  }
}

void Win64Input::resetFrame() {
  for (int i = 0; i < (int)Keys::keyCount; i++) {
    keyDown[i] = false;
    keyUp[i] = false;
  }
  if (mouseCaptured) {
    POINT center;
    center.x = window->getWidth() / 2;
    center.y = window->getHeight() / 2;
    ClientToScreen((HWND)window->getHandle(), &center);
    SetCursorPos(center.x, center.y);
    mousePosition = Vector2(0, 0);
  }
}

void Win64Input::setCaptureMouse(Window* window_) {
  mouseCaptured = window_ != nullptr;
  window = dynamic_cast<Win64Window*>(window_);
  mousePosition = Vector2(0, 0);
  ShowCursor(!mouseCaptured);
}

void Win64Input::onKeyDown(int virtualKey) {
  keyDown[(int)fromVirtualKey(virtualKey)] = true;
  state[(int)fromVirtualKey(virtualKey)] = true;
}

void Win64Input::onKeyUp(int virtualKey) {
  keyUp[(int)fromVirtualKey(virtualKey)] = true;
  state[(int)fromVirtualKey(virtualKey)] = false;
}

void Win64Input::onMouseMove(uint64_t lparam) {
  POINTS points = *(POINTS*)(&lparam);
  mousePosition = Vector2(points.x, points.y);
  if (mouseCaptured) {
    mousePosition -= Vector2(window->getWidth() / 2, window->getHeight() / 2);
  }
}

}  // namespace impl
}  // namespace cubit
