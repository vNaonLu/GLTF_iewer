#pragma once
#include "scenes_entity.h"



namespace vnaon_scenes {

	class ScenesSkyBox;
	class ScenesSkyBox : public ScenesEntity {

	protected:
		vnaon_gl::GLVertexArray_p p_vertex_array;
		vnaon_gl::GLProgram_p p_skybox_shaderprogram;
		vnaon_gl::GLSkyBox_p GLTexture_p;
		bool ready_to_draw;

	public:
		ScenesSkyBox();
		~ScenesSkyBox();

		virtual void Init(vnaon_gl::GLManager *parg_gl) override;

		virtual void ReleaseResource() override;

		static ScenesEntity_p Create();

	protected:
		virtual void MainDraw(vnaon_gl::GLManager *parg_gl, const vnaon_common::Camera &carg_camera) override;

	private:
		virtual bool ReadyToDraw(vnaon_gl::GLManager *parg_gl) override;

		bool InitProgram(vnaon_gl::GLManager *parg_gl);

		bool InitTexture(vnaon_gl::GLManager *parg_gl);

		bool InitBuffer(vnaon_gl::GLManager *parg_gl);

	};

}