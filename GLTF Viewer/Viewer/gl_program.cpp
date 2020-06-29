#include <algorithm>



#include "gl_manager.h"
#include "gl_program.h"
#include "common_file_manager.h"



namespace vnaon_gl {

	GLProgram::GLProgram(GLuint arg_handle, const std::string &arg_name)
		: GLResource(arg_handle) {
		valid = false;
		_program_name = arg_name;
		_vertex_source = "";
		_fragment_source = "";
	}

	GLProgram::~GLProgram() {
	}

	GLProgram_p GLProgram::Create(GLuint arg_handle, const std::string &arg_name) {
		return std::make_shared<GLProgram>(arg_handle, arg_name);
	}

	bool GLProgram::AttachVertexShader(const std::string &arg_src) {
		_vertex_source = std::string(arg_src);
		return true;
	}

	bool GLProgram::AttachFragmentShader(const std::string &arg_src) {
		_fragment_source = std::string(arg_src);
		return true;
	}

	bool GLProgram::AttachVertexShaderFromFile(const std::string &arg_path) {
		auto arg_src = vnaon_common::file_manager::GetBinary(arg_path);

		if ( arg_src != nullptr ) {
			_vertex_source = arg_src->GetBuffer();
			return true;
		} else {
			return false;
		}
	}

	bool GLProgram::AttachFragmentShaderFromFile(const std::string &arg_path) {
		auto arg_src = vnaon_common::file_manager::GetBinary(arg_path);

		if ( arg_src != nullptr ) {
			_fragment_source = arg_src->GetBuffer();
			return true;
		} else {
			return false;
		}
	}

	std::string GLProgram::GetName() const {
		return _program_name;
	}

	p_uniform GLProgram::GetUnifrom(std::string arg_uniform, GLint arg_index) {
		p_uniform ret = _uniforms_info[arg_uniform][arg_index];
		if ( ret == nullptr ) ret = GLUniform::Create(GL_NONE, arg_uniform, 0);
		return ret;
	}

	bool GLProgram::ReadyToCompile() const {
		return _vertex_source != "" && _fragment_source != "";
	}

	void GLProgram::SetProfile(GLuint arg_name) {
		valid = true;
		SetHandle(arg_name);
		CollectAttributes();
		CollectUnifoms();
	}

	std::string GLProgram::GetVertexShaderSource() const {
		return _vertex_source;
	}

	std::string GLProgram::GetFragmentShaderSource() const {
		return _fragment_source;
	}

	void GLProgram::CollectAttributes() {
		const GLuint handle = GetHandle();
		GLint active_attrib_length;
		glGetProgramiv(handle, GL_ACTIVE_ATTRIBUTES, &active_attrib_length);
		GLManager::__GetRenderError("glGetProgramiv");

		for ( int i = 0; i < active_attrib_length; i++ ) {
			GLsizei char_len;
			GLint att_len;
			GLenum type;
			GLchar name[GLProgram::MAX_NAME_LEN];
			glGetActiveAttrib(handle, (GLuint) i, GLProgram::MAX_NAME_LEN, &char_len, &att_len, &type, name);
			GLManager::__GetRenderError("glGetActiveAttrib");

			_attributes_info[name] = GLProgram::ArgumentProperties{ (GLuint) i, att_len, type };
		}
	}

	void GLProgram::CollectUnifoms() {
		const GLuint handle = GetHandle();
		GLint active_uniform_length;
		glGetProgramiv(handle, GL_ACTIVE_UNIFORMS, &active_uniform_length);
		GLManager::__GetRenderError("glGetProgramiv");

		for ( int i = 0; i < active_uniform_length; i++ ) {
			GLsizei char_len;
			GLint uni_len;
			GLenum type;
			GLchar name[GLProgram::MAX_NAME_LEN];
			glGetActiveUniform(handle, (GLuint) i, GLProgram::MAX_NAME_LEN, &char_len, &uni_len, &type, name);
			GLManager::__GetRenderError("glGetActiveUniform");

			std::vector<p_uniform> v_uniform(uni_len);
			for ( int j = 0; j < uni_len; j++ )
				v_uniform[j] = GLUniform::Create(type, name, (GLuint) (i + j));
			_uniforms_info[name] = v_uniform;
		}
	}

}