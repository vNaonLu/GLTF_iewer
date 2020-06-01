#pragma once
#include "GLResource.h"
#include <vector>
#include <string>

namespace vNaonGL {

	class GLshaderprogram : public GLresource {
		
	protected:
		GLboolean mValid;
		std::string mShaderName;
		std::string mOriginalVertexShaderText;
		std::vector<std::string> mOriginalFragmentShaderText;

	public:
		GLshaderprogram(GLuint handle, const std::string &name );
		~GLshaderprogram();

		static pGLresource create(GLuint handle, const std::string &name);

		bool attachVertexShaderFromMemory(const std::string &source);
		bool attachFragmentShaderFromMemory(const std::string &source);

		bool attachVertexShaderFromFile(const std::string &path);
		bool attachFragmentShaderFromFile(const std::string &path);

		bool isValid() const;

		std::string getShaderName() const;

	protected:
		bool readyToCompile() const;
		void setHandle(GLuint name);

		void copyVertexShaderSource(GLchar *pOut, GLsizei &Length) const;
		void copyFragmentShaderSource(std::vector<GLchar *> &pOut, std::vector<GLsizei> &Length) const;

		friend class GLdevice;

	};

}