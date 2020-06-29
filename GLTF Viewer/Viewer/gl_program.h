#pragma once
#include <vector>
#include <string>
#include <map>


#include "gl_entity.h"
#include "gl_uniform.h"


namespace vnaon_gl {

	class GLProgram;
	typedef std::shared_ptr<GLProgram> GLProgram_p;



	/// <summary>
	/// A program object used for GLManager.
	/// </summary>
	class GLProgram : public GLResource {
		
	private:
		const static GLsizei MAX_NAME_LEN = 100;
		struct ArgumentProperties {
			GLuint location;
			GLint size;
			GLenum type;
		};
		std::string _program_name;
		std::string _vertex_source;
		std::string _fragment_source;
		std::map<std::string, ArgumentProperties> _attributes_info;
		std::map<std::string, std::vector<p_uniform>> _uniforms_info;

	public:
		GLProgram(GLuint arg_handle, const std::string &arg_name );
		~GLProgram();

		/// <summary>
		/// Generate a shared pointer of the shader program.
		/// </summary>
		static GLProgram_p Create(GLuint arg_handle, const std::string &arg_name);

		/// <summary>
		/// Attach a text of the vertex shader to object.
		/// </summary>
		/// <param name="arg_src"> Specifies the text of the source.</param>
		/// <returns>Specifies attaching success or not.</returns>
		bool AttachVertexShader(const std::string &arg_src);

		/// <summary>
		/// Attach a text of the fragment shader to object.
		/// </summary>
		/// <param name="arg_src"> Specifies the text of the source.</param>
		/// <returns>Specifies attaching success or not.</returns>
		bool AttachFragmentShader(const std::string &arg_src);

		/// <summary>
		/// Attach a text of the vertex shader to object from local file.
		/// </summary>
		/// <param name="arg_src"> Specifies a relative location of sorce.</param>
		/// <returns>Specifies attaching success or not.</returns>
		bool AttachVertexShaderFromFile(const std::string &arg_path);

		/// <summary>
		/// Attach a text of the fragment shader to object from local file.
		/// </summary>
		/// <param name="arg_src"> Specifies a relative location of sorce.</param>
		/// <returns>Specifies attaching success or not.</returns>
		bool AttachFragmentShaderFromFile(const std::string &arg_path);

		/// <summary>
		/// Specifies the name of program.
		/// </summary>
		std::string GetName() const;

		/// <summary>
		/// Get the target GetUnifrom.
		/// </summary>
		p_uniform GetUnifrom(std::string arg_uniform, GLint arg_index = 0);

	protected:

		/// <summary>
		/// Specifies the object is ready to compile or not.
		/// </summary>
		bool ReadyToCompile() const;

		/// <summary>
		/// When the program is link successfully, this function will be called by GLManager.
		/// </summary>
		/// <param name="arg_name"> the handle of GLResource.</param>
		void SetProfile(GLuint arg_name);

		/// <summary>
		/// Specifies the text of the vertex shader.
		/// </summary>
		std::string GetVertexShaderSource() const;

		/// <summary>
		/// Specifies the text of the fragment shader.
		/// </summary>
		std::string GetFragmentShaderSource() const;

	private:
		/// <summary>
		/// Collect the activw attribute in the shader program.
		/// </summary>
		void CollectAttributes();
		
		/// <summary>
		/// Collect the active uniforms in the shader program.
		/// </summary>
		void CollectUnifoms();

		friend class GLManager;
	};

}