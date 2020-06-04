#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "main_context.h"
#include "Rect.h"

namespace vnaon_scenes {
	// ---
	view_controller *render_context::controller_p = nullptr;
	render_context::render_context(const std::string &arg_name, const int &arg_width, const int &arg_height) {
		window_p = nullptr;
		window_name = arg_name;
		view_port.right = arg_width;
		view_port.bottom = arg_height;
	}
	render_context::~render_context() {
		terminate();

		if ( render_context::controller_p != nullptr ) {
			render_context::controller_p->close();
			delete  render_context::controller_p;
		}
	}
	void render_context::render() {
		if ( !init() ) return;

		set_swap_interval(1);
		while ( alive() ) {
			render_context::controller_p->render();
			swap_buffer();
		}
	}
	bool render_context::create_window() {
		using namespace vnaon_geometry;

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		int width = (int) Rect::width(view_port);
		int height = (int) Rect::height(view_port);
		window_p = glfwCreateWindow(width, height, window_name.c_str(), nullptr, nullptr);

		if ( window_p == nullptr )
			return false;
		else
			return true;

	}
	bool render_context::init_window() {
		if ( window_p == nullptr )
			return false;

		glfwMakeContextCurrent(window_p);

		if ( !gladLoadGLLoader((GLADloadproc) glfwGetProcAddress) )
			return false;

		return true;
	}
	bool render_context::alive() const {
		return  !glfwWindowShouldClose(window_p);
	}
	void render_context::swap_buffer() {
		glfwSwapBuffers(window_p);
		glfwPollEvents();
	}
	void render_context::set_swap_interval(int interval) {
		glfwSwapInterval(interval);
	}
	void render_context::terminate() {
		glfwTerminate();
		if ( window_p != nullptr ) glfwDestroyWindow(window_p);
	}
	bool render_context::init() {
		render_context::controller_p = new vnaon_scenes::view_controller();
		create_window();
		attach_event();
		init_window();

		bool ret = true;
		return ret;
	}
	void render_context::attach_event() {
		glfwSetFramebufferSizeCallback(window_p, onResize);
	}
	void render_context::process() {

		while ( stop_if_need() ) {
		}
	}
	void render_context::onResize(GLFWwindow *window, int width, int height) {
		render_context::controller_p->adjust_viewer(width, height);
	}
}