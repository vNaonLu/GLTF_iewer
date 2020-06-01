#pragma once
#include <vector>
#include <string>

#include "Rect.h"
#include "ViewController.h"
#include "EventContext.h"

namespace vnaon_scenes {
	/*
	 * render_context
	 * The context between the OpenGL and the controller.
	 */
	class render_context : public vnaon_common::_i_event_context {
	public:
		static view_controller *controller_p;
	private:
		GLFWwindow *window_p;
		std::string window_name;

		vnaon_geometry::Rect view_port;
	public:
		render_context(const std::string &arg_name, const int &arg_width, const int &arg_height);
		~render_context();
		// the main function of render_context.
		void render();
	private:
		bool init();
		bool create_window();
		bool init_window();
		bool alive() const;
		void swap_buffer();
		void set_swap_interval(int interval);
		void terminate();
		void attach_event();
		virtual void process() override;
	public:
		static void onResize(GLFWwindow *window, int width, int height);

	};

}