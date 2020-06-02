#include "GLobject.h"

namespace vnaon_gl {

	GLresource::GLresource(GLuint arg_handle) {
		destroy_function = nullptr;
		_name_h = arg_handle;
	}

	GLresource::~GLresource() {
		if ( destroy_function != nullptr ) destroy_function(&_name_h);
	}

	GLuint GLresource::get_handle() const {
		return _name_h;
	}

	void GLresource::set_handle(GLuint arg_handle) {
		_name_h = arg_handle;
	}

	void GLresource::_attach_destory_func(d_destroy_func arg_func) {
		destroy_function = arg_func;
	}

}