#pragma once
#include <memory>



#include "gl_manager.h"
#include "common_camera.h"



namespace vnaon_scenes {

	class ScenesEntity;
	typedef std::shared_ptr<ScenesEntity> ScenesEntity_p;


	class ScenesEntity {
		
	protected:
		glm::vec3 offset;

	public:
		ScenesEntity();
		virtual ~ScenesEntity();

		void DrawScenes(vnaon_gl::GLManager *parg_gl,  const vnaon_common::Camera &carg_camera);

		virtual void Init(vnaon_gl::GLManager *parg_gl);

		virtual void ReleaseResource();

	protected:
		virtual bool ReadyToDraw(vnaon_gl::GLManager *parg_gl);

		virtual void MainDraw(vnaon_gl::GLManager *parg_gl, const vnaon_common::Camera &carg_camera);

	};
}
