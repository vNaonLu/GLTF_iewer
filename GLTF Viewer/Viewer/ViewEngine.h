#pragma once
#include <chrono>

#include "GLcontroller.h"

namespace vnaon_scenes {

	/*
	An engine used to control and manage render.
	 */
	class CViewEngine {

	private:
		typedef std::chrono::system_clock clock;
		clock::time_point _last_engine_time;
		double _fps;

		vnaon_gl::GLcontroller *_p_glcontroller;
		vnaon_gl::p_program test_program;

	public:
		CViewEngine();
		~CViewEngine();

		//Main Function.
		void draw();

		void adjust_viewport(const int &w, const int &h);

	private:
		void _init();

		void _clac_fps();

	};

}