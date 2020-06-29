#include <fstream>
#include <sstream>



#include "common_file_manager.h"
#include "debug_tools.hpp"



namespace vnaon_common{

	file_manager::MemoryChunk::MemoryChunk(Byte *p_arg_bin, std::size_t arg_length)
		:std::string(p_arg_bin, arg_length){
	}

	file_manager::MemoryChunk::MemoryChunk(std::string p_arg_bin)
		: std::string(p_arg_bin){
	}

	file_manager::MemoryChunk::~MemoryChunk() {
	}

	std::size_t file_manager::MemoryChunk::GetSize() const {
		return size();
	}

	const char *file_manager::MemoryChunk::GetBuffer() const {
		return c_str();
	}

	file_manager::MemoryChunk_p file_manager::GetBinary(const std::string &arg_path) {
		using namespace std;
		MemoryChunk_p ret = nullptr;
		ifstream file(arg_path.c_str());

		if ( file.is_open() ) {
			stringstream text;
			text << file.rdbuf();
			file.close();
			ret = make_shared<MemoryChunk>(text.str());
		} else {
			_DebugTools_::Log({ "Failed to open the file: " + arg_path });
		}

		return ret;
	}

}