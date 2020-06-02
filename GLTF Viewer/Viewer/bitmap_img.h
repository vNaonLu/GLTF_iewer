#pragma once
#include <memory>
#include <string>

namespace vnaon_common{ 

	class bitmap_img;
	typedef std::shared_ptr<bitmap_img> p_bitmap;



	/// <summary>
	/// An object of bitmap.
	/// </summary>
	class bitmap_img{ 
	
	private:
		unsigned char *_p_buf;
		int _width;
		int _height;

	public:
		bitmap_img(unsigned char *arg_buf, int arg_width, int arg_height);
		~bitmap_img();

		static p_bitmap create_from_file(const std::string &arg_path);

		int get_width() const;

		int get_height() const;

		unsigned char *get_buffer();
	
	};

}