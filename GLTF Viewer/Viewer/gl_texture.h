#pragma once
#include "gl_entity.h"

namespace vnaon_gl {

	class GLTexture;
	typedef std::shared_ptr<GLTexture> GLTexture_p;



	/// <summary>
	/// An Object of texture for OpenGL, and be used for GLManager.
	/// </summary>
	class GLTexture : public GLResource{

	public:
		/// <summary>
		/// A samplar used for GLTexture.
		/// </summary>
		struct SAMPLER {
			GLint	level;
			GLsizei width;
			GLsizei height;
			GLenum	format;
			GLenum	type;
			GLenum	mag_filter;
			GLenum	min_filter;
			GLenum	wrap_s;
			GLenum	wrap_t;
		};

	protected:
		SAMPLER samplar;

	public:
		GLTexture(GLuint arg_name, SAMPLER arg_samplar);
		~GLTexture();

		static GLTexture_p Create(GLuint arg_name, SAMPLER arg_samplar);

	};

}