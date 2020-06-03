#include <fstream>
#include <sstream>



#include "file_manager.h"
#include "_DEBUG_OBJECT.hpp"



namespace vnaon_common{

	file_manager::memory_chunk::memory_chunk(Byte *p_arg_bin, std::size_t arg_length)
		:std::string(p_arg_bin, arg_length){
	}

	file_manager::memory_chunk::memory_chunk(std::string p_arg_bin)
		: std::string(p_arg_bin){
	}

	file_manager::memory_chunk::~memory_chunk() {
	}

	std::size_t file_manager::memory_chunk::get_size() const {
		return size();
	}

	const char *file_manager::memory_chunk::get_buffer() const {
		return c_str();
	}

	file_manager::p_memory_chunk file_manager::get_binary(const std::string &arg_path) {
		using namespace std;
		p_memory_chunk ret = nullptr;
		ifstream file(arg_path.c_str());

		if ( file.is_open() ) {
			stringstream text;
			text << file.rdbuf();
			file.close();
			ret = make_shared<memory_chunk>(text.str());
		} else {
			DEBUGConsole::log({ "Failed to open the file: " + arg_path });
		}

		return ret;
	}

}