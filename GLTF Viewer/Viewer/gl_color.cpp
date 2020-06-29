#include <stdexcept>
#include "gl_color.h"

namespace vnaon_gl {

	GLColor::GLColor() 
		:glm::vec4(0.0f, 0.0f, 0.0f, 0.0f) {
	}

	GLColor::GLColor(const float arg_r, const float arg_g, const float arg_b, const float arg_a)
		: glm::vec4(arg_r, arg_g, arg_b, arg_a) {
	}

	GLColor::GLColor(const std::string &arg_hex) {
		Parse(arg_hex, *this);
	}

	GLColor::~GLColor() {
	}

	bool GLColor::Parse(const std::string &arg_hex, GLColor &arg_out) {
		bool ret = false;

		if ( arg_hex.find('#') != std::string::npos ) {
		
			auto hexadecimalString = arg_hex.substr(1);
			auto size = hexadecimalString.size();

			try {

				if ( size == 8 ) {
					// rgba
					arg_out.r = std::stoi(hexadecimalString.substr(0, 2), nullptr, 16) / 255.0f;
					arg_out.g = std::stoi(hexadecimalString.substr(0, 2), nullptr, 16) / 255.0f;
					arg_out.b = std::stoi(hexadecimalString.substr(0, 2), nullptr, 16) / 255.0f;
					arg_out.a = std::stoi(hexadecimalString.substr(0, 2), nullptr, 16) / 255.0f;
				} else if ( size == 6 ) {
					// rgb
					arg_out.r = std::stoi(hexadecimalString.substr(0, 2), nullptr, 16) / 255.0f;
					arg_out.g = std::stoi(hexadecimalString.substr(0, 2), nullptr, 16) / 255.0f;
					arg_out.b = std::stoi(hexadecimalString.substr(0, 2), nullptr, 16) / 255.0f;
					arg_out.a = 1.0f;
				}
				ret = true;

			} catch (const std::invalid_argument &e){
				e.what();
				arg_out.r = 0.0f;
				arg_out.g = 0.0f;
				arg_out.b = 0.0f;
				arg_out.a = 0.0f;
			}
		
		
		}

		return ret;
	}

}