#include <sstream>
#include <fstream>

#include "GLShaderProgram.h"
#include "FileManager.h"

namespace vNaonGL {

	GLshaderprogram::GLshaderprogram(GLuint handle, const std::string &name)
		: GLresource(handle) {
		mValid = false;
		mShaderName = name;
		mOriginalVertexShaderText = "";
		mOriginalFragmentShaderText.clear();
	}

	GLshaderprogram::~GLshaderprogram() {
	}

	pGLresource GLshaderprogram::create(GLuint handle, const std::string &name) {
		return std::make_shared<GLshaderprogram>(handle, name);
	}

	bool GLshaderprogram::attachVertexShaderFromMemory(const std::string &source) {
		mOriginalVertexShaderText = std::string(source);
		return true;
	}

	bool GLshaderprogram::attachFragmentShaderFromMemory(const std::string &source) {
		std::string newFragShader = std::string(source);
		mOriginalFragmentShaderText.push_back(newFragShader);
		return true;
	}

	bool GLshaderprogram::attachVertexShaderFromFile(const std::string &path) {

		auto source = vNaonCommon::FileManager::getBinaryFromFile(path);

		if ( source != nullptr ) {
			mOriginalVertexShaderText = source->getBuffer();
			return true;
		} else {
			return false;
		}
	}

	bool GLshaderprogram::attachFragmentShaderFromFile(const std::string &path) {

		auto source = vNaonCommon::FileManager::getBinaryFromFile(path);

		if ( source != nullptr ) {
			mOriginalFragmentShaderText.push_back(source->getBuffer());
			return true;
		} else {
			return false;
		}
	}

	bool GLshaderprogram::isValid() const {
		return mValid;
	}

	std::string GLshaderprogram::getShaderName() const {
		return mShaderName;
	}

	bool GLshaderprogram::readyToCompile() const {
		return mOriginalVertexShaderText != "" && mOriginalFragmentShaderText.size() > 0;
	}

	void GLshaderprogram::setHandle(GLuint name) {
		mValid = true;
		hName = name;
	}

	void GLshaderprogram::copyVertexShaderSource(GLchar *pOut, GLsizei &Length) const {
		Length = (GLint) mOriginalVertexShaderText.size();
		pOut = new GLchar[Length];
		for ( int i = 0; i < Length; i++ ) pOut[i] = mOriginalVertexShaderText[i];
	}

	void GLshaderprogram::copyFragmentShaderSource(std::vector<GLchar *> &pOut, std::vector<GLsizei> &Length) const {
		auto shaderLengthes = mOriginalFragmentShaderText.size();
		pOut.resize(shaderLengthes);
		Length.resize(shaderLengthes);

		for ( int i = 0; i < shaderLengthes; i++ ) {
			auto &src = pOut[i];
			Length[i] = (GLint) mOriginalVertexShaderText.size();
			src = new GLchar[Length[i]];
			for ( int j = 0; j < Length[i]; j++ ) src[j] = mOriginalVertexShaderText[j];
		}
	}

}