#include"Image.h"

namespace vNaonCommon {

	CBitmapImg::CBitmapImg(unsigned char *buffer, std::size_t width, std::size_t height) {

		pBuffer = buffer;
		mWidth = width;
		mHeight = height;

	}

	CBitmapImg::~CBitmapImg() {
		if ( pBuffer != nullptr ) stbi_image_free(pBuffer);
	}

	pBitmapImg CBitmapImg::createFromFile(const std::string &path) {
		int width, height, channel;
		unsigned char *imgBuffer = stbi_load(path.c_str(), &width, &height, &channel, 4);
		pBitmapImg ret = nullptr;
		if(imgBuffer != nullptr) ret = std::make_shared<CBitmapImg>(imgBuffer, width, height);

		return ret;
	}

	int CBitmapImg::getWidth() const {
		return mWidth;
	}

	int CBitmapImg::getHeight() const {
		return mHeight;
	}

	unsigned char *CBitmapImg::getBuffer() {
		return pBuffer;
	}

}