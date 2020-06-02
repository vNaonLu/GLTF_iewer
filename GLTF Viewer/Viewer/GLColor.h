#pragma once
#include <glm/vec4.hpp>
#include <string>

namespace vnaon_gl {



	/// <summary>
	/// An object specified a color, which containing 4-channel value of color with range[0, 1].
	/// </summary>
	class GLcolor : public glm::vec4{

	public:
		GLcolor();
		GLcolor(const float arg_r, const float arg_g, const float arg_b, const float arg_a);
		GLcolor(const std::string &arg_hex);
		~GLcolor();

	private:
		static bool _parse_hex_str(const std::string &arg_hex, GLcolor &arg_out);

	};

}
