#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>



#include "Rect.h"
#include "GLcolor.h"
#include "GLobject.h"
#include "GLtexture.h"
#include "GLprogram.h"
#include "GLbuffer.h"



namespace vnaon_gl {



	/// <summary>
	/// An Object for communication with OpenGL.
	/// </summary>
	class GLcontroller {

	private:
		GLcolor _cln_cor;
		p_texture _p_ept_tex;

		p_vertex_arr _p_bnd_vert_arr;
		p_program _p_bnd_prog;

	public:
		GLcontroller();
		~GLcontroller();

		/// <summary>
		/// Clear buffers to preset values.
		/// </summary>
		/// <param name="FLAG">(GLenum) Bitwise OR of masks that indicate the buffers to be cleared. The four masks are GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_ACCUM_BUFFER_BIT, and GL_STENCIL_BUFFER_BIT.</param>
		void clear(const GLenum &FLAG = GL_COLOR_BUFFER_BIT) const;

		/// <summary>
		/// Specify clear values for the color buffers.
		/// </summary>
		void set_clean_color(const GLcolor &COLOR);

		/// <summary>
		/// Set the viewport.
		/// </summary>
		/// <param name="WIDTH">(GLsizei) Specify the width of the viewport.</param>
		/// <param name="HEIGHT">(GLsizei) Specify the height of the viewport.</param>
		void adjust_viewport(const GLsizei &WIDTH, const GLsizei &HEIGHT);



		/// <summary>
		/// Create and initialize a vertex buffer object's data .
		/// </summary>
		/// <param name="USAGE">(GLenum) Specifies the expected usage pattern of the data store.</param>
		/// <param name="DATA">(void*) Specifies a pointer to data that will be copied into the data store for initialization, or NULL if no data is to be copied.</param>
		/// <param name="SIZE">(GLsizeiptr) Specifies the size in bytes of the buffer object's new data store.</param>
		p_vertex_buf create_vertex_buffer(GLenum USAGE, const void* DATA = nullptr, GLsizeiptr SIZE = 0) const;
		
		/// <summary>
		/// Create and initialize a indicies buffer object's data .
		/// </summary>
		/// <param name="USAGE">(GLenum) Specifies the expected usage pattern of the data store.</param>
		/// <param name="DATA">(void*) Specifies a pointer to data that will be copied into the data store for initialization, or NULL if no data is to be copied.</param>
		/// <param name="SIZE">(GLsizeiptr) Specifies the size in bytes of the buffer object's new data store.</param>
		p_indicies_buf create_indicies_buffer(GLenum USAGE, const void *DATA = nullptr, GLsizeiptr SIZE = 0) const;

		/// <summary>
		/// Generate vertex array object names.
		/// </summary>
		p_vertex_arr create_vertex_array() const;

		/// <summary>
		/// Bind a vertex array object
		/// </summary>
		/// <param name="VERTEX_ARRAY">(VAO) Specifies the name of the vertex array to bind.</param>
		void bind_vertex_array(p_vertex_arr VERTEX_ARRAY);

		/// <summary>
		/// Bind a null vertex array object
		/// </summary>
		void unbind_vertex_array();

		typedef std::vector<GLvertexarray::ATTRIB_INFO> attribute_information;
		/// <summary>
		/// Initialize a vertex array object with binding vertex buffer and indicies buffer.
		/// </summary>
		void init_vertex_array(p_vertex_arr VERTEX_ARRAY, attribute_information ATTRIB_INFO, p_indicies_buf INDICIES_BUFFER = nullptr);

		/// <summary>
		/// Create a shader program object.
		/// </summary>
		/// <param name="PROGRAM_NAME">(string) Specify the name of program.</param>
		p_program create_shader_program(const std::string &PROGRAM_NAME = "Untitled Shader") const;

		/// <summary>
		/// Compile and Link a program object a program.
		/// </summary>
		bool compile_program(p_program PROGRAM);

		/// <summary>
		/// Installs a program object as part of current rendering state
		/// </summary>
		/// <param name="PROGRAM">Specifies the handle of the program object whose executables are to be used as part of current rendering state.</param>
		/// <returns></returns>
		bool use_program(p_program PROGRAM);


		/// <summary>
		/// Create and initialize a texture with local loacation of the file.
		/// </summary>
		p_texture create_texture_from_file(
			const std::string &FILE_LOCATION,
			GLtexture::SAMPLAR TEXTURE_SAMPLAR = GLtexture::SAMPLAR{ 
				0, 
				1, 
				1,
				GL_RGBA, 
				GL_UNSIGNED_BYTE,
				GL_LINEAR,
				GL_LINEAR,
				GL_REPEAT,
				GL_REPEAT
			}
		) const;


	private:
		p_texture _create_empty_texture() const;

		bool _compile_shader(GLuint arg_handle, GLchar *arg_src, GLint arg_len, std::string &arg_msg) const;

		void _init();

	private:
		//Used for debug error.
		static bool __getRenderError(const std::string &who);
		static void __resetErrorMessage();

	};

}