#pragma once
#include <chrono>
#include <vector>



#include "gl_manager.h"
#include "common_camera.h"
#include "scenes_entity.h"



namespace vnaon_scenes {

	/*
	An engine used to control and manage Render.
	 */
	class ScenesEngine {

	private:
		vnaon_gl::GLManager *_p_glcontroller;

		// Information of Camera.
		vnaon_common::Camera _camera;
		double _near;
		double _far;

		// Rendering entity.
		bool _first_render;
		std::vector<ScenesEntity_p> entities;

	public:
		ScenesEngine();
		~ScenesEngine();

		//Main Function.
		void Draw(glm::ivec2 arg_viewport, glm::vec3 arg_frustum_pos);

	private:
		void Init();

		void SetCamera(glm::ivec2 arg_viewport, glm::vec3 arg_pos, double arg_near, double arg_far);

		void InitRender(); //only once.

	};

}