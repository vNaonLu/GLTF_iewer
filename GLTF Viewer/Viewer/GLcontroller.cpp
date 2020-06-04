#include "GLcontroller.h"
#include "bitmap_img.h"

#include "_DEBUG_OBJECT.hpp"

#define __OPENGL_DEBUG__

namespace vnaon_gl {

	GLcontroller::GLcontroller() {
		_cln_cor = GLcolor(0.0, 0.0, 0.0, 1.0);
		_p_bnd_vert_arr = nullptr;
		_p_bnd_prog = nullptr;
		_p_bnd_skybox = nullptr;
	}

	GLcontroller::~GLcontroller() {
	}

	void GLcontroller::clear(const GLenum &arg_flag) const {
		GLenum flag = GL_NONE;

		if ( arg_flag & GL_COLOR_BUFFER_BIT )
			flag |= GL_COLOR_BUFFER_BIT;

		glClear(flag);
		__getRenderError("glClear");

	}

	void GLcontroller::set_clean_color(const GLcolor &arg_color) {
		_cln_cor = arg_color;
		glClearColor(_cln_cor.r, _cln_cor.g, _cln_cor.b, _cln_cor.a);
		__getRenderError("glClearColor");
	}

	void GLcontroller::adjust_viewport(const GLsizei &arg_width, const GLsizei &arg_height) {
		glViewport(0, 0, arg_width, arg_height);
		__getRenderError("glViewport");
	}

	void GLcontroller::disable_depth_Mask() {
		glDepthMask(GL_FALSE);
		__getRenderError("glDepthMask");
	}

	void GLcontroller::enable_depth_Mask() {
		glDepthMask(GL_TRUE);
		__getRenderError("glDepthMask");
	}

	p_vertex_buf GLcontroller::create_vertex_buffer(GLenum arg_usage, const void *p_arg_data, GLsizeiptr arg_len) const {
		GLuint vboHandle;
		glGenBuffers(1, &vboHandle);
		__getRenderError("glGenBuffers");

		glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
		__getRenderError("glBindBuffer");

		glBufferData(GL_ARRAY_BUFFER, arg_len, p_arg_data, arg_usage);
		__getRenderError("glBufferData");

		p_vertex_buf ret = GLvertexbuffer::create(vboHandle, arg_usage);

		ret->_attach_destory_func([this](GLuint *_name_h) {
			glDeleteBuffers(1, _name_h);
			__getRenderError("glDeleteBuffers");
			}
		);

		return ret;
	}

