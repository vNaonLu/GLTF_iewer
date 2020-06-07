#pragma once
#include <chrono>



#include "GLcontroller.h"
#include "camera.h"



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
		glm::vec3 _dir;
		glm::vec3 _ahd;
		double _near;
		double _far;

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
		void _init_camera();

		void _clac_fps();


	};

}