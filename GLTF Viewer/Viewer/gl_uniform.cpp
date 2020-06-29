#include "gl_uniform.h"
#include "gl_manager.h"



#include "debug_tools.hpp"



namespace vnaon_gl {

	GLUniform::GLUniform(std::string arg_name, GLuint arg_location) {
		this->_name = arg_name;
		this->_location = arg_location;
	}
	GLUniform::~GLUniform() {
	}
	p_uniform GLUniform::Create(GLenum arg_type, std::string arg_name, GLuint arg_location) {
		switch ( arg_type ) {
		case GL_SAMPLER_2D:
			return std::make_shared<GLUniform1i>(arg_name, arg_location);
		case GL_FLOAT_MAT4:
			return std::make_shared<GLUniformMatrix4fv>(arg_name, arg_location);
		default:
			return std::make_shared<GLUniform>(arg_name, arg_location);
		}
	}
	void GLUniform::SetValue(const void *arg_value) {
		_DebugTools_::Log(this->_name + " is inactive or does not exist in the current program.");
	}
	GLuint GLUniform::GetLocation() const {
		return this->_location;
	}


	//===
	GLUniform1i::GLUniform1i(std::string arg_name, GLuint arg_location) : GLUniform(arg_name, arg_location) {
	}
	GLUniform1i::~GLUniform1i() {
	}
	void GLUniform1i::SetValue(const void *arg_value) {
		glUniform1iv(GetLocation(), 1, (const GLint *) arg_value);
		GLManager::__GetRenderError("glUniform1iv");
	}


	//===
	GLUniformMatrix4fv::GLUniformMatrix4fv(std::string arg_name, GLuint arg_location) : GLUniform(arg_name, arg_location) {
	}
	GLUniformMatrix4fv::~GLUniformMatrix4fv() {
	}
	void GLUniformMatrix4fv::SetValue(const void *arg_value) {
		glUniformMatrix4fv(GetLocation(), 1, GL_FALSE, (const GLfloat*) arg_value);
		GLManager::__GetRenderError("glUniformMatrix4fv");
	}
}