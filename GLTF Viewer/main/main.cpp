#include <Windows.h>
#include <Windowsx.h>
#include "..\Viewer\main_context.h"
#include "..\Viewer\debug_tools.hpp"

#pragma warning (disable: 4996)
vnaon_scenes::RenderContext *g_context = nullptr;

LRESULT CALLBACK WndProc(HWND arg_hWnd, UINT arg_msg, WPARAM arg_wParam, LPARAM arg_lParam) {
    if ( g_context != nullptr && g_context->p_controller != nullptr ) {
        switch ( arg_msg ) {
        case WM_LBUTTONUP:
        {
            int xPos = GET_X_LPARAM(arg_lParam);
            int yPos = GET_Y_LPARAM(arg_lParam);
            g_context->p_controller->OnLeftMouseUp(xPos, yPos);
        }
        return 0;
        //----
        case WM_LBUTTONDOWN:
        {
            int xPos = GET_X_LPARAM(arg_lParam);
            int yPos = GET_Y_LPARAM(arg_lParam);
            g_context->p_controller->OnLeftMouseDown(xPos, yPos);
        }
        return 0;
        //----
        case WM_MOUSEMOVE:
        {
            int xPos = GET_X_LPARAM(arg_lParam);
            int yPos = GET_Y_LPARAM(arg_lParam);
            g_context->p_controller->OnMouseMove(xPos, yPos);
        }
        return 0;
        //----
        case WM_SIZING:
        {            
            RECT *view_rect;
            view_rect = (RECT *) arg_lParam;
            g_context->p_controller->OnViewportChange((int)(view_rect->right - view_rect->left), (int)(view_rect->bottom - view_rect->top));
        }
        return 0;
        //----
        case WM_SIZE:
        {
            g_context->p_controller->OnViewportChange(LOWORD(arg_lParam), HIWORD(arg_lParam));
        }
        return 0;
        //----
        case WM_CLOSE:
        {
            g_context->Expire();
        }
        return 0;
        }
        return DefWindowProc(arg_hWnd, arg_msg, arg_wParam, arg_lParam);
    } else {
        switch ( arg_msg ) {
        case WM_CLOSE:
        {
            PostQuitMessage(0);
        }
        return 0;
        }
        return DefWindowProc(arg_hWnd, arg_msg, arg_wParam, arg_lParam);    
    }
}

int WINAPI WinMain(HINSTANCE instance_handle, HINSTANCE prev_instance_handle, PSTR cmd_line, int cmd_show) {
    WNDCLASSEX window_class;
    ZeroMemory(&window_class, sizeof(window_class));
    window_class.cbSize = sizeof(window_class);
    window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    window_class.lpfnWndProc = WndProc;
    window_class.hInstance = instance_handle;
    window_class.hCursor = LoadCursor(0, IDC_ARROW),
    window_class.lpszClassName = "wglWnd";
    RegisterClassEx(&window_class);
    HWND window_handle = CreateWindowEx(
        WS_EX_ACCEPTFILES,
        window_class.lpszClassName,
        "GLTF Viewer",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1280, 1080,
        NULL, NULL,
        instance_handle, NULL
    );
    g_context = new vnaon_scenes::RenderContext(instance_handle, window_handle, 1280, 1080);

    
    ShowWindow(window_handle, cmd_show);
    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    MSG msg;
    while ( g_context->IsValid() ) {
        if ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ) {
            if ( msg.message == WM_QUIT )
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    delete g_context;
    PostQuitMessage(0);

    return 0;
}
