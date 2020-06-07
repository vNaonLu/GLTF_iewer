#pragma once
#include <chrono>
#include <vector>



#include "GLcontroller.h"
#include "camera.h"
#include "scenes_object.h"



namespace vnaon_scenes {

	/*
	An engine used to control and manage render.
	 */
	class scenes_engine {

	private:
		typedef std::chrono::system_clock clock;
		clock::time_point _last_engine_time;
		vnaon_gl::GLcontroller *_p_glcontroller;
		double _fps;
		double _degfov;
		double _aspect;

		// Information of camera.
		vnaon_common::camera _camera;
		glm::vec3 _pos;
		double _near;
		double _far;

		// Rendering entity.
		bool _first_render;
		std::vector<p_scenes_object> entities;

	public:
		scenes_engine();
		~scenes_engine();

		//Main Function.
		void draw();

		void adjust_viewport(const int &w, const int &h);

	private:
		void _init();

		void _init_camera();

		void _init_render(); //only once.

		void _clac_fps();


	};

}