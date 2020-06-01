#pragma once
#include <memory>
#include <string>

namespace vnaon_common{ 

	class CBitmapImg;
	typedef std::shared_ptr<CBitmapImg> pBitmapImg;

	class CBitmapImg{ 
	
	protected:
		unsigned char *pBuffer;
		int mWidth;
		int mHeight;

	public:
		CBitmapImg(unsigned char *buffer, std::size_t width, std::size_t height);
		~CBitmapImg();

		static pBitmapImg createFromFile(const std::string &path);

		int getWidth() const;

		int getHeight() const;

		unsigned char *getBuffer();
	
	};

}