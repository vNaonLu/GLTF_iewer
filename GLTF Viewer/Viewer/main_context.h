#pragma once
#include <vector>
#include <string>
#include <glm\vec2.hpp>



#include "scenes_controller.h"
#include "common_context.h"



namespace vnaon_scenes {



	/// <summary>
	/// The context between the OpenGL and the controller.
	/// </summary>
	class render_context : public vnaon_common::_i_event_context {
	public:
		view_controller *p_controller;
	private:
		HINSTANCE _hInstance;
		HWND _hWnd;
		HDC _device_context;
		HGLRC _render_context;
		glm::ivec2 _viewport;
	public:
		render_context(HINSTANCE arg_hInstance, HWND arg_hWnd, int arg_width, int arg_height);
		~render_context();
	private:
		bool init_wglcontext();
		bool init();
		virtual void process() override;
	public:		
		static LRESULT CALLBACK fake_procedure(HWND window_handle, UINT message, WPARAM param_w, LPARAM param_l);
		void onResize(int width, int height);

	};

}