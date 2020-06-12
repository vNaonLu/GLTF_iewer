#include <Windows.h>
#include <Windowsx.h>
#include "..\Viewer\main_context.h"
#include "..\Viewer\_DEBUG_OBJECT.hpp"

#pragma warning (disable: 4996)
vnaon_scenes::render_context *g_context = nullptr;

LRESULT CALLBACK window_procedure(HWND arg_hWnd, UINT arg_msg, WPARAM arg_wParam, LPARAM arg_lParam) {
    if ( g_context != nullptr && g_context->p_controller != nullptr ) {
        switch ( arg_msg ) {
        case WM_LBUTTONUP:
        {
            int xPos = GET_X_LPARAM(arg_lParam);
            int yPos = GET_Y_LPARAM(arg_lParam);
            g_context->p_controller->on_left_mouse_up(xPos, yPos);
        }
        return 0;
        //----
        case WM_LBUTTONDOWN:
        {
            int xPos = GET_X_LPARAM(arg_lParam);
            int yPos = GET_Y_LPARAM(arg_lParam);
            g_context->p_controller->on_left_mouse_down(xPos, yPos);
        }
        return 0;
        //----
        case WM_MOUSEMOVE:
        {
            int xPos = GET_X_LPARAM(arg_lParam);
            int yPos = GET_Y_LPARAM(arg_lParam);
            g_context->p_controller->on_mouse_move(xPos, yPos);
        }
        return 0;
        //----
        case WM_DESTROY:
        {
            g_context->abort();
        }
        return 0;
        }
        return DefWindowProc(arg_hWnd, arg_msg, arg_wParam, arg_lParam);
    } else {
        switch ( arg_msg ) {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
        }
        return 0;
        }
        return DefWindowProc(arg_hWnd, arg_msg, arg_wParam, arg_lParam);    
    }
}

int WINAPI WinMain(HINSTANCE instance_handle, HINSTANCE prev_instance_handle, PSTR cmd_line, int cmd_show) {
    WNDCLASSA window_class;
    ZeroMemory(&window_class, sizeof(window_class));
    window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    window_class.lpfnWndProc = window_procedure;
    window_class.hInstance = instance_handle;
    window_class.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    window_class.hCursor = LoadCursor(0, IDC_ARROW),
    window_class.lpszClassName = "GLTF Viewer";
    window_class.cbClsExtra = 0;
    window_class.cbWndExtra = 0;
    RECT rect;
    ZeroMemory(&rect, sizeof(rect));
    rect.right = 1280;
    rect.bottom = 1080;
    RegisterClassA(&window_class);

    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
    HWND window_handle = CreateWindowExA(
        0,
        window_class.lpszClassName,
        "GLTF Viewer",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        rect.right - rect.left,
        rect.bottom - rect.top,
        0,
        0,
        instance_handle,
        0
    );

    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    g_context = new vnaon_scenes::render_context(instance_handle, window_handle, 1280, 1080);

    MSG msg;
    while ( g_context->is_alive() ) {
        if ( PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE) ) {
            if ( msg.message == WM_QUIT )
                break;
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }
    }

    delete g_context;

    return 0;
}
