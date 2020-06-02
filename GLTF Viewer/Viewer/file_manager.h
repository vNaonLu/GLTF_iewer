#pragma once
#include <string>
#include <memory>



namespace vnaon_common {



	/// <summary>
	/// A manager excuting with local file.
	/// </summary>
	class file_manager {

	public:
		typedef char Byte;
		class CMemoryChunk : std::string{
		public:
			CMemoryChunk(Byte *p_arg_bin, std::size_t arg_length);
			CMemoryChunk(std::string p_arg_bin);
			~CMemoryChunk();

			/// <summary>
			/// Specifies a length of buffer in byte.
			/// </summary>
			std::size_t get_size() const;

			/// <summary>
			/// Specifies a buffer.
			/// </summary>
			const char *get_buffer() const;

		};
		typedef std::shared_ptr<CMemoryChunk> MemoryChunk;

	public:

		static MemoryChunk get_binary(const std::string &arg_pth);

	};

}