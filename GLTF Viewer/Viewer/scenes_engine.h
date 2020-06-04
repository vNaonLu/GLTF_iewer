#pragma once
#include <chrono>

#include "GLcontroller.h"

namespace vnaon_scenes {

	/*
	An engine used to control and manage render.
	 */
	class scenes_engine {

	private:
		typedef std::chrono::system_clock clock;
		clock::time_point _last_engine_time;
		double _fps;
		double _aspect;

		vnaon_gl::GLcontroller *_p_glcontroller;

		vnaon_gl::p_program _p_skybox_program;
		vnaon_gl::p_skybox _p_skybox;
		vnaon_gl::p_vertex_arr _p_skybox_arr;

	public:
		scenes_engine();
		~scenes_engine();

		//Main Function.
		void draw();

		void adjust_viewport(const int &w, const int &h);

	private:
		void _init();
		bool _init_gl_resource();

		void _clac_fps();

	};

}