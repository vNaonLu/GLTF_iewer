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
		vnaon_gl::GLcontroller *_p_glcontroller;

		// Information of camera.
		vnaon_common::camera _camera;
		double _near;
		double _far;

		// Rendering entity.
		bool _first_render;
		std::vector<p_scenes_object> entities;

	public:
		scenes_engine();
		~scenes_engine();

		//Main Function.
		void draw(glm::vec2 arg_viewport, glm::vec3 arg_frustum_pos);

		void adjust_viewport(const int &w, const int &h);

	private:
		void _init();

		void _set_camera(glm::vec2 arg_viewport, glm::vec3 arg_pos, double arg_near, double arg_far);

		void _init_render(); //only once.

	};

}