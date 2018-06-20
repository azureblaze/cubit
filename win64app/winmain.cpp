#include <cubit/cubit.h>

int __stdcall WinMain(
    void *hInstance,
    void *hPrevInstance,
    const char *lpCmdLine,
    int nCmdShow) {
  auto application =
      cubit::createWin64Application((intptr_t)hInstance, lpCmdLine);
  application->initialize();
  return application->start();
}