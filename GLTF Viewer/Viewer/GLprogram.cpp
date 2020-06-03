#include <algorithm>

#include "GLcontroller.h"
#include "GLprogram.h"
#include "file_manager.h"



namespace vnaon_gl {

	GLshaderprogram::GLshaderprogram(GLuint arg_handle, const std::string &arg_name)
		: GLresource(arg_handle) {
		_valid = false;
		_program_name = arg_name;
		_vert_shd_src = "";
		_frag_shd_srcs.clear();
	}

	GLshaderprogram::~GLshaderprogram() {
	}

	p_program GLshaderprogram::create(GLuint arg_handle, const std::string &arg_name) {
		return std::make_shared<GLshaderprogram>(arg_handle, arg_name);
	}

	bool GLshaderprogram::attach_vertex_shader(const std::string &arg_src) {
		_vert_shd_src = std::string(arg_src);
		return true;
	}

	bool GLshaderprogram::attach_fragment_shader(const std::string &arg_src) {
		std::string newFragShader = std::string(arg_src);
		_frag_shd_srcs.push_back(newFragShader);
		return true;
	}

	bool GLshaderprogram::attach_vertex_shader_from_file(const std::string &arg_path) {
		auto arg_src = vnaon_common::file_manager::get_binary(arg_path);

		if ( arg_src != nullptr ) {
			_vert_shd_src = arg_src->get_buffer();
			return true;
		} else {
			return false;
		}
	}

	bool GLshaderprogram::attach_fragment_shader_from_file(const std::string &arg_path) {
		auto arg_src = vnaon_common::file_manager::get_binary(arg_path);

		if ( arg_src != nullptr ) {
			_frag_shd_srcs = arg_src->get_buffer();
			return true;
		} else {
			return false;
		}
	}

	bool GLshaderprogram::is_valid() const {
		return _valid;
	}

	std::string GLshaderprogram::get_program_name() const {
		return _program_name;
	}

	bool GLshaderprogram::ready_to_compile() const {
		return _vert_shd_src != "" && _frag_shd_srcs != "";
	}

	void GLshaderprogram::set_profile(GLuint arg_name) {
		_valid = true;
		set_handle(arg_name);
		_collect_attribs();
		_collect_unifors();
	}

	std::string GLshaderprogram::get_vert_shd_src() const {
		return _vert_shd_src;
	}

	std::string GLshaderprogram::get_frag_shd_src() const {
		return _frag_shd_srcs;
	}

	void GLshaderprogram::_collect_attribs() {
		const GLuint handle = get_handle();
		GLint active_attrib_length;
		glGetProgramiv(handle, GL_ACTIVE_ATTRIBUTES, &active_attrib_length);
		GLcontroller::__getRenderError("glGetProgramiv");

		for ( int i = 0; i < active_attrib_length; i++ ) {
			GLsizei char_len;
			GLint att_len;
			GLenum type;
			GLchar name[GLshaderprogram::MAX_NAME_LEN];
			glGetActiveAttrib(handle, (GLuint) i, GLshaderprogram::MAX_NAME_LEN, &char_len, &att_len, &type, name);
			GLcontroller::__getRenderError("glGetActiveAttrib");

			_attribs_info[name] = GLshaderprogram::_ARG_PROP{ (GLuint) i, att_len, type };
		}
	}

	void GLshaderprogram::_collect_unifors() {
		const GLuint handle = get_handle();
		GLint active_uniform_length;
		glGetProgramiv(handle, GL_ACTIVE_UNIFORMS, &active_uniform_length);
		GLcontroller::__getRenderError("glGetProgramiv");

		for ( int i = 0; i < active_uniform_length; i++ ) {
			GLsizei char_len;
			GLint uni_len;
			GLenum type;
			GLchar name[GLshaderprogram::MAX_NAME_LEN];
			glGetActiveUniform(handle, (GLuint) i, GLshaderprogram::MAX_NAME_LEN, &char_len, &uni_len, &type, name);
			GLcontroller::__getRenderError("glGetActiveUniform");

			_unifors_info[name] = GLshaderprogram::_ARG_PROP{ (GLuint) i, uni_len, type };
		}
	}

}