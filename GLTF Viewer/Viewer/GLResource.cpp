#include "GLResource.h"

namespace vNaonGL {

	GLresource::GLresource(GLuint handle) {
		pDestroy = nullptr;
		hName = handle;
	}

	GLresource::~GLresource() {
		if ( pDestroy != nullptr ) pDestroy(&hName);
	}

	GLuint GLresource::getHandle() const {
		return hName;
	}

	void GLresource::attachDestoryFunc(DestroyFunc func) {
		pDestroy = func;
	}

}