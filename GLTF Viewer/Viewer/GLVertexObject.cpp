#include "GLVertexObject.h"

namespace vNaonGL {

	// VBO
	GLvertexbuffer::GLvertexbuffer(GLuint handle, GLenum usage)
		: GLresource(handle){
		mUsage = usage;
	}

	GLvertexbuffer::~GLvertexbuffer() {
	}

	pGLvertexbuffer GLvertexbuffer::Create(GLuint handle, GLenum usage) {
		return std::make_shared<GLvertexbuffer>(handle, usage);
	}

	// IBO
	GLindiciesbuffer::GLindiciesbuffer(GLuint handle, GLenum usage)
		: GLresource(handle) {
		mUsage = usage;
	}

	GLindiciesbuffer::~GLindiciesbuffer() {
	}

	pGLindiciesbuffer GLindiciesbuffer::Create(GLuint handle, GLenum usage) {
		return std::make_shared<GLindiciesbuffer>(handle, usage);
	}

	// VAO
	GLvertexarray::GLvertexarray(GLuint handle)
		: GLresource(handle) {
		mAttribInformation.clear();
		pIBO = nullptr;
	}

	GLvertexarray::~GLvertexarray() {
	}

	pGLvertexarray GLvertexarray::Create(GLuint handle) {
		return std::make_shared<GLvertexarray>(handle);
	}

	void GLvertexarray::attachInfomation(ATTRIB_INFO info) {
		mAttribInformation.push_back(info);
	}

}