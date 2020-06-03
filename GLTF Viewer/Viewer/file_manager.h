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
		class memory_chunk : std::string{
		public:
			memory_chunk(Byte *p_arg_bin, std::size_t arg_length);
			memory_chunk(std::string p_arg_bin);
			~memory_chunk();

			/// <summary>
			/// Specifies a length of buffer in byte.
			/// </summary>
			std::size_t get_size() const;

			/// <summary>
			/// Specifies a buffer.
			/// </summary>
			const char *get_buffer() const;

		};
		typedef std::shared_ptr<memory_chunk> p_memory_chunk;

	public:

		static p_memory_chunk get_binary(const std::string &arg_pth);

	};

}