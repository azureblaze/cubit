﻿#pragma once

#ifdef DELETE
#undef DELETE
#endif

namespace cubit {
enum class Keys {
  UNKNOWN,
  // KEYBOARD
  BACKSPACE,
  TAB,
  ENTER,
  ESCAPE,
  SPACE,
  PAGE_UP,
  PAGE_DOWN,
  END,
  HOME,
  LEFT,
  UP,
  RIGHT,
  DOWN,
  INSERT,
  DELETE,
  KEY_0,
  KEY_1,
  KEY_2,
  KEY_3,
  KEY_4,
  KEY_5,
  KEY_6,
  KEY_7,
  KEY_8,
  KEY_9,
  A,
  B,
  C,
  D,
  E,
  F,
  G,
  H,
  I,
  J,
  K,
  L,
  M,
  N,
  O,
  P,
  Q,
  R,
  S,
  T,
  U,
  V,
  W,
  X,
  Y,
  Z,
  NUM_0,
  NUM_1,
  NUM_2,
  NUM_3,
  NUM_4,
  NUM_5,
  NUM_6,
  NUM_7,
  NUM_8,
  NUM_9,
  NUM_MULTIPLY,
  NUM_ADD,
  NUM_SUBTRACT,
  NUM_DEMICAL,
  NUM_DIVIDE,
  F1,
  F2,
  F3,
  F4,
  F5,
  F6,
  F7,
  F8,
  F9,
  F10,
  F11,
  F12,
  SHIFT,
  CONTROL,
  ALT,
  // MOUSE
  LMOUSE,
  MMOUSE,
  RMOUSE,
  keyCount
};
}
