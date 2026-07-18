#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <math.h>
#include "types.h"
#include "framebuffer.h"
#include "noise.h"
#include "draw.h"
#include "color.h"
#include "tests.h"
#include "vecmath.h"
#include "camera.h"
#include "config.h"
#include "obj.h"
#include "trans.h"

framebuffer fb;
camera cam;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    init(&fb);
    initCam(&cam);

    fill(&fb, rgb(183, 183, 183));
    vec3 light = {-1.0f, -1.0f, 2.0f};
    tri3 tris[] = {
        {{{-5.0f, -1.8f, 3.0f}, {-5.0f, -1.8f, 8.0f}, {5.0f, -1.8f, 3.0f}}},
        {{{-5.0f, -1.8f, 8.0f}, {5.0f, -1.8f, 8.0f}, {5.0f, -1.8f, 3.0f}}}};
    mesh3 base = {.tris = tris, .count = sizeof(tris) / sizeof(tris[0])};
    drawMesh3d(&fb, &cam, base, light, ORANGE);
    mesh3 sonic;
    parse_obj("assets/Sonic.obj", &sonic);
    moveMesh(&sonic, 0, 0, 3.5);
    rotateMeshEuler(&sonic, 90, -45, 0);
    drawMesh3d(&fb, &cam, base, light, rgb(140, 183, 76));
    drawMesh3d(&fb, &cam, sonic, light, rgb(89, 135, 199));
    render_image(&fb);
    render_image_depth(&fb);

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
    BITMAPINFO bmi = {0};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = fb.width;
    bmi.bmiHeader.biHeight = -fb.height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    ShowWindow(hwnd, nCmdShow);

    int running = 1;
    float t = 0.0f;

    LARGE_INTEGER ticksPerSecond, lastTickCount, currentTickCount;
    QueryPerformanceFrequency(&ticksPerSecond);
    QueryPerformanceCounter(&lastTickCount);
    float dt = 0;

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
        t += 2 * dt;
        float r = 3.0f;
        clear_framebuffer(&fb);
        light = (vec3){r * cosf(t), -1.0f, r * (sinf(t) + 3)};

        fill(&fb, rgb(183, 183, 183));
        // rotateMeshEuler(&sonic, 0,  60 * dt, 0);
        drawMesh3d(&fb, &cam, base, light, rgb(140, 183, 76));
        drawMesh3d(&fb, &cam, sonic, light, rgb(89, 135, 199));
        // drawMesh3d(&fb, &cam, tip, light, GREEN);

        // drawMesh3d(&fb, &cam, cock, light, PINK);

        // drawMesh3d(&fb, &cam, ball, light, RED);

        // drawMesh3d(&fb, &cam, ball_blue, light, BLUE);

        HDC hdc = GetDC(hwnd);
        StretchDIBits(
            hdc,
            0, 0, fb.width, fb.height,
            0, 0, fb.width, fb.height,
            fb.pixels, &bmi,
            DIB_RGB_COLORS, SRCCOPY);
        ReleaseDC(hwnd, hdc);
        // Evaluate Delta Time 
        {
            QueryPerformanceCounter(&currentTickCount);
            uint64_t elapsedTicks = currentTickCount.QuadPart - lastTickCount.QuadPart;
            // Convert to microseconds to not lose precision
            uint64_t elapsedTimeInMicroseconds = (elapsedTicks * 1000000) / ticksPerSecond.QuadPart;
            
            lastTickCount = currentTickCount;

            // Time in milliseconds
            dt = (float)elapsedTimeInMicroseconds / 1000.0f;

            // Time in seconds
            dt /= 1000.0f;
        }
    }
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    BITMAPINFO bmi = {0};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = fb.width;
    bmi.bmiHeader.biHeight = -fb.height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

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