#include "scenes_object.h"



namespace vnaon_scenes {

	scenes_object::scenes_object() {
		offset = glm::vec3(0.0);
	}

	scenes_object::~scenes_object() {
	}

	void scenes_object::draw_scenes(vnaon_gl::GLcontroller *parg_gl, const vnaon_common::camera &carg_camera) {
		if ( _init_render(parg_gl) )
			draws(parg_gl, carg_camera);
	}

	void scenes_object::init(vnaon_gl::GLcontroller *parg_gl) {
	}

	void scenes_object::release_gl_resource() {
	}

	bool scenes_object::_init_render(vnaon_gl::GLcontroller *parg_gl) {
		return false;
	}

	void scenes_object::draws(vnaon_gl::GLcontroller *parg_gl, const vnaon_common::camera &carg_camera) {
	}

}