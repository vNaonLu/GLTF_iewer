#ifndef STBI_INCLUDE_STB_IMAGE_H
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#endif



#include "bitmap_img.h"



namespace vnaon_common {

	bitmap_img::bitmap_img(unsigned char *arg_buffer, int arg_width, int arg_height) {

		_p_buf = arg_buffer;
		_width = arg_width;
		_height = arg_height;

	}

	bitmap_img::~bitmap_img() {
		if ( _p_buf != nullptr ) stbi_image_free(_p_buf);
	}

	p_bitmap bitmap_img::create_from_file(const std::string &arg_path) {
		int width, height, channel;
		unsigned char *imgBuffer = stbi_load(arg_path.c_str(), &width, &height, &channel, 4);
		p_bitmap ret = nullptr;
		if(imgBuffer != nullptr) ret = std::make_shared<bitmap_img>(imgBuffer, width, height);

		return ret;
	}

	int bitmap_img::get_width() const {
		return _width;
	}

	int bitmap_img::get_height() const {
		return _height;
	}

	unsigned char *bitmap_img::get_buffer() {
		return _p_buf;
	}

}