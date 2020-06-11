#include "GLuniform.h"
#include "GLcontroller.h"



#include "_DEBUG_OBJECT.hpp"



namespace vnaon_gl {

	GLuniform::GLuniform(std::string arg_name, GLuint arg_location) {
		this->_name = arg_name;
		this->_location = arg_location;
	}
	GLuniform::~GLuniform() {
	}
	p_uniform GLuniform::create(GLenum arg_type, std::string arg_name, GLuint arg_location) {
		switch ( arg_type ) {
		case GL_SAMPLER_2D:
			return std::make_shared<GLint_vector_1>(arg_name, arg_location);
		case GL_FLOAT_MAT4:
			return std::make_shared<GLfloat_matrix_4x4>(arg_name, arg_location);
		default:
			return std::make_shared<GLuniform>(arg_name, arg_location);
		}
	}
	void GLuniform::set_value(const void *arg_value) {
		DEBUGConsole::log(this->_name + " is inactive or does not exist in the current program.");
	}
	GLuint GLuniform::get_location() const {
		return this->_location;
	}


	//===
	GLint_vector_1::GLint_vector_1(std::string arg_name, GLuint arg_location) : GLuniform(arg_name, arg_location) {
	}
	GLint_vector_1::~GLint_vector_1() {
	}
	void GLint_vector_1::set_value(const void *arg_value) {
		glUniform1iv(get_location(), 1, (const GLint *) arg_value);
		GLcontroller::__getRenderError("glUniform1iv");
	}


	//===
	GLfloat_matrix_4x4::GLfloat_matrix_4x4(std::string arg_name, GLuint arg_location) : GLuniform(arg_name, arg_location) {
	}
	GLfloat_matrix_4x4::~GLfloat_matrix_4x4() {
	}
	void GLfloat_matrix_4x4::set_value(const void *arg_value) {
		glUniformMatrix4fv(get_location(), 1, GL_FALSE, (const GLfloat*) arg_value);
		GLcontroller::__getRenderError("glUniformMatrix4fv");
	}
}