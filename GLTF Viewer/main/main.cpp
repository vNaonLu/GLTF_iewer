#include <Windows.h>
#include <Windowsx.h>
#include "..\Viewer\main_context.h"
#include "..\Viewer\_DEBUG_OBJECT.hpp"

#pragma warning (disable: 4996)
vnaon_scenes::render_context *g_context = nullptr;

LRESULT CALLBACK window_procedure(HWND arg_hWnd, UINT arg_msg, WPARAM arg_wParam, LPARAM arg_lParam) {
    switch ( arg_msg ) {
    case WM_MOUSEMOVE:
    {
        int xPos = GET_X_LPARAM(arg_lParam);
        int yPos = GET_Y_LPARAM(arg_lParam);
        DEBUGConsole::log("Mouse Move: (x:" + std::to_string(xPos) + ", y:" + std::to_string(yPos) + ")");
    }
    break;
    //----
    case WM_DESTROY:
    {
        g_context->abort();
        PostQuitMessage(0);
    }
    break;
    //----
    default:
        return DefWindowProc(arg_hWnd, arg_msg, arg_wParam, arg_lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE instance_handle, HINSTANCE prev_instance_handle, PSTR cmd_line, int cmd_show) {
    WNDCLASS window_class;
    ZeroMemory(&window_class, sizeof(window_class));
    window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    window_class.lpfnWndProc = window_procedure;
    window_class.hInstance = instance_handle;
    window_class.lpszClassName = TEXT("GLTF Viewer");
    RegisterClass(&window_class);
    HWND window_handle = CreateWindow(TEXT("GLTF Viewer"), TEXT("GLTF Viewer"), WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE, 0, 0, 1280, 1080, NULL, NULL, instance_handle, NULL);

    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    g_context = new vnaon_scenes::render_context(instance_handle, window_handle, 800, 600);

    ShowWindow(window_handle, SW_SHOW);

    MSG msg;
    while ( true ) {
        if ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ) {
            if ( msg.message == WM_QUIT )
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    delete g_context;

    return 0;
}
