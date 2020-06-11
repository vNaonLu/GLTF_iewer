#include "scenes_skybox.h"



namespace vnaon_scenes {

	scenes_skybox::scenes_skybox() : scenes_object() {
		ready_to_draw = false;
		release_gl_resource();
	}
	scenes_skybox::~scenes_skybox() {
	}

	void scenes_skybox::init(vnaon_gl::GLcontroller *parg_gl) {
		ready_to_draw = true;
		ready_to_draw |= _init_program(parg_gl);
		ready_to_draw |= _init_texture(parg_gl);
		ready_to_draw |= _init_vertex(parg_gl);
	}

	void scenes_skybox::release_gl_resource() {
		p_vertex_array = nullptr;
		p_texture = nullptr;
		p_skybox_shaderprogram = nullptr;
	}

	p_scenes_object scenes_skybox::create() {
		return std::make_shared<scenes_skybox>();
	}

	void scenes_skybox::draws(vnaon_gl::GLcontroller *parg_gl, const vnaon_common::camera &carg_camera) {
		parg_gl->use_program(p_skybox_shaderprogram);
		parg_gl->bind_skybox_object(p_texture);
		parg_gl->bind_vertex_array(p_vertex_array);
		glm::mat4 translate = carg_camera.get_model_offset_matrix(glm::vec3(0.0));
		glm::mat4 scale = glm::scale(glm::mat4(1.0), glm::vec3(glm::length(carg_camera.get_pos()) * 10.0f));
		glm::mat4 mvp_matrix = carg_camera.get_viewproj_matrix() * translate;
		p_skybox_shaderprogram->uniform("model_proj_view")->set_value(glm::value_ptr(mvp_matrix));
		parg_gl->draw_array(GL_TRIANGLES, 0, 36);
		parg_gl->unbind_vertex_array();
	}

	bool scenes_skybox::_init_render(vnaon_gl::GLcontroller *parg_gl) {
		return ready_to_draw;
	}

	bool scenes_skybox::_init_program(vnaon_gl::GLcontroller *parg_gl) {
		p_skybox_shaderprogram = parg_gl->create_shader_program("sky_shader");
		p_skybox_shaderprogram->attach_vertex_shader_from_file(R"(glsl\skybox.vs)");
		p_skybox_shaderprogram->attach_fragment_shader_from_file(R"(glsl\skybox.fs)");
		return parg_gl->compile_program(p_skybox_shaderprogram);
	}

	bool scenes_skybox::_init_texture(vnaon_gl::GLcontroller *parg_gl) {

		p_texture = parg_gl->create_skybox_from_file(
			std::vector<std::string>{
				R"(image\right.jpg)",
				R"(image\left.jpg)",
				R"(image\top.jpg)",
				R"(image\bottom.jpg)",
				R"(image\back.jpg)",
				R"(image\front.jpg)"
			}
		);
		return p_texture != nullptr;
	}

	bool scenes_skybox::_init_vertex(vnaon_gl::GLcontroller *parg_gl) {

		float skybox_vertex_binary[] = {
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};

		auto vert_buf = parg_gl->create_vertex_buffer(GL_STATIC_DRAW, skybox_vertex_binary, 108 * sizeof(float));
		
		p_vertex_array = parg_gl->create_vertex_array();
		parg_gl->init_vertex_array(p_vertex_array, vnaon_gl::GLcontroller::attribute_information{
			{vert_buf, 0, 3, GL_FLOAT, GL_FALSE, 0, 0}
			}
		);

		return p_vertex_array != nullptr;
	}

}