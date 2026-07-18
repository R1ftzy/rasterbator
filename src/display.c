#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <math.h>
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
camera cam;
BITMAPINFO bmi = {0};

typedef struct
{
  vec3 light;
  mesh3 base;
  mesh3 sonic;
  float speed;
  float dt;
} model;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void init(model *m)
{
  init_framebuffer(&fb);
  initCam(&cam);
  m->light = (vec3){-1.0f, -1.0f, 2.0f};
  fill(&fb, rgb(183, 183, 183));
  tri3 tris[] = {
      {{{-5.0f, -1.8f, 3.0f}, {-5.0f, -1.8f, 8.0f}, {5.0f, -1.8f, 3.0f}}},
      {{{-5.0f, -1.8f, 8.0f}, {5.0f, -1.8f, 8.0f}, {5.0f, -1.8f, 3.0f}}}};
  m->base.tris = malloc(sizeof(tris));
  memcpy(m->base.tris, tris, sizeof(tris));
  m->base.count = sizeof(tris) / sizeof(tris[0]);
  parse_obj("assets/Sonic.obj", &m->sonic);
  moveMesh(&m->sonic, 0, 0, 3.5);
  rotateMeshEuler(&m->sonic, 90, -45, 0);
  m->dt = 0;
  m->speed = 0.0;
}

void update(model *m)
{
  m->speed += 2 * m->dt;
  float r = 3.0f;
  m->light = (vec3){r * cosf(m->speed), -1.0f, r * (sinf(m->speed) + 3)};

  clear_framebuffer(&fb, rgb(183, 183, 183));

  rotateMeshEuler(&m->sonic, 0, 60 * m->dt, 0);
  drawMesh3d(&fb, &cam, m->base, m->light, rgb(140, 183, 76));
  drawMesh3d(&fb, &cam, m->sonic, m->light, rgb(89, 135, 199));
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
  model m;
  init(&m);

  const wchar_t CLASS_NAME[] = L"Sample Window Class";

  WNDCLASS wc = {0};

  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;

  RegisterClass(&wc);

  RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

  HWND hwnd = CreateWindowEx(
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

  int running = 1;

  LARGE_INTEGER ticksPerSecond, lastTickCount, currentTickCount;
  QueryPerformanceFrequency(&ticksPerSecond);
  QueryPerformanceCounter(&lastTickCount);
  int frame_count = 0;
  // Game loop
  while (running)
  {
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        running = 0;
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

    update(&m);

    // framebuffer to window
    {
      HDC hdc = GetDC(hwnd);
      StretchDIBits(
          hdc,
          0, 0, fb.width, fb.height,
          0, 0, fb.width, fb.height,
          fb.pixels, &bmi,
          DIB_RGB_COLORS, SRCCOPY);
      ReleaseDC(hwnd, hdc);
    }

    // Evaluate Delta Time
    {
      QueryPerformanceCounter(&currentTickCount);
      uint64_t elapsedTicks = currentTickCount.QuadPart - lastTickCount.QuadPart;
      // Convert to microseconds to not lose precision
      uint64_t elapsedTimeInMicroseconds = (elapsedTicks * 1000000) / ticksPerSecond.QuadPart;

      lastTickCount = currentTickCount;

      // Time in milliseconds
      m.dt = (float)elapsedTimeInMicroseconds / 1000.0f;

      // Time in seconds
      m.dt /= 1000.0f;
    }

    // Checking Framerate
    if (frame_count % 30 == 0)
    {
      wchar_t title[64];
      swprintf(title, 64, L"rasterbator | %.0f fps", 1.0f / m.dt);
      SetWindowTextW(hwnd, title);
    }
    frame_count++;
  }
  return 0;
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
    HDC hdc = BeginPaint(hwnd, &ps);

    StretchDIBits(
        hdc,
        0, 0,
        fb.width,
        fb.height,
        0, 0,
        fb.width,
        fb.height,
        fb.pixels,
        &bmi,
        DIB_RGB_COLORS,
        SRCCOPY);
    EndPaint(hwnd, &ps);
  }
    return 0;
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}