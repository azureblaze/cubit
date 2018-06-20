#include "VCDebugLogger.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "Win64Util.h"

using namespace std;
namespace cubit {
namespace impl {
void VCDebugLogger::log(string_view line) {
  OutputDebugString(Win64Util::utf8ToWchar(line).c_str());
}
}  // namespace impl
}  // namespace cubit
