#include <stdexcept>
#include "GLcolor.h"

namespace vNaonGL {

	GLcolor::GLcolor() 
		:glm::vec4(0.0f, 0.0f, 0.0f, 0.0f) {
	}

	GLcolor::GLcolor(const float r, const float g, const float b, const float a)
		: glm::vec4(r, g, b, a) {
	}

	GLcolor::GLcolor(const std::string &hexString) {
		ParseHexadecimalColor(hexString, *this);
	}

	GLcolor::~GLcolor() {
	}

	bool GLcolor::ParseHexadecimalColor(const std::string &cHexString, GLcolor &rOut) {
		bool ret = false;

		if ( cHexString.find('#') != std::string::npos ) {
		
			auto hexadecimalString = cHexString.substr(1);
			auto size = hexadecimalString.size();

			try {

				if ( size == 8 ) {
					// rgba
					rOut.r = std::stoi(hexadecimalString.substr(0, 2), nullptr, 16) / 255.0f;
					rOut.g = std::stoi(hexadecimalString.substr(0, 2), nullptr, 16) / 255.0f;
					rOut.b = std::stoi(hexadecimalString.substr(0, 2), nullptr, 16) / 255.0f;
					rOut.a = std::stoi(hexadecimalString.substr(0, 2), nullptr, 16) / 255.0f;
				} else if ( size == 6 ) {
					// rgb
					rOut.r = std::stoi(hexadecimalString.substr(0, 2), nullptr, 16) / 255.0f;
					rOut.g = std::stoi(hexadecimalString.substr(0, 2), nullptr, 16) / 255.0f;
					rOut.b = std::stoi(hexadecimalString.substr(0, 2), nullptr, 16) / 255.0f;
					rOut.a = 1.0f;
				}
				ret = true;

			} catch (const std::invalid_argument &e){
				e.what();
				rOut.r = 0.0f;
				rOut.g = 0.0f;
				rOut.b = 0.0f;
				rOut.a = 0.0f;
			}
		
		
		}

		return ret;
	}

}