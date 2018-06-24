#include "DxResult.h"

#include <stdexcept>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace cubit {
namespace impl {
void checkResult(int result) {
  if (result >= 0) {
    return;
  }
  char* buffer;
  FormatMessageA(
      FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
      nullptr,
      result,
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      (LPSTR)&buffer,
      0,
      nullptr);

  std::string error(buffer);
  LocalFree(&buffer);

  throw new std::exception(error.c_str());
}
}  // namespace impl
}  // namespace cubit
