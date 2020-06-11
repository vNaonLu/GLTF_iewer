#include <functional>
#include <Windows.h>
#include <glad/glad.h>
#include <gl/glext.h>
#include <gl/wglext.h>

#include "main_context.h"
#include "_DEBUG_OBJECT.hpp"

namespace vnaon_scenes {

	render_context::render_context(HINSTANCE arg_hInstance, HWND arg_hWnd, int arg_width, int arg_height) : vnaon_common::_i_event_context() {
		this->p_controller = nullptr;
		this->_hInstance = arg_hInstance;
		this->_hWnd = arg_hWnd;
		this->_device_context = nullptr;
		this->_render_context = nullptr;
		this->_viewport = glm::ivec2(arg_width, arg_height);
	}

	render_context::~render_context() {

	}

	bool render_context::init_wglcontext() {
		//this->_hInstance = GetModuleHandle(NULL);
		WNDCLASS window_class;
		ZeroMemory(&window_class, sizeof(window_class));
		window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		window_class.lpfnWndProc = fake_procedure;
		window_class.hInstance = this->_hInstance;
		window_class.lpszClassName = TEXT("FAKE");
		RegisterClass(&window_class);

		HWND fake_wnd = CreateWindow(TEXT("FAKE"), TEXT("GLTF Viewer"), WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE, 0, 0, 1, 1, NULL, NULL, this->_hInstance, NULL);
		HDC fake_device_context = GetDC(fake_wnd);

		PIXELFORMATDESCRIPTOR descriptor;
		ZeroMemory(&descriptor, sizeof(descriptor));
		descriptor.nSize = sizeof(descriptor);
		descriptor.nVersion = 1;
		descriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_DRAW_TO_BITMAP | PFD_SUPPORT_OPENGL | PFD_GENERIC_ACCELERATED | PFD_DOUBLEBUFFER | PFD_SWAP_LAYER_BUFFERS;
		descriptor.iPixelType = PFD_TYPE_RGBA;
		descriptor.cColorBits = 32;
		descriptor.cRedBits = 8;
		descriptor.cGreenBits = 8;
		descriptor.cBlueBits = 8;
		descriptor.cAlphaBits = 8;
		descriptor.cDepthBits = 32;
		descriptor.cStencilBits = 8;

		int pixel_format = ChoosePixelFormat(fake_device_context, &descriptor);
		SetPixelFormat(fake_device_context, pixel_format, &descriptor);

		HGLRC fake_render_context = wglCreateContext(fake_device_context);
		wglMakeCurrent(fake_device_context, fake_render_context);

		PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC) wglGetProcAddress("wglGetExtensionsStringARB");
		PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC) wglGetProcAddress("wglChoosePixelFormatARB");
		PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC) wglGetProcAddress("wglCreateContextAttribsARB");
		PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC) wglGetProcAddress("wglSwapIntervalEXT");


		if ( !gladLoadGL() ) {
			DEBUGConsole::log("Failed to load OpenGL");
			return false;
		}

		wglMakeCurrent(fake_device_context, NULL);
		wglDeleteContext(fake_render_context);
		ReleaseDC(fake_wnd, fake_device_context);
		DestroyWindow(fake_wnd);

		//this->_hWnd = CreateWindow(TEXT("GLTF Viewer"), TEXT("GLTF Viewer"), WS_OVERLAPPED | WS_SYSMENU | WS_VISIBLE, 0, 0, 800, 600, NULL, NULL, this->_hInstance, NULL);
		this->_device_context = GetDC(this->_hWnd);

		int pixel_format_arb;
		UINT pixel_formats_found;
		int pixel_attributes[] = {
			WGL_SUPPORT_OPENGL_ARB, TRUE,
			WGL_DRAW_TO_WINDOW_ARB, TRUE,
			WGL_DRAW_TO_BITMAP_ARB, TRUE,
			WGL_DOUBLE_BUFFER_ARB, TRUE,
			WGL_SWAP_LAYER_BUFFERS_ARB, TRUE,
			WGL_COLOR_BITS_ARB, 32,
			WGL_RED_BITS_ARB, 8,
			WGL_GREEN_BITS_ARB, 8,
			WGL_BLUE_BITS_ARB, 8,
			WGL_ALPHA_BITS_ARB, 8,
			WGL_DEPTH_BITS_ARB, 32,
			WGL_STENCIL_BITS_ARB, 8,
			WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			0
		};
		if ( wglChoosePixelFormatARB(this->_device_context, pixel_attributes, NULL, 1, &pixel_format_arb, &pixel_formats_found) == FALSE ) {
			return false;
		}
		if ( SetPixelFormat(this->_device_context, pixel_format, &descriptor) == FALSE ) {
			return false;
		}
		

		GLint context_attributes[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
			WGL_CONTEXT_MINOR_VERSION_ARB, 0,
			0
		};

		this->_render_context = wglCreateContextAttribsARB(this->_device_context, 0, context_attributes);

		if ( !this->_render_context ) {
			DEBUGConsole::log("Failed to create the render context.");
			return false;
		}

		wglMakeCurrent(this->_device_context, this->_render_context);
		wglSwapIntervalEXT(1);

		return true;
	}

	bool render_context::init() {
		this->p_controller = new vnaon_scenes::view_controller();

		bool ret = true;
		return ret;
	}

	void render_context::process() {

		if ( init_wglcontext() && init() ) {
			while ( is_alive() ) {

				p_controller->render();

				SwapBuffers(_device_context);
			}
		}

		if ( p_controller != nullptr ) {
			p_controller->close();
			delete p_controller;
		}

		PostQuitMessage(0);
	}

	LRESULT render_context::fake_procedure(HWND window_handle, UINT message, WPARAM param_w, LPARAM param_l) {
		switch ( message ) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(window_handle, message, param_w, param_l);
	}

	void render_context::onResize(int width, int height) {
		p_controller->adjust_viewer(width, height);
	}
}