#include "GLdevice.h"
#include "GLVertexObject.h"
#include "GLShaderProgram.h"
#include "Image.h"

#include "_DEBUG_OBJECT.hpp"

#define __OPENGL_DEBUG__

namespace vNaonGL {

	GLdevice::GLdevice() {
		mClearColor = GLcolor(0.0, 0.0, 0.0, 1.0);
		pCurrentBoundVAO = nullptr;
		pCurrentBoundSPO = nullptr;
	}

	GLdevice::~GLdevice() {
	}

	void GLdevice::clear(const GLenum &cClearFlag) const {
		GLenum flag = GL_NONE;

		if ( cClearFlag & GL_COLOR_BUFFER_BIT )
			flag |= GL_COLOR_BUFFER_BIT;

		glClear(flag);
		__getRenderError("glClear");

	}

	void GLdevice::setClearColorBuffer(const GLcolor &cColor) {
		mClearColor = cColor;
		glClearColor(mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a);
		__getRenderError("glClearColor");
	}

	void GLdevice::resizeViewport(const GLsizei &w, const GLsizei &h) {
		glViewport(0, 0, w, h);
		__getRenderError("glViewport");
	}

	pGLvertexbuffer GLdevice::createVertexBufferObject(GLenum usage, const void *pData, GLsizeiptr length) const {
		GLuint vboHandle;
		glGenBuffers(1, &vboHandle);
		__getRenderError("glGenBuffers");

		glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
		__getRenderError("glBindBuffer");

		glBufferData(GL_ARRAY_BUFFER, length, pData, usage);
		__getRenderError("glBufferData");

		pGLvertexbuffer ret = GLvertexbuffer::create(vboHandle, usage);

		ret->attachDestoryFunc([this](GLuint *hName) {
			glDeleteBuffers(1, hName);
			__getRenderError("glDeleteBuffers");
			});

		return ret;
	}

