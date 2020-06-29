#pragma once
#include <vector>
#include <string>
#include <Windows.h>
#include <glad/glad.h>
#include <gl/glext.h>
#include <gl/wglext.h>
#include <glm/vec2.hpp>



#include "scenes_controller.h"
#include "common_context.h"



namespace vnaon_scenes {



	/// <summary>
	/// The context between the OpenGL and the controller.
	/// </summary>
	class RenderContext : public vnaon_common::EventContext {
	public:
		ScenesViewController *p_controller;
	private:
		HINSTANCE _hInstance;
		HWND _hWnd;
		HDC _device_context;
		HGLRC _render_context;
		glm::ivec2 _viewport;

		PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
		PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
		PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
	public:
		RenderContext(HINSTANCE arg_hInstance, HWND arg_hWnd, int arg_width, int arg_height);
		~RenderContext();
	private:
		bool InitOpenGLExtensions();
		bool InitOpenGL();
		bool Init();
		virtual void Process() override;
	public:		
		static LRESULT CALLBACK DummyProc(HWND window_handle, UINT message, WPARAM param_w, LPARAM param_l);

	};

}