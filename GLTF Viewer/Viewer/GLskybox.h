#pragma once
#include <vector>
#include <string>

#include "GLobject.h"



namespace vnaon_gl {

	class GLcontroller;

	class GLskybox;
	typedef std::shared_ptr<GLskybox> p_skybox;



	class GLskybox : public GLresource{

	private:
		std::vector<std::string> _img_src;

	public:
		GLskybox(GLuint arg_name, const std::vector<std::string> &arg_src);
		~GLskybox();


		static p_skybox create(GLuint arg_name, const std::vector<std::string> &arg_src);

	private:
		bool _init();

		friend class GLcontroller;
	};

}