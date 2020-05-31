#include <fstream>
#include <sstream>

#include "FileManager.h"
#include "_DEBUG_OBJECT.hpp"

namespace vNaonCommon{

	FileManager::CMemoryChunk::CMemoryChunk(Byte *pBin, std::size_t length)
		:std::string(pBin, length){
	}

	FileManager::CMemoryChunk::CMemoryChunk(std::string pBin) 
		: std::string(pBin){
	}

	FileManager::CMemoryChunk::~CMemoryChunk() {
	}

	std::size_t FileManager::CMemoryChunk::getSize() const {
		return size();
	}

	std::string FileManager::CMemoryChunk::getBuffer() const {
		return std::string(c_str());
	}

	FileManager::MemoryChunk FileManager::getBinaryFromFile(const std::string &path) {
		using namespace std;
		MemoryChunk ret = nullptr;
		ifstream file;
		file.exceptions(ifstream::failbit | ifstream::badbit);

		try {
			file.open(path.c_str(), ios::out);
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