#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <math.h>
#include <stdbool.h>
#include "types.h"
#include "framebuffer.h"
#include "draw.h"
#include "color.h"
#include "vecmath.h"
#include "camera.h"
#include "config.h"
#include "obj.h"
#include "trans.h"

framebuffer fb;
BITMAPINFO bmi = {0};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

LARGE_INTEGER ticksPerSecond, lastTickCount, currentTickCount;

uint64_t get_delta_time()
{
  QueryPerformanceCounter(&currentTickCount);
  uint64_t elapsedTicks = currentTickCount.QuadPart - lastTickCount.QuadPart;
  // Convert to microseconds to not lose precision
  uint64_t elapsedTimeInMicroseconds = (elapsedTicks * 1000000) / ticksPerSecond.QuadPart;
  lastTickCount = currentTickCount;
  return elapsedTimeInMicroseconds;
}

bool is_running()
{
  MSG msg;
  while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
  {
    if (msg.message == WM_QUIT)
      return false;
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return true;
}
HWND hwnd;
HDC memDC;
void draw_frame()
{
  HDC hdc = GetDC(hwnd);
  BitBlt(hdc, 0, 0, fb.width, fb.height, memDC, 0, 0, SRCCOPY);
  ReleaseDC(hwnd, hdc);
}

void RB_create_window()
{
  HDC windowDC = GetDC(hwnd);
  memDC = CreateCompatibleDC(windowDC);
  HBITMAP hBitmap = CreateDIBSection(windowDC, &bmi, DIB_RGB_COLORS, (void **)&fb.pixels, NULL, 0);
  SelectObject(memDC, hBitmap);
  ReleaseDC(hwnd, windowDC);
}

void RB_set_title(wchar_t title[64])
{
  SetWindowTextW(hwnd, title);
}

extern int main();

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
  // model m;

  init_framebuffer(&fb);
  const wchar_t CLASS_NAME[] = L"Sample Window Class";

  WNDCLASS wc = {0};

  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;

  RegisterClass(&wc);

  RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

  hwnd = CreateWindowEx(
      0, CLASS_NAME, L"Rasterbator demo",
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT,
      rect.right - rect.left,
      rect.bottom - rect.top,
      NULL, NULL, hInstance, NULL);

  if (hwnd == NULL)
  {
    return 0;
  }
  bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmi.bmiHeader.biWidth = fb.width;
  bmi.bmiHeader.biHeight = -fb.height;
  bmi.bmiHeader.biPlanes = 1;
  bmi.bmiHeader.biBitCount = 32;
  bmi.bmiHeader.biCompression = BI_RGB;

  ShowWindow(hwnd, nCmdShow);

  QueryPerformanceFrequency(&ticksPerSecond);
  QueryPerformanceCounter(&lastTickCount);
  return main();
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;

  case WM_PAINT:
  {
    PAINTSTRUCT ps;
    BeginPaint(hwnd, &ps);
    EndPaint(hwnd, &ps);
  }
    return 0;
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}