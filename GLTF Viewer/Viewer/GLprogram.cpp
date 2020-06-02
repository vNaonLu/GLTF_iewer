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
			_frag_shd_srcs.push_back(arg_src->get_buffer());
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
		return _vert_shd_src != "" && _frag_shd_srcs.size() > 0;
	}

	void GLshaderprogram::set_profile(GLuint arg_name) {
		_valid = true;
		set_handle(arg_name);
	}

	void GLshaderprogram::cpy_vert_shd_src(GLchar *p_arg_out, GLsizei &arg_len) const {
		arg_len = (GLint) _vert_shd_src.size();
		p_arg_out = new GLchar[arg_len];
		for ( int i = 0; i < arg_len; i++ ) p_arg_out[i] = _vert_shd_src[i];
	}

	void GLshaderprogram::cpy_frag_shd_src(std::vector<GLchar *> &p_arg_out, std::vector<GLsizei> &arg_len) const {
		auto shaderLengthes = _frag_shd_srcs.size();
		p_arg_out.resize(shaderLengthes);
		arg_len.resize(shaderLengthes);

		for ( int i = 0; i < shaderLengthes; i++ ) {
			auto &src = p_arg_out[i];
			arg_len[i] = (GLint) _vert_shd_src.size();
			src = new GLchar[arg_len[i]];
			for ( int j = 0; j < arg_len[i]; j++ ) src[j] = _vert_shd_src[j];
		}
	}

}