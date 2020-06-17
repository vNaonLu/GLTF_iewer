#include "GLtexture.h"
#include "GLcontroller.h"



namespace vnaon_gl {

	GLtexture::GLtexture(GLuint arg_name, SAMPLER arg_samplar)
		: GLresource(arg_name){
		samplar = arg_samplar;
	}

	GLtexture::~GLtexture() {
	}

	p_texture GLtexture::create(GLuint arg_name, SAMPLER arg_samplar) {
		return std::make_shared<GLtexture>(arg_name, arg_samplar);
	}

}