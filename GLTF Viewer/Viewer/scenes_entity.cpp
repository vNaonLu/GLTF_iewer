#include "scenes_entity.h"



namespace vnaon_scenes {

	ScenesEntity::ScenesEntity() {
		offset = glm::vec3(0.0);
	}

	ScenesEntity::~ScenesEntity() {
	}

	void ScenesEntity::DrawScenes(vnaon_gl::GLManager *parg_gl, const vnaon_common::Camera &carg_camera) {
		if ( ReadyToDraw(parg_gl) )
			MainDraw(parg_gl, carg_camera);
	}

	void ScenesEntity::Init(vnaon_gl::GLManager *parg_gl) {
	}

	void ScenesEntity::ReleaseResource() {
	}

	bool ScenesEntity::ReadyToDraw(vnaon_gl::GLManager *parg_gl) {
		return false;
	}

	void ScenesEntity::MainDraw(vnaon_gl::GLManager *parg_gl, const vnaon_common::Camera &carg_camera) {
	}

}