#pragma once
#include "scenes_object.h"



namespace vnaon_scenes {

	class scenes_skybox;
	typedef std::shared_ptr<scenes_skybox> p_scenes_skybox;
	class scenes_skybox : public scenes_object {

	protected:
		vnaon_gl::p_vertex_arr p_vertex_array;
		vnaon_gl::p_program p_skybox_shaderprogram;
		vnaon_gl::p_skybox p_texture;
		bool ready_to_draw;

	public:
		scenes_skybox();
		~scenes_skybox();

		virtual void init(vnaon_gl::GLcontroller *parg_gl) override;

		virtual void release_gl_resource() override;

		static p_scenes_object create();

	protected:
		virtual void draws(vnaon_gl::GLcontroller *parg_gl, const vnaon_common::camera &carg_camera) override;

	private:
		virtual bool _init_render(vnaon_gl::GLcontroller *parg_gl) override;

		bool _init_program(vnaon_gl::GLcontroller *parg_gl);

		bool _init_texture(vnaon_gl::GLcontroller *parg_gl);

		bool _init_vertex(vnaon_gl::GLcontroller *parg_gl);

	};

}