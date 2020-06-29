#pragma once
#include <memory>
#include <string>

namespace vnaon_common{ 

	class BitmapImage;
	typedef std::shared_ptr<BitmapImage> BitmapImage_p;



	/// <summary>
	/// An object of bitmap.
	/// </summary>
	class BitmapImage{ 
	
	private:
		unsigned char *_p_buffer;
		int _width;
		int _height;

	public:
		BitmapImage(unsigned char *arg_buf, int arg_width, int arg_height);
		~BitmapImage();

		static BitmapImage_p CreateFromFile(const std::string &arg_path);

		int GetWidth() const;

		int GetHeight() const;

		unsigned char *GetBuffer();
	
	};

}