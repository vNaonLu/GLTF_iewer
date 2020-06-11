#pragma once
#include <vector>
#include <string>
#include <map>


#include "GLobject.h"
#include "GLuniform.h"


namespace vnaon_gl {

	class GLshaderprogram;
	typedef std::shared_ptr<GLshaderprogram> p_program;



	/// <summary>
	/// A program object used for GLcontroller.
	/// </summary>
	class GLshaderprogram : public GLresource {
		
	private:
		const static GLsizei MAX_NAME_LEN = 100;
		struct _ARG_PROP {
			GLuint location;
			GLint size;
			GLenum type;
		};
		std::string _program_name;
		std::string _vert_shd_src;
		std::string _frag_shd_srcs;
		std::map<std::string, _ARG_PROP> _attribs_info;
		std::map<std::string, std::vector<p_uniform>> _unifors_info;

	public:
		GLshaderprogram(GLuint arg_handle, const std::string &arg_name );
		~GLshaderprogram();

		/// <summary>
		/// Generate a shared pointer of the shader program.
		/// </summary>
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
		/// Specifies the name of program.
		/// </summary>
		std::string get_program_name() const;

		/// <summary>
		/// Get the target uniform.
		/// </summary>
		p_uniform uniform(std::string arg_uniform, GLint arg_index = 0);

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
		/// Specifies the text of the vertex shader.
		/// </summary>
		std::string get_vert_shd_src() const;

		/// <summary>
		/// Specifies the text of the fragment shader.
		/// </summary>
		std::string get_frag_shd_src() const;

	private:
		/// <summary>
		/// Collect the activw attribute in the shader program.
		/// </summary>
		void _collect_attribs();
		
		/// <summary>
		/// Collect the active uniforms in the shader program.
		/// </summary>
		void _collect_unifors();

		friend class GLcontroller;
	};

}