#include "gl_manager.h"
#include "common_bitmap.h"



#include "debug_tools.hpp"



namespace vnaon_gl {

	GLManager::GLManager() {
		_cln_cor = GLColor(0.0, 0.0, 0.0, 1.0);
		_p_bnd_vert_arr = nullptr;
		_p_bnd_prog = nullptr;
		_p_bnd_skybox = nullptr;
	}

	GLManager::~GLManager() {
	}

	void GLManager::Clear(const GLenum &arg_flag) const {
		GLenum flag = GL_NONE;

		if ( arg_flag & GL_COLOR_BUFFER_BIT )
			flag |= GL_COLOR_BUFFER_BIT;

		glClear(flag);
		__GetRenderError("glClear");

	}

	void GLManager::SetClearColor(const GLColor &arg_color) {
		_cln_cor = arg_color;
		glClearColor(_cln_cor.r, _cln_cor.g, _cln_cor.b, _cln_cor.a);
		__GetRenderError("glClearColor");
	}

	void GLManager::AdjustViewport(const GLsizei &arg_width, const GLsizei &arg_height) {
		glViewport(0, 0, arg_width, arg_height);
		__GetRenderError("glViewport");
	}

	void GLManager::DisableDepthMask() {
		glDepthMask(GL_FALSE);
		__GetRenderError("glDepthMask");
	}

	void GLManager::EnableDepthMask() {
		glDepthMask(GL_TRUE);
		__GetRenderError("glDepthMask");
	}

	GLVertexBuffer_p GLManager::CreateVertexBuffer(GLenum arg_usage, const void *p_arg_data, GLsizeiptr arg_len) const {
		GLuint vboHandle;
		glGenBuffers(1, &vboHandle);
		__GetRenderError("glGenBuffers");

		glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
		__GetRenderError("glBindBuffer");

		glBufferData(GL_ARRAY_BUFFER, arg_len, p_arg_data, arg_usage);
		__GetRenderError("glBufferData");

		GLVertexBuffer_p ret = GLVertexBuffer::Create(vboHandle, arg_usage);

		ret->AttachDestroyFunction([this](GLuint *_name_h) {
			glDeleteBuffers(1, _name_h);
			__GetRenderError("glDeleteBuffers");
			}
		);

		return ret;
	}

