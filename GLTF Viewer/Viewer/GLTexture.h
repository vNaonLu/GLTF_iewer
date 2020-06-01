#pragma once
#include "GLResource.h"

namespace vNaonGL {

	class GLTexture : public GLresource{
	public:
		struct SAMPLAR {
			GLint level;
			GLsizei width;
			GLsizei height;
			GLenum format;
			GLenum type;
			GLenum magFilter;
			GLenum minFilter;
			GLenum wrapS;
			GLenum wrapT;
		};

	protected:
		SAMPLAR mSamplar;

	public:
		GLTexture(GLuint name, SAMPLAR samplar);
		~GLTexture();

		static pGLTexture create(GLuint name, SAMPLAR samplar);

	};

}