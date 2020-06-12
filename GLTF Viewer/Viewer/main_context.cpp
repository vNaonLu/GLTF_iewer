#include <functional>

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
		this->wglChoosePixelFormatARB = NULL;
		this->wglCreateContextAttribsARB = NULL;
	}

	render_context::~render_context() {

	}

	bool render_context::init_opengl_extensions() {
		WNDCLASSA window_class;
		ZeroMemory(&window_class, sizeof(window_class));
		window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		window_class.lpfnWndProc = fake_procedure;
		window_class.hInstance = GetModuleHandle(NULL);
		window_class.hCursor = LoadCursor(0, IDC_ARROW),
		window_class.lpszClassName = "dummy";
		if ( !RegisterClassA(&window_class) ) {
			DEBUGConsole::log("Failed to register dummy OpenGL window.");
			return false;
		}

		HWND dummy_wnd = CreateWindowExA(
			0,
			window_class.lpszClassName,
			"dummy window",
			0,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			0,
			0,
			window_class.hInstance,
			0
		);
		if ( !dummy_wnd ) {
			DEBUGConsole::log("Failed to create dummy OpenGL window.");
			return false;
		}
		HDC dummy_device_context = GetDC(dummy_wnd);

		PIXELFORMATDESCRIPTOR pfd;
		ZeroMemory(&pfd, sizeof(pfd));
		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_GENERIC_ACCELERATED;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.iLayerType = PFD_MAIN_PLANE,
		pfd.cColorBits = 32;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;

		int pixel_format = ChoosePixelFormat(dummy_device_context, &pfd);
		if ( !pixel_format ) {
			DEBUGConsole::log("Failed to find a suitable pixel format.");
			return false;
		}
		if ( !SetPixelFormat(dummy_device_context, pixel_format, &pfd) ) {
			DEBUGConsole::log("Failed to set the pixel format.");
			return false;
		}

		HGLRC dummy_render_context = wglCreateContext(dummy_device_context);
		if ( !dummy_render_context ) {
			DEBUGConsole::log("Failed to create a dummy OpenGL rendering context.");
			return false;
		}

		if ( !wglMakeCurrent(dummy_device_context, dummy_render_context) ) {
			DEBUGConsole::log("Failed to activate dummy OpenGL rendering context.");
			return false;
		}

		this->wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC) wglGetProcAddress("wglChoosePixelFormatARB");
		this->wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC) wglGetProcAddress("wglCreateContextAttribsARB");
		this->wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC) wglGetProcAddress("wglSwapIntervalEXT");

		wglMakeCurrent(dummy_device_context, NULL);
		wglDeleteContext(dummy_render_context);
		ReleaseDC(dummy_wnd, dummy_device_context);
		DestroyWindow(dummy_wnd);

		return true;
	}

	bool render_context::init_opengl() {
		if ( !init_opengl_extensions() )
			return false;

		this->_device_context = GetDC(this->_hWnd);

		int pixel_attributes[] = {
			WGL_DRAW_TO_WINDOW_ARB,     GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB,     GL_TRUE,
			WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
			WGL_SWAP_METHOD_ARB,		WGL_SWAP_EXCHANGE_ARB,
			WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
			WGL_DOUBLE_BUFFER_ARB,      GL_TRUE,
			WGL_SAMPLE_BUFFERS_ARB,		GL_TRUE,
			WGL_SAMPLES_ARB,			4,
			WGL_COLOR_BITS_ARB,         32,
			WGL_DEPTH_BITS_ARB,         24,
			WGL_STENCIL_BITS_ARB,       8,
			0
		};
		int pixel_format;
		UINT num_formats;
		this->wglChoosePixelFormatARB(this->_device_context, pixel_attributes, NULL, 1, &pixel_format, &num_formats);

		if ( !num_formats ) {
			DEBUGConsole::log("Failed to set the pixel format.");
			return false;
		}

		PIXELFORMATDESCRIPTOR pfd;
		if ( !SetPixelFormat(this->_device_context, pixel_format, &pfd) ) {
			DEBUGConsole::log("Failed to set the pixel format.");
			return false;
		}		

		GLint context_attributes[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
			WGL_CONTEXT_MINOR_VERSION_ARB, 6,
			0
		};

		this->_render_context = this->wglCreateContextAttribsARB(this->_device_context, 0, context_attributes);

		if ( !this->_render_context ) {
			DEBUGConsole::log("Failed to create the render context.");
			return false;
		}

		if ( !wglMakeCurrent(this->_device_context, this->_render_context) ) {
			DEBUGConsole::log("Failed to activate the render context.");
			return false;
		}


		if ( !gladLoadGL() ) {
			DEBUGConsole::log("Failed to load OpenGL");
			return false;
		}

		ShowWindow(this->_hWnd, SW_SHOW);

		this->wglSwapIntervalEXT(1);

		return true;
	}

	bool render_context::init() {
		this->p_controller = new vnaon_scenes::view_controller(_viewport.x, _viewport.y);

		bool ret = true;
		return ret;
	}

	void render_context::process() {

		if ( init_opengl() && init() ) {
			SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
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
		_viewport = glm::ivec2(width, height);
		p_controller->adjust_viewer(width, height);
	}
}