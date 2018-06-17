#include <cubit/cubit.h>

int __stdcall WinMain(
    void *hInstance,
    void *hPrevInstance,
    const char *lpCmdLine,
    int nCmdShow) {
  return cubit::createWin64Application(hInstance, lpCmdLine)->start();
}