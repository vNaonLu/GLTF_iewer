#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>

#include "Rect.h"
#include "GLcolor.h"
#include "GLResource.h"
#include "GLVertexObject.h"

namespace vNaonGL {

	/*
	 A interface which is used for communication with the openGL.
	*/
	class GLdevice {
	private:
		GLcolor mClearColor;

		pGLvertexarray pCurrentBoundVAO;
		pGLshaderprogram pCurrentBoundSPO;

	public:
		GLdevice();
		~GLdevice();

	public:
		//Clear the viewer.
		void clear(const GLenum &cClearFlag = GL_COLOR_BUFFER_BIT) const;
		//Specifies a color of buffer for clear.
		void setClearColorBuffer(const GLcolor &cColor);
		//Set viewport
		void resizeViewport(const GLsizei &w, const GLsizei &h);

		// Vertex buffers...
		// ---

		pGLvertexbuffer createVertexBufferObject(GLenum usage, const void* pData = nullptr, GLsizeiptr length = 0) const;

		pGLindiciesbuffer createIndiciesBufferObjecet(GLenum usage, const void *pData = nullptr, GLsizeiptr length = 0) const;

		pGLvertexarray createVertexArrayObject() const;

		void bindVertexArray(pGLvertexarray pVAO);
		void unbindVertexArray();

		typedef std::vector<GLvertexarray::ATTRIB_INFO> AttributeInformations;
		void initializeVertexArray(pGLvertexarray pDest, AttributeInformations infos, pGLindiciesbuffer pIBO = nullptr);

		// Shader Program...
		// ---

		pGLshaderprogram createShaderProgram(const std::string &name = "Untitled Shader") const;
		bool compileShaderProgram(pGLshaderprogram pSPO);

		bool useProgram(pGLshaderprogram pSPO);

	protected:
		void bindVertexBuffer(pGLvertexbuffer pVBO) const;
		void unbindVertexBuffer() const;

		void bindIndiciesBuffer(pGLindiciesbuffer pIBO) const;
		void unbindIndiciesBuffer() const;

		// NOTE: stride is based on length of bytes.
		void vertexAttribPointer(GLuint idx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLsizeiptr offset) const;

		bool compileShader(GLuint hS, GLchar *pSrc, GLint length, std::string &info) const;

	private:
		//Used for debug error.
		static bool __getRenderError(const std::string &who);
		static void __resetErrorMessage();

	};

}