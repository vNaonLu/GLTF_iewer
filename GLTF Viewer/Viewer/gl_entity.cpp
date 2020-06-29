#include "gl_entity.h"

namespace vnaon_gl {

	GLResource::GLResource(GLuint arg_handle) {
		_destroy_function = nullptr;
		_name_h = arg_handle;
		valid = true;
	}

	GLResource::~GLResource() {
		if ( _destroy_function != nullptr ) _destroy_function(&_name_h);
	}

	GLuint GLResource::GetHandle() const {
		return _name_h;
	}

	bool GLResource::IsValid() const {
		return valid;
	}

	void GLResource::SetHandle(GLuint arg_handle) {
		_name_h = arg_handle;
	}

	void GLResource::AttachDestroyFunction(d_destroy_func arg_func) {
		_destroy_function = arg_func;
	}

}