#include "QPCTimer.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace cubit {
namespace impl {

QPCFrequency::QPCFrequency() {
  LARGE_INTEGER largeInteger;
  QueryPerformanceFrequency(&largeInteger);
  frequency = largeInteger.QuadPart;
}

static int64_t getCounter() {
  LARGE_INTEGER largeInteger;
  QueryPerformanceCounter(&largeInteger);
  return largeInteger.QuadPart;
}

void QPCTimer::start() { startTime = getCounter(); }

float QPCTimer::get() {
  uint64_t counter = getCounter();
  return ((float)(counter - startTime)) / (float)frequency;
}

}  // namespace impl
}  // namespace cubit
