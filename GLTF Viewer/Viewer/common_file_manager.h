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
		class MemoryChunk : std::string{
		public:
			MemoryChunk(Byte *p_arg_bin, std::size_t arg_length);
			MemoryChunk(std::string p_arg_bin);
			~MemoryChunk();

			/// <summary>
			/// Specifies a length of buffer in byte.
			/// </summary>
			std::size_t GetSize() const;

			/// <summary>
			/// Specifies a buffer.
			/// </summary>
			const char *GetBuffer() const;

		};
		typedef std::shared_ptr<MemoryChunk> MemoryChunk_p;

	public:

		static MemoryChunk_p GetBinary(const std::string &arg_pth);

	};

}