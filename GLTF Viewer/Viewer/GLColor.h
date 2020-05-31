#pragma once
#include <glm/vec4.hpp>
#include <string>

namespace vNaonGL {

	/*
	An object specifies color used in openGL.
	 */
	class GLcolor : public glm::vec4{

	public:
		GLcolor();
		GLcolor(const float r, const float g, const float b, const float a);
		GLcolor(const std::string &hexString);
		~GLcolor();

	public:
		static bool ParseHexadecimalColor(const std::string &cHexString, GLcolor &rOut);

	};

}
