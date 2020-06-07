#pragma once
#include <memory>



#include "GLcontroller.h"
#include "camera.h"



namespace vnaon_scenes {

	class scenes_object;
	typedef std::shared_ptr<scenes_object> p_scenes_object;


	class scenes_object {
		
	protected:
		vnaon_gl::p_vertex_arr p_drawing_vertex_object;
		glm::vec3 offset;

	public:
		scenes_object();
		virtual ~scenes_object();

		virtual void draw_scenes(vnaon_gl::GLcontroller *parg_gl,  const vnaon_common::camera &carg_camera);

	};
}
