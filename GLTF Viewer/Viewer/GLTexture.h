#pragma once
#include "GLobject.h"

namespace vnaon_gl {

	class GLtexture;
	typedef std::shared_ptr<GLtexture> p_texture;



	/// <summary>
	/// An Object of texture for OpenGL, and be used for GLcontroller.
	/// </summary>
	class GLtexture : public GLresource{

	public:
		/// <summary>
		/// A samplar used for GLtexture.
		/// </summary>
		struct SAMPLAR {
			GLint	level;
			GLsizei width;
			GLsizei height;
			GLenum	format;
			GLenum	type;
			GLenum	mag_filter;
			GLenum	min_filter;
			GLenum	wrapS;
			GLenum	wrapT;
		};

	protected:
		SAMPLAR sampler;

	public:
		GLtexture(GLuint arg_name, SAMPLAR arg_samplar);
		~GLtexture();

		static p_texture create(GLuint arg_name, SAMPLAR arg_samplar);

	};

}