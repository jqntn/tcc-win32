#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
  auto W = CreateWindow(
    L"Static", L" ", WS_POPUP | WS_SIZEBOX | SS_NOTIFY, 0, 0, 0, 0, 0, 0, 0, 0);

  auto H = GetDC(W);
  ShowWindow(W, 3);

  MSG M;

  while (1) {
    if (PeekMessage(&M, 0, 0, 0, 1))
      DispatchMessage(&M);
  }

  /**/

  puts("Hello, World!");

  return EXIT_SUCCESS;
}