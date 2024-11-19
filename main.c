#pragma comment(lib, "user32")
#pragma comment(lib, "gdi32")
#pragma comment(lib, "opengl32")

#define MSAA_0X 9
#define MSAA_2X 25
#define MSAA_4X 41
#define MSAA_8X 57
#define MSAA_16X 73

#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#undef NDEBUG
#include <assert.h>

__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
__declspec(dllexport) DWORD AmdPowerXpressRequestHighPerformance = 0x00000001;

int
main(void)
{
  puts("compiled with tiny c compiler 0.9.27");

  HMODULE h_user32 = LoadLibraryA("user32");
  assert(NULL != h_user32);

  FARPROC p_SetProcessDPIAware = GetProcAddress(h_user32, "SetProcessDPIAware");
  assert(NULL != p_SetProcessDPIAware);
  assert(TRUE == p_SetProcessDPIAware());

  HWND h_wnd = CreateWindowA(
    "Static", NULL, WS_POPUP | SS_NOTIFY, 0, 0, 0, 0, NULL, NULL, NULL, NULL);
  assert(NULL != h_wnd);

  HDC h_dc = GetDC(h_wnd);
  assert(NULL != h_dc);

  BOOL _ = ShowWindow(h_wnd, SW_MAXIMIZE);

  PIXELFORMATDESCRIPTOR ppfd = { 0 };
  assert(TRUE == SetPixelFormat(h_dc, MSAA_0X, &ppfd));

  HGLRC h_glrc = wglCreateContext(h_dc);
  assert(NULL != h_glrc);
  assert(TRUE == wglMakeCurrent(h_dc, h_glrc));

  MSG msg;

  while (TRUE == SwapBuffers(h_dc)) {
    if (TRUE == PeekMessageA(&msg, h_wnd, 0, 0, 1)) {
      LRESULT _ = DispatchMessageA(&msg);
    }
  }

  return EXIT_SUCCESS;
}