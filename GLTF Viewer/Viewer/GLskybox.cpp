#include "GLskybox.h"
#include "GLcontroller.h"
#include "bitmap_img.h"



namespace vnaon_gl {

	GLskybox::GLskybox(GLuint arg_name, const std::vector<std::string> &arg_src) : GLresource(arg_name){
		_img_src = arg_src;
		valid = _init();
	}

	GLskybox::~GLskybox() {
	}

	p_skybox GLskybox::create(GLuint arg_name, const std::vector<std::string> &arg_src) {
		return std::make_shared<GLskybox>(arg_name, arg_src);
	}

	bool GLskybox::_init() {
		bool ret = false;
		if ( _img_src.size() >= 6 ) {
			GLuint name_id;
			glGenTextures(1, &name_id);
			GLcontroller::__getRenderError("glGenTextures");
			glActiveTexture(GL_TEXTURE0);
			GLcontroller::__getRenderError("glActiveTexture");

			glBindTexture(GL_TEXTURE_CUBE_MAP, name_id);
			GLcontroller::__getRenderError("glBindTexture");

			bool img_load_completed = true;
			for ( int i = 0; i < 6 && img_load_completed; i++ ) {
				auto bitmap = vnaon_common::bitmap_img::create_from_file(_img_src[i]);

				if ( bitmap != nullptr ) {
					glTexImage2D(
						GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
						0, GL_RGBA, bitmap->get_width(), bitmap->get_height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap->get_buffer()
					);
					GLcontroller::__getRenderError("glTexImage2D");
				} else {
					img_load_completed = false;
				}
			}

			if ( img_load_completed ) {
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				GLcontroller::__getRenderError("glTexParameteri");
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				GLcontroller::__getRenderError("glTexParameteri");
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				GLcontroller::__getRenderError("glTexParameteri");
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				GLcontroller::__getRenderError("glTexParameteri");
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				GLcontroller::__getRenderError("glTexParameteri");
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
				GLcontroller::__getRenderError("glBindTexture");
				set_handle(name_id);
				_attach_destory_func([](GLuint *arg_name) {
					glDeleteTextures(1, arg_name);
					GLcontroller::__getRenderError("glDeleteTextures");
					}
				);
				ret = true;
			}

		}
		return ret;
	}

}