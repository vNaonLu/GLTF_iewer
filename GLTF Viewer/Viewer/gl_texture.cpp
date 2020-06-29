#include "gl_texture.h"
#include "gl_manager.h"



namespace vnaon_gl {

	GLTexture::GLTexture(GLuint arg_name, SAMPLER arg_samplar)
		: GLResource(arg_name){
		samplar = arg_samplar;
	}

	GLTexture::~GLTexture() {
	}

	GLTexture_p GLTexture::Create(GLuint arg_name, SAMPLER arg_samplar) {
		return std::make_shared<GLTexture>(arg_name, arg_samplar);
	}

}