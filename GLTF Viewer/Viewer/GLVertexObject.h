#pragma once
#include <vector>
#include "GLResource.h"

namespace vNaonGL {

	// VBO
	class GLvertexbuffer : public GLresource{
	
	protected:
		GLenum mUsage;

	public:
		GLvertexbuffer(GLuint handle, GLenum usage);
		~GLvertexbuffer();

		static pGLvertexbuffer create(GLuint handle, GLenum usage);

		friend class GLdevice;

	};

	// IBO
	class GLindiciesbuffer : public GLresource {

	protected:
		GLenum mUsage;

	public:
		GLindiciesbuffer(GLuint handle, GLenum usage);
		~GLindiciesbuffer();

		static pGLindiciesbuffer create(GLuint handle, GLenum usage);

		friend class GLdevice;

	};

	//VAO
	class GLvertexarray : public GLresource {
	
	protected:
		struct ATTRIB_INFO {
			pGLvertexbuffer pVBO;
			GLuint index;
			GLint size;
			GLenum type;
			GLboolean normalized;
			GLsizei stride;
			GLsizeiptr offset;
		};
		std::vector<ATTRIB_INFO> mAttribInformation;
		pGLindiciesbuffer pIBO;

	public:
		GLvertexarray(GLuint handle);
		~GLvertexarray();

		static pGLvertexarray create(GLuint handle);

	protected:
		void attachInfomation(ATTRIB_INFO info);

		friend class GLdevice;

	};

}