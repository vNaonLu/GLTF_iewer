#pragma once
#include <glm/vec4.hpp>
#include <string>

namespace vnaon_gl {



	/// <summary>
	/// An object specified a color, which containing 4-channel value of color with range[0, 1].
	/// </summary>
	class GLColor : public glm::vec4{

	public:
		GLColor();
		GLColor(const float arg_r, const float arg_g, const float arg_b, const float arg_a);
		GLColor(const std::string &arg_hex);
		~GLColor();

	private:
		static bool Parse(const std::string &arg_hex, GLColor &arg_out);

	};

}
