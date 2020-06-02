#include "GLbuffer.h"

namespace vnaon_gl {

	GLvertexbuffer::GLvertexbuffer(GLuint arg_handle, GLenum arg_usage)
		: GLresource(arg_handle){
		_usage = arg_usage;
	}

	GLvertexbuffer::~GLvertexbuffer() {
	}

	p_vertex_buf GLvertexbuffer::create(GLuint arg_handle, GLenum arg_usage) {
		return std::make_shared<GLvertexbuffer>(arg_handle, arg_usage);
	}



	GLindiciesbuffer::GLindiciesbuffer(GLuint arg_handle, GLenum arg_usage)
		: GLresource(arg_handle) {
		_usage = arg_usage;
	}

	GLindiciesbuffer::~GLindiciesbuffer() {
	}

	p_indicies_buf GLindiciesbuffer::create(GLuint arg_handle, GLenum arg_usage) {
		return std::make_shared<GLindiciesbuffer>(arg_handle, arg_usage);
	}



	GLvertexarray::GLvertexarray(GLuint arg_handle)
		: GLresource(arg_handle) {
		_attrib_info.clear();
		_ind_buf_obj = nullptr;
	}

	GLvertexarray::~GLvertexarray() {
	}

	p_vertex_arr GLvertexarray::create(GLuint arg_handle) {
		return std::make_shared<GLvertexarray>(arg_handle);
	}

	void GLvertexarray::attach_ind_buf(p_indicies_buf arg_ibo) {
		_ind_buf_obj = arg_ibo;
	}

	void GLvertexarray::attach_buf_info(ATTRIB_INFO arg_info) {
		_attrib_info.push_back(arg_info);
	}

}