#include "gl_buffer_object.h"

namespace vnaon_gl {

	GLVertexBuffer::GLVertexBuffer(GLuint arg_handle, GLenum arg_usage)
		: GLResource(arg_handle){
		_usage = arg_usage;
	}

	GLVertexBuffer::~GLVertexBuffer() {
	}

	GLVertexBuffer_p GLVertexBuffer::Create(GLuint arg_handle, GLenum arg_usage) {
		return std::make_shared<GLVertexBuffer>(arg_handle, arg_usage);
	}



	GLIndiciesBuffer::GLIndiciesBuffer(GLuint arg_handle, GLenum arg_usage)
		: GLResource(arg_handle) {
		_usage = arg_usage;
	}

	GLIndiciesBuffer::~GLIndiciesBuffer() {
	}

	GLIndiciesBuffer_p GLIndiciesBuffer::Create(GLuint arg_handle, GLenum arg_usage) {
		return std::make_shared<GLIndiciesBuffer>(arg_handle, arg_usage);
	}



	GLVertexArray::GLVertexArray(GLuint arg_handle)
		: GLResource(arg_handle) {
		_attrib_info.clear();
		_indicies_buffer = nullptr;
	}

	GLVertexArray::~GLVertexArray() {
	}

	GLVertexArray_p GLVertexArray::Create(GLuint arg_handle) {
		return std::make_shared<GLVertexArray>(arg_handle);
	}

	void GLVertexArray::AttachIndiciesBuffer(GLIndiciesBuffer_p arg_ibo) {
		_indicies_buffer = arg_ibo;
	}

	void GLVertexArray::AttachVertexBuffer(VertexAttributeInfomation arg_info) {
		_attrib_info.push_back(arg_info);
	}

}