#pragma once
#include <string>
#include <memory>

namespace vNaonCommon {

	class FileManager {

	public:
		typedef char Byte;
		class CMemoryChunk : std::string{
		public:
			CMemoryChunk(Byte *pBin, std::size_t length);
			CMemoryChunk(std::string pBin);
			~CMemoryChunk();

			std::size_t getSize() const;

			std::string getBuffer() const;

		};
		typedef std::shared_ptr<CMemoryChunk> MemoryChunk;

	public:

		static MemoryChunk getBinaryFromFile(const std::string &path);

	};

}