#include <fstream>
#include <sstream>



#include "file_manager.h"
#include "_DEBUG_OBJECT.hpp"



namespace vnaon_common{

	file_manager::CMemoryChunk::CMemoryChunk(Byte *p_arg_bin, std::size_t arg_length)
		:std::string(p_arg_bin, arg_length){
	}

	file_manager::CMemoryChunk::CMemoryChunk(std::string p_arg_bin)
		: std::string(p_arg_bin){
	}

	file_manager::CMemoryChunk::~CMemoryChunk() {
	}

	std::size_t file_manager::CMemoryChunk::get_size() const {
		return size();
	}

	const char *file_manager::CMemoryChunk::get_buffer() const {
		return c_str();
	}

	file_manager::MemoryChunk file_manager::get_binary(const std::string &arg_path) {
		using namespace std;
		MemoryChunk ret = nullptr;
		ifstream file;
		file.exceptions(ifstream::failbit | ifstream::badbit);

		try {
			file.open(arg_path.c_str(), ios::out);
			stringstream text;
			text << file.rdbuf();
			file.close();

			ret = make_shared<CMemoryChunk>(text.str());
		} catch ( ifstream::failure e ) {
			DEBUGConsole::log({ e.what() });
		}

		return ret;
	}

}