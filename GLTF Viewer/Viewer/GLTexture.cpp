#include "GLTexture.h"

namespace vNaonGL {

	GLTexture::GLTexture(GLuint name, SAMPLAR samplar)
		: GLresource(name){
		mSamplar = samplar;
	}

	GLTexture::~GLTexture() {
	}

	pGLTexture GLTexture::create(GLuint name, SAMPLAR samplar) {
		return std::make_shared<GLTexture>(name, samplar);
	}

}