#include "Win64Util.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

using namespace std;

namespace cubit {
namespace impl {
wstring Win64Util::utf8ToWchar(string_view utf8) {
  int length = MultiByteToWideChar(
      CP_UTF8, MB_PRECOMPOSED, utf8.data(), utf8.size(), nullptr, 0);
  wstring result = wstring(length, L'\0');
  MultiByteToWideChar(
      CP_UTF8, MB_PRECOMPOSED, utf8.data(), utf8.size(), &result[0], length);
  return move(result);
}
}  // namespace impl
}  // namespace cubit