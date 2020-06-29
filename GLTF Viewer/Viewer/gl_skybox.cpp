#include "gl_skybox.h"
#include "gl_manager.h"
#include "common_bitmap.h"



namespace vnaon_gl {

	GLSkyBox::GLSkyBox(GLuint arg_name, const std::vector<std::string> &arg_src) : GLResource(arg_name) {
		_image_source = arg_src;
		valid = Init();
	}

	GLSkyBox::~GLSkyBox() {
	}

	GLSkyBox_p GLSkyBox::Create(GLuint arg_name, const std::vector<std::string> &arg_src) {
		return std::make_shared<GLSkyBox>(arg_name, arg_src);
	}

	bool GLSkyBox::Init() {
		bool ret = false;
		if ( _image_source.size() >= 6 ) {
			GLuint name_id;
			glGenTextures(1, &name_id);
			GLManager::__GetRenderError("glGenTextures");
			glActiveTexture(GL_TEXTURE0);
			GLManager::__GetRenderError("glActiveTexture");

			glBindTexture(GL_TEXTURE_CUBE_MAP, name_id);
			GLManager::__GetRenderError("glBindTexture");

			bool img_load_completed = true;
			for ( int i = 0; i < 6 && img_load_completed; i++ ) {
				auto bitmap = vnaon_common::BitmapImage::CreateFromFile(_image_source[i]);

				if ( bitmap != nullptr ) {
					glTexImage2D(
						GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
						0, GL_RGBA, bitmap->GetWidth(), bitmap->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap->GetBuffer()
					);
					GLManager::__GetRenderError("glTexImage2D");
				} else {
					img_load_completed = false;
				}
			}

			if ( img_load_completed ) {
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				GLManager::__GetRenderError("glTexParameteri");
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				GLManager::__GetRenderError("glTexParameteri");
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				GLManager::__GetRenderError("glTexParameteri");
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				GLManager::__GetRenderError("glTexParameteri");
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				GLManager::__GetRenderError("glTexParameteri");
				glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
				GLManager::__GetRenderError("glBindTexture");
				SetHandle(name_id);
				AttachDestroyFunction([](GLuint *arg_name) {
					glDeleteTextures(1, arg_name);
					GLManager::__GetRenderError("glDeleteTextures");
					}
				);
				ret = true;
			}

		}
		return ret;
	}

}