#include "DxResult.h"

#include <sstream>
#include <stdexcept>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <d3d11.h>

#include <cubit/core/exception.h>

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

  throw new Exception(error.c_str());
}

void checkResult(int result, ID3DBlob* blob) {
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

  std::stringstream error;
  error << buffer;
  LocalFree(&buffer);

  if (blob != nullptr) {
    error << "\n"
          << std::string(
                 (const char*)blob->GetBufferPointer(), blob->GetBufferSize());
  }
  std::string str = error.str();
  throw new Exception(str.c_str());
}

}  // namespace impl
}  // namespace cubit