	pGLindiciesbuffer GLdevice::createIndiciesBufferObjecet(GLenum usage, const void *pData, GLsizeiptr length) const {
		GLuint iboHandle;
		glGenBuffers(1, &iboHandle);
		__getRenderError("glGenBuffers");

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboHandle);
		__getRenderError("glBindBuffer");

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, length, pData, usage);
		__getRenderError("glBufferData");

		pGLindiciesbuffer ret = GLindiciesbuffer::create(iboHandle, usage);

		ret->attachDestoryFunc([this](GLuint *hName) {
			glDeleteBuffers(1, hName);
			__getRenderError("glDeleteBuffers");
			});

		return ret;
	}

	pGLvertexarray GLdevice::createVertexArrayObject() const {
		GLuint vaoHandle;
		glGenVertexArrays(1, &vaoHandle);
		__getRenderError("glGenVertexArrays");

		pGLvertexarray ret = GLvertexarray::create(vaoHandle);

		ret->attachDestoryFunc([this](GLuint *hName) {
			glDeleteVertexArrays(1, hName);
			__getRenderError("glDeleteBuffers");
			});

		return ret;
	}

	void GLdevice::bindVertexArray(pGLvertexarray pVAO) {
		pCurrentBoundVAO = pVAO;

		glBindVertexArray(pVAO->getHandle());
		__getRenderError("glBindVertexArray");
	}

	void GLdevice::unbindVertexArray() {
		pCurrentBoundVAO = nullptr;

		glBindVertexArray(0);
		__getRenderError("glBindVertexArray");
	}

	void GLdevice::initializeVertexArray(pGLvertexarray pDest, AttributeInformations infos, pGLindiciesbuffer pIBO) {

		bindVertexArray(pDest);

		pGLvertexbuffer holdVBO = nullptr;
		for ( auto info : infos ) {
		
			if ( holdVBO != info.pVBO ) {
				holdVBO = info.pVBO;
				bindVertexBuffer(holdVBO);
			}
			vertexAttribPointer(info.index, info.size, info.type, info.normalized, info.stride, info.offset);
			pDest->attachInfomation(info);
		}

		if ( pIBO != nullptr ) bindIndiciesBuffer(pIBO);

		unbindVertexBuffer();

	}

	pGLshaderprogram GLdevice::createShaderProgram(const std::string &name) const {

		pGLshaderprogram ret = std::make_shared<GLshaderprogram>(0, name);

		return ret;
	}

	bool GLdevice::compileShaderProgram(pGLshaderprogram pSPO) {
		bool ret = false;

		if ( pSPO->readyToCompile() ) {					
			bool vSuccess, fSuccess;
			GLuint hVertex = glCreateShader(GL_VERTEX_SHADER);
			__getRenderError("glCreateShader");
			GLuint hFragment = glCreateShader(GL_FRAGMENT_SHADER);
			__getRenderError("glCreateShader");
			
			// vertex
			std::string reason;
			GLchar *vertexSrc = nullptr;
			GLint vertexLength = 0;
			pSPO->copyVertexShaderSource(vertexSrc, vertexLength);
			vSuccess = compileShader(hVertex, vertexSrc, vertexLength, reason);
			if ( vSuccess )
				DEBUGConsole::log({ pSPO->getShaderName() + "failed to compile vertex shader. Reason:\n" + reason });
			delete[] vertexSrc;

			// fragment
			reason.clear();
			std::vector<GLchar *> fragmentSrc;
			std::vector<GLint> fragmentLength;
			pSPO->copyFragmentShaderSource(fragmentSrc, fragmentLength);
			fSuccess = compileShader(hFragment, fragmentSrc[0], fragmentLength[0], reason);
			if ( fSuccess )
				DEBUGConsole::log({ pSPO->getShaderName() + "failed to compile fragment shader. Reason:\n" + reason });
			for ( auto *src : fragmentSrc ) delete[] src;

			if ( vSuccess && fSuccess ) {
				GLuint hProgram;
				hProgram = glCreateProgram();
				__getRenderError("glCreateShader");

				glAttachShader(hProgram, hVertex);
				__getRenderError("glAttachShader");

				glAttachShader(hProgram, hFragment);
				__getRenderError("glAttachShader");

				glLinkProgram(hProgram);
				__getRenderError("glLinkProgram");

				GLint success;
				GLchar infoLog[512];
				glGetProgramiv(hProgram, GL_LINK_STATUS, &success);
				if ( !success ) {
					DEBUGConsole::log({ pSPO->getShaderName() + "failed to link program. Reason:\n" + infoLog });
					glDeleteProgram(hProgram);
					__getRenderError("glDeleteProgram");

				} else {
					pSPO->setHandle(hProgram);
					pSPO->attachDestoryFunc([this](GLuint *hName) {
						glDeleteProgram(*hName);
						__getRenderError("glDeleteProgram");
						});
					ret = true;
				}

			}

			glDeleteShader(hVertex);
			__getRenderError("glDeleteShader");
			glDeleteShader(hFragment);
			__getRenderError("glDeleteShader");
		}

		return ret;
	}

	bool GLdevice::useProgram(pGLshaderprogram pSPO) {
		pCurrentBoundSPO = pSPO;
		glUseProgram(pCurrentBoundSPO->getHandle());
		return __getRenderError("glUseProgram");
	}

	pGLTexture GLdevice::createTextureFromFile(const std::string &path, GLTexture::SAMPLAR samplar) const{
		pGLTexture ret = nullptr;
		vNaonCommon::pBitmapImg img = vNaonCommon::CBitmapImg::createFromFile(path);
		if ( img != nullptr ) {
			samplar.width = img->getWidth();
			samplar.height = img->getHeight();

			bool success = true;
			GLuint hTex;
			glGenTextures(1, &hTex);
			success |= __getRenderError("glGenTextures");

			glActiveTexture(GL_TEXTURE0);
			success |= __getRenderError("glActiveTexture");

			glBindTexture(GL_TEXTURE_2D, hTex);
			success |= __getRenderError("glBindTexture");

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, samplar.wrapS);
			success |= __getRenderError("glTexParameteri");

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, samplar.wrapT);
			success |= __getRenderError("glTexParameteri");

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, samplar.minFilter);
			success |= __getRenderError("glTexParameteri");

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, samplar.magFilter);
			success |= __getRenderError("glTexParameteri");

			glTexImage2D(GL_TEXTURE_2D, samplar.level, samplar.format, samplar.width, samplar.height, 0, samplar.format, samplar.type, img->getBuffer());
			success |= __getRenderError("glTexImage2D");

			glGenerateMipmap(GL_TEXTURE_2D);
			success |= __getRenderError("glGenerateMipmap");

			// reset texture
			glBindTexture(GL_TEXTURE_2D, pEmptyTexutre->getHandle());
			success |= __getRenderError("glBindTexture");

			if ( success )
				ret = GLTexture::create(hTex, samplar);

		}
		return ret;
	}

	pGLTexture GLdevice::createEmptyTexture() const {
		GLTexture::SAMPLAR samplar{ 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
		GLuint hTex;
		glGenTextures(1, &hTex);
		__getRenderError("glGenTextures");
		glActiveTexture(GL_TEXTURE0);
		__getRenderError("glActiveTexture");
		glBindTexture(GL_TEXTURE_2D, hTex);
		__getRenderError("glBindTexture");
		float bin[4] = { 0, 0, 0, 1 };
		glTexImage2D(GL_TEXTURE_2D, samplar.level, samplar.format, samplar.width, samplar.height, 0, samplar.format, samplar.type, bin);
		__getRenderError("glTexImage2D");

		return GLTexture::create(hTex, samplar);
	}

	void GLdevice::bindVertexBuffer(pGLvertexbuffer pVBO) const {
		glBindBuffer(GL_ARRAY_BUFFER, pVBO->getHandle());
		__getRenderError("glBindBuffer");
	}

	void GLdevice::unbindVertexBuffer() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		__getRenderError("glBindBuffer");
	}

	void GLdevice::bindIndiciesBuffer(pGLindiciesbuffer pIBO) const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pIBO->getHandle());
		__getRenderError("glBindBuffer");
	}

	void GLdevice::unbindIndiciesBuffer() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		__getRenderError("glBindBuffer");
	}

	void GLdevice::vertexAttribPointer(GLuint idx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLsizeiptr offset) const {
		glEnableVertexAttribArray(idx);
		__getRenderError("glEnableVertexAttribArray");
		glVertexAttribPointer(idx, size, type, normalized, stride, (const void *) offset);
		__getRenderError("glVertexAttribPointer");
	}

	bool GLdevice::compileShader(GLuint hS, GLchar *pSrc, GLint length, std::string &info) const {
		GLint success;
		GLchar infoLog[512];

		glShaderSource(hS, 1, &pSrc, &length);
		__getRenderError("glShaderSource");

		glCompileShader(hS);
		__getRenderError("glCompileShader");

		glGetShaderiv(hS, GL_COMPILE_STATUS, &success);
		__getRenderError("glGetShaderiv");
		if ( !success ) {
			info = infoLog;
			return false;
		} else {
			return true;
		}
	}

	void GLdevice::initDefaultValues() {

		pEmptyTexutre = createEmptyTexture();

	}

	// for debug
	bool GLdevice::__getRenderError(const std::string &who) {

#ifdef __OPENGL_DEBUG__
		std::string errorName = "";
		switch ( glGetError() ) {

		case GL_INVALID_ENUM:
			errorName = "GL_INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			errorName = "GL_INVALID_VALUE";
			break;
		case GL_INVALID_OPERATION:
			errorName = "GL_INVALID_OPERATION";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			errorName = "GL_INVALID_FRAMEBUFFER_OPERATION";
			break;
		case GL_OUT_OF_MEMORY:
			errorName = "GL_OUT_OF_MEMORY";
			break;

		}
		
		if ( errorName != "" ) {
			DEBUGConsole::log({ who + " got " + errorName + " error." });
			return false;
		} else {
			return true;
		}
#else
		return true;
#endif

	}

	void GLdevice::__resetErrorMessage() {

#ifdef __OPENGL_DEBUG__
		while ( glGetError() != GL_NO_ERROR );
#endif

	}

}