	GLIndiciesBuffer_p GLManager::CreateIndiciesBuffer(GLenum arg_usage, const void *p_arg_data, GLsizeiptr arg_len) const {
		GLuint iboHandle;
		glGenBuffers(1, &iboHandle);
		__GetRenderError("glGenBuffers");

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboHandle);
		__GetRenderError("glBindBuffer");

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, arg_len, p_arg_data, arg_usage);
		__GetRenderError("glBufferData");

		GLIndiciesBuffer_p ret = GLIndiciesBuffer::Create(iboHandle, arg_usage);

		ret->AttachDestroyFunction([this](GLuint *_name_h) {
			glDeleteBuffers(1, _name_h);
			__GetRenderError("glDeleteBuffers");
			}
		);

		return ret;
	}

	GLVertexArray_p GLManager::CreateVertexArray() const {
		GLuint vaoHandle;
		glGenVertexArrays(1, &vaoHandle);
		__GetRenderError("glGenVertexArrays");

		GLVertexArray_p ret = GLVertexArray::Create(vaoHandle);

		ret->AttachDestroyFunction([this](GLuint *_name_h) {
			glDeleteVertexArrays(1, _name_h);
			__GetRenderError("glDeleteBuffers");
			}
		);

		return ret;
	}

	void GLManager::BindVertexArray(GLVertexArray_p p_arg_dest) {
		if ( p_arg_dest->IsValid() ) {
			_p_bnd_vert_arr = p_arg_dest;
			glBindVertexArray(p_arg_dest->GetHandle());
			__GetRenderError("glBindVertexArray");
		}
	}

	void GLManager::UnbindVertexArray() {
		_p_bnd_vert_arr = nullptr;

		glBindVertexArray(0);
		__GetRenderError("glBindVertexArray");
	}

	void GLManager::SetVertexArray(GLVertexArray_p p_arg_dest, VertexAttributes infos, GLIndiciesBuffer_p p_arg_ind) {

		BindVertexArray(p_arg_dest);

		GLVertexBuffer_p holdVBO = nullptr;
		for ( auto info : infos ) {
		
			if ( holdVBO != info.vertex_buffer ) {
				holdVBO = info.vertex_buffer;
				glBindBuffer(GL_ARRAY_BUFFER, p_arg_dest->GetHandle());
				__GetRenderError("glBindBuffer");
			}
			glEnableVertexAttribArray(info.index);
			__GetRenderError("glEnableVertexAttribArray");
			glVertexAttribPointer(info.index, info.size, info.type, info.normalized, info.stride, (const void *) info.offset);
			__GetRenderError("glVertexAttribPointer");

			p_arg_dest->AttachVertexBuffer(info);
		}

		if ( p_arg_ind != nullptr ) {
			p_arg_dest->AttachIndiciesBuffer(p_arg_ind);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_arg_ind->GetHandle());
			__GetRenderError("glBindBuffer");
		}

		UnbindVertexArray();

	}

	GLProgram_p GLManager::CreateProgram(const std::string &src_name) const {

		GLProgram_p ret = GLProgram::Create(0, src_name);
		return ret;
	}

	bool GLManager::CompileProgram(GLProgram_p p_arg_dest) {
		bool ret = false;

		if ( p_arg_dest->ReadyToCompile() ) {					
			bool is_compiled_vert, is_compiled_frag;
			GLuint h_vert = glCreateShader(GL_VERTEX_SHADER);
			__GetRenderError("glCreateShader");
			GLuint h_frag = glCreateShader(GL_FRAGMENT_SHADER);
			__GetRenderError("glCreateShader");
			
			// vertex
			std::string reason;
			auto vert_src = p_arg_dest->GetVertexShaderSource();
			is_compiled_vert = CompileShader(h_vert, vert_src.c_str(), (GLint) vert_src.size(), reason);
			if ( !is_compiled_vert )
				_DebugTools_::Log({"Failed to compile vertex shader: " + p_arg_dest->GetName() + ". Reason:\n" + reason });

			// fragment
			reason.clear();
			auto frag_src = p_arg_dest->GetFragmentShaderSource();
			is_compiled_frag = CompileShader(h_frag, frag_src.c_str(), (GLint) frag_src.size(), reason);
			if ( !is_compiled_frag )
				_DebugTools_::Log({"Failed to compile fragment shader: "+ p_arg_dest->GetName() + ". Reason:\n" + reason });

			if ( is_compiled_vert && is_compiled_frag ) {
				GLuint hProgram;
				hProgram = glCreateProgram();
				__GetRenderError("glCreateShader");

				glAttachShader(hProgram, h_vert);
				__GetRenderError("glAttachShader");
				
				glAttachShader(hProgram, h_frag);
				__GetRenderError("glAttachShader");

				glLinkProgram(hProgram);
				__GetRenderError("glLinkProgram");

				GLint success;
				GLchar infoLog[512];
				glGetProgramiv(hProgram, GL_LINK_STATUS, &success);
				if ( !success ) {
					_DebugTools_::Log({ "Failed to link program: " + p_arg_dest->GetName() + ". Reason:\n" + infoLog });
					glDeleteProgram(hProgram);
					__GetRenderError("glDeleteProgram");

				} else {
					p_arg_dest->SetProfile(hProgram);
					p_arg_dest->AttachDestroyFunction([this](GLuint *_name_h) {
						glDeleteProgram(*_name_h);
						__GetRenderError("glDeleteProgram");
						});
					ret = true;
				}

			}

			glDeleteShader(h_vert);
			__GetRenderError("glDeleteShader");
			glDeleteShader(h_frag);
			__GetRenderError("glDeleteShader");
		}

		return ret;
	}

	bool GLManager::UseProgram(GLProgram_p p_arg_dest) {
		if ( p_arg_dest->IsValid() ) {
			_p_bnd_prog = p_arg_dest;
			glUseProgram(_p_bnd_prog->GetHandle());
			return __GetRenderError("glUseProgram");
		}
		return false;
	}

	GLTexture_p GLManager::CreateTextureFromFile(const std::string &path, GLTexture::SAMPLER samplar) const{
		GLTexture_p ret = nullptr;
		vnaon_common::BitmapImage_p img = vnaon_common::BitmapImage::CreateFromFile(path);
		if ( img != nullptr ) {
			samplar.width = img->GetWidth();
			samplar.height = img->GetHeight();

			bool success = true;
			GLuint hTex;
			glGenTextures(1, &hTex);
			success |= __GetRenderError("glGenTextures");

			glActiveTexture(GL_TEXTURE0);
			success |= __GetRenderError("glActiveTexture");

			glBindTexture(GL_TEXTURE_2D, hTex);
			success |= __GetRenderError("glBindTexture");

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, samplar.wrap_s);
			success |= __GetRenderError("glTexParameteri");

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, samplar.wrap_t);
			success |= __GetRenderError("glTexParameteri");

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, samplar.min_filter);
			success |= __GetRenderError("glTexParameteri");

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, samplar.mag_filter);
			success |= __GetRenderError("glTexParameteri");

			glTexImage2D(GL_TEXTURE_2D, samplar.level, samplar.format, samplar.width, samplar.height, 0, samplar.format, samplar.type, img->GetBuffer());
			success |= __GetRenderError("glTexImage2D");

			glGenerateMipmap(GL_TEXTURE_2D);
			success |= __GetRenderError("glGenerateMipmap");

			// reset texture
			glBindTexture(GL_TEXTURE_2D, _p_ept_tex->GetHandle());
			success |= __GetRenderError("glBindTexture");

			if ( success ) {
				ret = GLTexture::Create(hTex, samplar);
				ret->AttachDestroyFunction([](GLuint *arg_name) {
					glDeleteTextures(1, arg_name);
					}
				);
			}

		}
		return ret;
	}

	GLSkyBox_p GLManager::CreateSkyBoxFromFile(const std::vector<std::string> &arg_img_sources) const {
		GLSkyBox_p p_skybox_object = GLSkyBox::Create(0, arg_img_sources);
		p_skybox_object = p_skybox_object->IsValid() ? p_skybox_object : nullptr;
		return p_skybox_object;
	}

	void GLManager::BindSkybox(GLSkyBox_p arg_skybox) {
		if ( arg_skybox->IsValid() ) {
			_p_bnd_skybox = arg_skybox;
			glBindTexture(GL_TEXTURE_CUBE_MAP, _p_bnd_skybox->GetHandle());
			__GetRenderError("glBindTexture");
		}
	}

	void GLManager::DrawArrays(GLenum arg_mode, GLint arg_first, GLsizei arg_count) {
		glDrawArrays(arg_mode, arg_first, arg_count);
		__GetRenderError("glDrawArrays");
	}

	GLTexture_p GLManager::CreateEmptyTexture() const {
		GLTexture::SAMPLER samplar{ 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
		GLuint hTex;
		glGenTextures(1, &hTex);
		__GetRenderError("glGenTextures");
		glActiveTexture(GL_TEXTURE0);
		__GetRenderError("glActiveTexture");
		glBindTexture(GL_TEXTURE_2D, hTex);
		__GetRenderError("glBindTexture");
		float bin[4] = { 0, 0, 0, 1 };
		glTexImage2D(GL_TEXTURE_2D, samplar.level, samplar.format, samplar.width, samplar.height, 0, samplar.format, samplar.type, bin);
		__GetRenderError("glTexImage2D");

		return GLTexture::Create(hTex, samplar);
	}

	bool GLManager::CompileShader(GLuint arg_handle, const GLchar *arg_src, GLint arg_len, std::string &arg_msg) const {
		GLint is_compiled;

		glShaderSource(arg_handle, 1, &arg_src, &arg_len);
		__GetRenderError("glShaderSource");

		glCompileShader(arg_handle);
		__GetRenderError("glCompileShader");

		glGetShaderiv(arg_handle, GL_COMPILE_STATUS, &is_compiled);
		__GetRenderError("glGetShaderiv");
		if ( is_compiled == GL_FALSE ) {
			GLint max_length = 0;
			glGetShaderiv(arg_handle, GL_INFO_LOG_LENGTH, &max_length);
			__GetRenderError("glGetShaderiv");
			std::vector<GLchar> err_log(max_length);
			glGetShaderInfoLog(arg_handle, max_length, &max_length, &err_log[0]);
			__GetRenderError("glGetShaderiv");
			arg_msg = err_log.data();
			return false;
		} else {
			return true;
		}
	}

	void GLManager::Init() {

		_p_ept_tex = CreateEmptyTexture();

	}

	// for debug
	bool GLManager::__GetRenderError(const std::string &who) {

#ifdef __GL_FUNCTION_TRACKER__
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
			_DebugTools_::Log({ who + " got " + errorName + " error." });
			return false;
		} else {
			return true;
		}
#else
		return true;
#endif

	}

	void GLManager::__ResetErrorMessage() {

#ifdef __GL_FUNCTION_TRACKER__
		while ( glGetError() != GL_NO_ERROR );
#endif

	}

}