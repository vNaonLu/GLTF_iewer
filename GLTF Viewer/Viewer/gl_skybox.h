#pragma once
#include <vector>
#include <string>

#include "gl_entity.h"



namespace vnaon_gl {

	class GLManager;

	class GLSkyBox;
	typedef std::shared_ptr<GLSkyBox> GLSkyBox_p;



	class GLSkyBox : public GLResource{

	private:
		std::vector<std::string> _image_source;

	public:
		GLSkyBox(GLuint arg_name, const std::vector<std::string> &arg_src);
		~GLSkyBox();


		static GLSkyBox_p Create(GLuint arg_name, const std::vector<std::string> &arg_src);

	private:
		bool Init();

		friend class GLManager;
	};

}