#pragma once
#include <memory>



#include "GLcontroller.h"
#include "camera.h"



namespace vnaon_scenes {

	class scenes_object;
	typedef std::shared_ptr<scenes_object> p_scenes_object;


	class scenes_object {
		
	protected:
		glm::vec3 offset;

	public:
		scenes_object();
		virtual ~scenes_object();

		void draw_scenes(vnaon_gl::GLcontroller *parg_gl,  const vnaon_common::camera &carg_camera);

		virtual void init(vnaon_gl::GLcontroller *parg_gl);

		virtual void release_gl_resource();

	protected:
		virtual bool _init_render(vnaon_gl::GLcontroller *parg_gl);

		virtual void draws(vnaon_gl::GLcontroller *parg_gl, const vnaon_common::camera &carg_camera);

	};
}
