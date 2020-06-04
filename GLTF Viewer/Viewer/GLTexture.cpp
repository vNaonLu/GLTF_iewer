#include "GLtexture.h"
#include "GLcontroller.h"



namespace vnaon_gl {

	GLtexture::GLtexture(GLuint arg_name, SAMPLAR arg_samplar)
		: GLresource(arg_name){
		samplar = arg_samplar;
	}

	GLtexture::~GLtexture() {
	}

	p_texture GLtexture::create(GLuint arg_name, SAMPLAR arg_samplar) {
		return std::make_shared<GLtexture>(arg_name, arg_samplar);
	}

}