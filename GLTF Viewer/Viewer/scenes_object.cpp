#include "scenes_object.h"


namespace vnaon_scenes {

	scenes_object::scenes_object() {
		offset = glm::vec3(0.0);
		p_drawing_vertex_object = nullptr;
	}

	scenes_object::~scenes_object() {
	}

	void scenes_object::draw_scenes(vnaon_gl::GLcontroller *parg_gl, const vnaon_common::camera &carg_camera) {
	}

}