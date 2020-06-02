#pragma once
#include "GLobject.h"
#include <vector>
#include <string>



namespace vnaon_gl {

	class GLshaderprogram;
	typedef std::shared_ptr<GLshaderprogram> p_program;



	/// <summary>
	/// A program object used for GLcontroller.
	/// </summary>
	class GLshaderprogram : public GLresource {
		
	private:
		GLboolean _valid;
		std::string _program_name;
		std::string _vert_shd_src;
		std::vector<std::string> _frag_shd_srcs;

	public:
		GLshaderprogram(GLuint arg_handle, const std::string &arg_name );
		~GLshaderprogram();

		static p_program create(GLuint arg_handle, const std::string &arg_name);

		/// <summary>
		/// Attach a text of the vertex shader to object.
		/// </summary>
		/// <param name="arg_src"> Specifies the text of the source.</param>
		/// <returns>Specifies attaching success or not.</returns>
		bool attach_vertex_shader(const std::string &arg_src);

		/// <summary>
		/// Attach a text of the fragment shader to object.
		/// </summary>
		/// <param name="arg_src"> Specifies the text of the source.</param>
		/// <returns>Specifies attaching success or not.</returns>
		bool attach_fragment_shader(const std::string &arg_src);

		/// <summary>
		/// Attach a text of the vertex shader to object from local file.
		/// </summary>
		/// <param name="arg_src"> Specifies a relative location of sorce.</param>
		/// <returns>Specifies attaching success or not.</returns>
		bool attach_vertex_shader_from_file(const std::string &arg_path);

		/// <summary>
		/// Attach a text of the fragment shader to object from local file.
		/// </summary>
		/// <param name="arg_src"> Specifies a relative location of sorce.</param>
		/// <returns>Specifies attaching success or not.</returns>
		bool attach_fragment_shader_from_file(const std::string &arg_path);

		/// <summary>
		/// Specifies the object is valid or invalid.
		/// </summary>
		bool is_valid() const;

		/// <summary>
		/// Specifies the name of program.
		/// </summary>
		std::string get_program_name() const;

	protected:
		/// <summary>
		/// Specifies the object is ready to compile or not.
		/// </summary>
		bool ready_to_compile() const;

		/// <summary>
		/// When the program is link successfully, this function will be called by GLcontroller.
		/// </summary>
		/// <param name="arg_name"> the handle of GLresource.</param>
		void set_profile(GLuint arg_name);

		/// <summary>
		/// Copy the text of the vertex shader.
		/// </summary>
		/// <param name="p_arg_out"> Specifies an output for the text. NOTE: Should be delete.</param>
		/// <param name="arg_len"> Specifies a length of vertex shader.</param>
		void cpy_vert_shd_src(GLchar *p_arg_out, GLsizei &arg_len) const;

		/// <summary>
		/// Copy the text of the fragment shader.
		/// </summary>
		/// <param name="p_arg_out"> Specifies an output for the text. NOTE: Should be delete.</param>
		/// <param name="arg_len"> Specifies a length of fragment shader.</param>
		void cpy_frag_shd_src(std::vector<GLchar *> &p_arg_out, std::vector<GLsizei> &arg_len) const;

		friend class GLcontroller;
	};

}