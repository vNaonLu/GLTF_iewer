#ifndef STBI_INCLUDE_STB_IMAGE_H
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#endif



#include "common_bitmap.h"



namespace vnaon_common {

	BitmapImage::BitmapImage(unsigned char *arg_buffer, int arg_width, int arg_height) {

		_p_buffer = arg_buffer;
		_width = arg_width;
		_height = arg_height;

	}

	BitmapImage::~BitmapImage() {
		if ( _p_buffer != nullptr ) stbi_image_free(_p_buffer);
	}

	BitmapImage_p BitmapImage::CreateFromFile(const std::string &arg_path) {
		int width, height, channel;
		unsigned char *imgBuffer = stbi_load(arg_path.c_str(), &width, &height, &channel, 4);
		BitmapImage_p ret = nullptr;
		if(imgBuffer != nullptr) ret = std::make_shared<BitmapImage>(imgBuffer, width, height);

		return ret;
	}

	int BitmapImage::GetWidth() const {
		return _width;
	}

	int BitmapImage::GetHeight() const {
		return _height;
	}

	unsigned char *BitmapImage::GetBuffer() {
		return _p_buffer;
	}

}