	p_indicies_buf GLcontroller::create_indicies_buffer(GLenum arg_usage, const void *p_arg_data, GLsizeiptr arg_len) const {
		GLuint iboHandle;
		glGenBuffers(1, &iboHandle);
		__getRenderError("glGenBuffers");

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboHandle);
		__getRenderError("glBindBuffer");

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, arg_len, p_arg_data, arg_usage);
		__getRenderError("glBufferData");

		p_indicies_buf ret = GLindiciesbuffer::create(iboHandle, arg_usage);

		ret->_attach_destory_func([this](GLuint *_name_h) {
			glDeleteBuffers(1, _name_h);
			__getRenderError("glDeleteBuffers");
			}
		);

		return ret;
	}

	p_vertex_arr GLcontroller::create_vertex_array() const {
		GLuint vaoHandle;
		glGenVertexArrays(1, &vaoHandle);
		__getRenderError("glGenVertexArrays");

		p_vertex_arr ret = GLvertexarray::create(vaoHandle);

		ret->_attach_destory_func([this](GLuint *_name_h) {
			glDeleteVertexArrays(1, _name_h);
			__getRenderError("glDeleteBuffers");
			}
		);

		return ret;
	}

	void GLcontroller::bind_vertex_array(p_vertex_arr p_arg_dest) {
		if ( p_arg_dest->is_valid() ) {
			_p_bnd_vert_arr = p_arg_dest;
			glBindVertexArray(p_arg_dest->get_handle());
			__getRenderError("glBindVertexArray");
		}
	}

	void GLcontroller::unbind_vertex_array() {
		_p_bnd_vert_arr = nullptr;

		glBindVertexArray(0);
		__getRenderError("glBindVertexArray");
	}

	void GLcontroller::init_vertex_array(p_vertex_arr p_arg_dest, attribute_information infos, p_indicies_buf p_arg_ind) {

		bind_vertex_array(p_arg_dest);

		p_vertex_buf holdVBO = nullptr;
		for ( auto info : infos ) {
		
			if ( holdVBO != info.vertex_buf ) {
				holdVBO = info.vertex_buf;
				glBindBuffer(GL_ARRAY_BUFFER, p_arg_dest->get_handle());
				__getRenderError("glBindBuffer");
			}
			glEnableVertexAttribArray(info.index);
			__getRenderError("glEnableVertexAttribArray");
			glVertexAttribPointer(info.index, info.size, info.type, info.normalized, info.stride, (const void *) info.offset);
			__getRenderError("glVertexAttribPointer");

			p_arg_dest->attach_buf_info(info);
		}

		if ( p_arg_ind != nullptr ) {
			p_arg_dest->attach_ind_buf(p_arg_ind);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_arg_ind->get_handle());
			__getRenderError("glBindBuffer");
		}

		unbind_vertex_array();

	}

	p_program GLcontroller::create_shader_program(const std::string &src_name) const {

		p_program ret = GLshaderprogram::create(0, src_name);
		return ret;
	}

	bool GLcontroller::compile_program(p_program p_arg_dest) {
		bool ret = false;

		if ( p_arg_dest->ready_to_compile() ) {					
			bool is_compiled_vert, is_compiled_frag;
			GLuint h_vert = glCreateShader(GL_VERTEX_SHADER);
			__getRenderError("glCreateShader");
			GLuint h_frag = glCreateShader(GL_FRAGMENT_SHADER);
			__getRenderError("glCreateShader");
			
			// vertex
			std::string reason;
			auto vert_src = p_arg_dest->get_vert_shd_src();
			is_compiled_vert = _compile_shader(h_vert, vert_src.c_str(), (GLint) vert_src.size(), reason);
			if ( !is_compiled_vert )
				DEBUGConsole::log({"Failed to compile vertex shader: " + p_arg_dest->get_program_name() + ". Reason:\n" + reason });

			// fragment
			reason.clear();
			auto frag_src = p_arg_dest->get_frag_shd_src();
			is_compiled_frag = _compile_shader(h_frag, frag_src.c_str(), (GLint) frag_src.size(), reason);
			if ( !is_compiled_frag )
				DEBUGConsole::log({"Failed to compile fragment shader: "+ p_arg_dest->get_program_name() + ". Reason:\n" + reason });

			if ( is_compiled_vert && is_compiled_frag ) {
				GLuint hProgram;
				hProgram = glCreateProgram();
				__getRenderError("glCreateShader");

				glAttachShader(hProgram, h_vert);
				__getRenderError("glAttachShader");
				
				glAttachShader(hProgram, h_frag);
				__getRenderError("glAttachShader");

				glLinkProgram(hProgram);
				__getRenderError("glLinkProgram");

				GLint success;
				GLchar infoLog[512];
				glGetProgramiv(hProgram, GL_LINK_STATUS, &success);
				if ( !success ) {
					DEBUGConsole::log({ "Failed to link program: " + p_arg_dest->get_program_name() + ". Reason:\n" + infoLog });
					glDeleteProgram(hProgram);
					__getRenderError("glDeleteProgram");

				} else {
					p_arg_dest->set_profile(hProgram);
					p_arg_dest->_attach_destory_func([this](GLuint *_name_h) {
						glDeleteProgram(*_name_h);
						__getRenderError("glDeleteProgram");
						});
					ret = true;
				}

			}

			glDeleteShader(h_vert);
			__getRenderError("glDeleteShader");
			glDeleteShader(h_frag);
			__getRenderError("glDeleteShader");
		}

		return ret;
	}

	bool GLcontroller::use_program(p_program p_arg_dest) {
		if ( p_arg_dest->is_valid() ) {
			_p_bnd_prog = p_arg_dest;
			glUseProgram(_p_bnd_prog->get_handle());
			return __getRenderError("glUseProgram");
		}
	}

	p_texture GLcontroller::create_texture_from_file(const std::string &path, GLtexture::SAMPLAR samplar) const{
		p_texture ret = nullptr;
		vnaon_common::p_bitmap img = vnaon_common::bitmap_img::create_from_file(path);
		if ( img != nullptr ) {
			samplar.width = img->get_width();
			samplar.height = img->get_height();

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

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, samplar.min_filter);
			success |= __getRenderError("glTexParameteri");

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, samplar.mag_filter);
			success |= __getRenderError("glTexParameteri");

			glTexImage2D(GL_TEXTURE_2D, samplar.level, samplar.format, samplar.width, samplar.height, 0, samplar.format, samplar.type, img->get_buffer());
			success |= __getRenderError("glTexImage2D");

			glGenerateMipmap(GL_TEXTURE_2D);
			success |= __getRenderError("glGenerateMipmap");

			// reset texture
			glBindTexture(GL_TEXTURE_2D, _p_ept_tex->get_handle());
			success |= __getRenderError("glBindTexture");

			if ( success ) {
				ret = GLtexture::create(hTex, samplar);
				ret->_attach_destory_func([](GLuint *arg_name) {
					glDeleteTextures(1, arg_name);
					}
				);
			}

		}
		return ret;
	}

	p_skybox GLcontroller::create_skybox_from_file(const std::vector<std::string> &arg_img_sources) const {
		p_skybox p_skybox_object = GLskybox::create(0, arg_img_sources);
		p_skybox_object = p_skybox_object->is_valid() ? p_skybox_object : nullptr;
		return p_skybox_object;
	}

	void GLcontroller::bind_skybox_object(p_skybox arg_skybox) {
		if ( arg_skybox->is_valid() ) {
			_p_bnd_skybox = arg_skybox;
			glBindTexture(GL_TEXTURE_CUBE_MAP, _p_bnd_skybox->get_handle());
			__getRenderError("glBindTexture");
		}
	}

	void GLcontroller::draw_array(GLenum arg_mode, GLint arg_first, GLsizei arg_count) {
		glDrawArrays(arg_mode, arg_first, arg_count);
		__getRenderError("glDrawArrays");
	}

	p_texture GLcontroller::_create_empty_texture() const {
		GLtexture::SAMPLAR samplar{ 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
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

		return GLtexture::create(hTex, samplar);
	}

	bool GLcontroller::_compile_shader(GLuint arg_handle, const GLchar *arg_src, GLint arg_len, std::string &arg_msg) const {
		GLint is_compiled;

		glShaderSource(arg_handle, 1, &arg_src, &arg_len);
		__getRenderError("glShaderSource");

		glCompileShader(arg_handle);
		__getRenderError("glCompileShader");

		glGetShaderiv(arg_handle, GL_COMPILE_STATUS, &is_compiled);
		__getRenderError("glGetShaderiv");
		if ( is_compiled == GL_FALSE ) {
			GLint max_length = 0;
			glGetShaderiv(arg_handle, GL_INFO_LOG_LENGTH, &max_length);
			__getRenderError("glGetShaderiv");
			std::vector<GLchar> err_log(max_length);
			glGetShaderInfoLog(arg_handle, max_length, &max_length, &err_log[0]);
			__getRenderError("glGetShaderiv");
			arg_msg = err_log.data();
			return false;
		} else {
			return true;
		}
	}

	void GLcontroller::_init() {

		_p_ept_tex = _create_empty_texture();

	}

	// for debug
	bool GLcontroller::__getRenderError(const std::string &who) {

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

	void GLcontroller::__resetErrorMessage() {

#ifdef __OPENGL_DEBUG__
		while ( glGetError() != GL_NO_ERROR );
#endif

	}

}