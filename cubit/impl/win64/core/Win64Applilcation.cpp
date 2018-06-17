#include "Win64Application.h"

#include <sstream>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
using namespace std;

namespace cubit {
namespace impl {
intptr_t a;

Win64Application::Win64Application(const Spec& spec) : spec(spec) {}

int Win64Application::start() {
  stringstream ss;
  ss << spec.applicationInstance << " " << spec.commandLineArgs;

  MessageBoxA(nullptr, ss.str().c_str(), "test", 0);
  return 0;
}
}  // namespace impl
}  // namespace cubit