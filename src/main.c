#include <Windows.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "cpu.h"

#define ID_GAME_TICK 1237

LRESULT CALLBACK WindowProc(HWND h_wnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    OutputDebugString(L"WindowProc\n");
    return DefWindowProc(h_wnd, msg, w_param, l_param);
/*
    RECT client_rect;
    GetClientRect(h_wnd, &client_rect);

    switch (msg)
    {
    case WM_QUIT:
        OutputDebugString(L"WM_QUIT\n");
        PostQuitMessage(0);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        OutputDebugString(L"WM_DESTROY\n");
        break;

    case WM_CLOSE:
        PostQuitMessage(0);
        OutputDebugString(L"WM_CLOSE\n");
        break;

    case WM_KEYDOWN:
        OutputDebugString(L"key down\n");
        break;

    case WM_KEYUP:
        OutputDebugString(L"key up\n");
        break;

    case WM_TIMER:
        OutputDebugString(L"timer\n");
        cpu_execute(cpu_obj);
        InvalidateRect(h_wnd, &client_rect, TRUE);
        break;

    case WM_PAINT:
        OutputDebugString(L"Paint\n");
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(h_wnd, &ps);

        int chip_8_to_win32_scale = 16;

        for (unsigned char y = 0; y < 32; ++y)
        {
            for (unsigned char x = 0; x < 64; ++x)
            {
                if (display_obj->pixels[y * 64 + x] == 1)
                {
                    wchar_t buff[256];
                    OutputDebugString(buff);
                    RECT draw_rect;
                    draw_rect.left = chip_8_to_win32_scale * x;
                    draw_rect.top = chip_8_to_win32_scale * y;
                    draw_rect.bottom = chip_8_to_win32_scale * (y + 1);
                    draw_rect.right = chip_8_to_win32_scale * (x + 1);

                    FillRect(hdc, &draw_rect, CreateSolidBrush(RGB(255, 255, 255)));
                }
                else if (display_obj->pixels[y * 64 + x] == 0)
                {
                    wchar_t buff[256];
                    swprintf(buff, 256, L"0 %d %d\n", x, y);
                    OutputDebugString(buff);
                    RECT draw_rect;
                    draw_rect.left = chip_8_to_win32_scale * x;
                    draw_rect.top = chip_8_to_win32_scale * y;
                    draw_rect.bottom = chip_8_to_win32_scale * (y + 1);
                    draw_rect.right = chip_8_to_win32_scale * (x + 1);

                    FillRect(hdc, &draw_rect, CreateSolidBrush(RGB(0, 0, 0)));
                }
            }
        }

        EndPaint(h_wnd, &ps);
        break;

    default:
        break;
    }
*/
}

int WINAPI wWinMain(_In_ HINSTANCE h_instance, _In_opt_ HINSTANCE previous_instance, _In_ PWSTR cmd_line, _In_ int cmd_show)
{
    OutputDebugString(L"Hello Chip8\n");

    WNDCLASS wc = {0};
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = h_instance;
    wc.lpszClassName = L"Chip8";
    wc.hCursor = LoadCursor(h_instance, IDC_ARROW);

    if (!RegisterClass(&wc))
    {
        return EXIT_FAILURE;
    }

    HWND h_wnd = CreateWindow(
        L"Chip8",
        L"Chip8",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1040,
        551,
        NULL,
        NULL,
        h_instance,
        NULL);

    if (!h_wnd)
    {
        return EXIT_FAILURE;
    }

    ShowWindow(h_wnd, cmd_show);
    UpdateWindow(h_wnd);

    char *path = "./build32/vscode/debug/IBM_Logo.ch8";
    cpu *c = cpu_create(h_instance, h_wnd);

    SetTimer(h_wnd, ID_GAME_TICK, 1000, NULL);

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    RECT client_rect;
    GetClientRect(h_wnd, &client_rect);

    BOOL gm;

    while ((gm = GetMessage(&msg, h_wnd, 0, 0)) != 0)
    {
        if (gm == -1)
        {
            break;
        }
        else
        {
            if (msg.message == WM_PAINT)
            {
                OutputDebugString(L"Paint\n");
            }
            else if (msg.message == WM_TIMER)
            {
                OutputDebugString(L"Timer\n");
                InvalidateRect(h_wnd, &client_rect, TRUE);
            }
            else
            {
                DispatchMessage(&msg);
            }
        }

        DefWindowProc(msg.hwnd, msg.message, msg.lParam, msg.wParam);
    }

    cpu_destroy(c);

    KillTimer(h_wnd, ID_GAME_TICK);
    DestroyWindow(h_wnd);

    return EXIT_SUCCESS;
}