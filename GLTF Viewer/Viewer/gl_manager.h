#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>



#include "gl_entity.h"
#include "gl_color.h"
#include "gl_texture.h"
#include "gl_program.h"
#include "gl_buffer_object.h"
#include "gl_skybox.h"



namespace vnaon_gl {



	/// <summary>
	/// An Object for communication with OpenGL.
	/// </summary>
	class GLManager {

	private:
		GLColor _cln_cor;
		GLTexture_p _p_ept_tex;

		GLVertexArray_p _p_bnd_vert_arr;
		GLProgram_p _p_bnd_prog;
		GLSkyBox_p _p_bnd_skybox;

	public:
		GLManager();
		~GLManager();

		/// <summary>
		/// Clear buffers to preset values.
		/// </summary>
		/// <param name="FLAG">(GLenum) Bitwise OR of masks that indicate the buffers to be cleared. The four masks are GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_ACCUM_BUFFER_BIT, and GL_STENCIL_BUFFER_BIT.</param>
		void Clear(const GLenum &FLAG = GL_COLOR_BUFFER_BIT) const;

		/// <summary>
		/// Specify Clear values for the color buffers.
		/// </summary>
		void SetClearColor(const GLColor &COLOR);

		/// <summary>
		/// Set the viewport.
		/// </summary>
		/// <param name="WIDTH">(GLsizei) Specify the width of the viewport.</param>
		/// <param name="HEIGHT">(GLsizei) Specify the height of the viewport.</param>
		void AdjustViewport(const GLsizei &WIDTH, const GLsizei &HEIGHT);

		void DisableDepthMask();
		void EnableDepthMask();


		/// <summary>
		/// Create and initialize a vertex buffer object's data .
		/// </summary>
		/// <param name="USAGE">(GLenum) Specifies the expected usage pattern of the data store.</param>
		/// <param name="DATA">(void*) Specifies a pointer to data that will be copied into the data store for initialization, or NULL if no data is to be copied.</param>
		/// <param name="SIZE">(GLsizeiptr) Specifies the size in bytes of the buffer object's new data store.</param>
		GLVertexBuffer_p CreateVertexBuffer(GLenum USAGE, const void* DATA = nullptr, GLsizeiptr SIZE = 0) const;
		
		/// <summary>
		/// Create and initialize a indicies buffer object's data .
		/// </summary>
		/// <param name="USAGE">(GLenum) Specifies the expected usage pattern of the data store.</param>
		/// <param name="DATA">(void*) Specifies a pointer to data that will be copied into the data store for initialization, or NULL if no data is to be copied.</param>
		/// <param name="SIZE">(GLsizeiptr) Specifies the size in bytes of the buffer object's new data store.</param>
		GLIndiciesBuffer_p CreateIndiciesBuffer(GLenum USAGE, const void *DATA = nullptr, GLsizeiptr SIZE = 0) const;

		/// <summary>
		/// Generate vertex array object names.
		/// </summary>
		GLVertexArray_p CreateVertexArray() const;

		/// <summary>
		/// Bind a vertex array object
		/// </summary>
		/// <param name="VERTEX_ARRAY">(VAO) Specifies the name of the vertex array to bind.</param>
		void BindVertexArray(GLVertexArray_p VERTEX_ARRAY);

		/// <summary>
		/// Bind a null vertex array object
		/// </summary>
		void UnbindVertexArray();

		typedef std::vector<GLVertexArray::VertexAttributeInfomation> VertexAttributes;
		/// <summary>
		/// Initialize a vertex array object with binding vertex buffer and indicies buffer.
		/// </summary>
		void SetVertexArray(GLVertexArray_p VERTEX_ARRAY, VertexAttributes VertexAttributeInfomation, GLIndiciesBuffer_p INDICIES_BUFFER = nullptr);

		/// <summary>
		/// Create a shader program object.
		/// </summary>
		/// <param name="PROGRAM_NAME">(string) Specify the name of program.</param>
		GLProgram_p CreateProgram(const std::string &PROGRAM_NAME = "Untitled Shader") const;

		/// <summary>
		/// Compile and Link a program object a program.
		/// </summary>
		bool CompileProgram(GLProgram_p PROGRAM);

		/// <summary>
		/// Installs a program object as part of current rendering state
		/// </summary>
		/// <param name="PROGRAM">Specifies the handle of the program object whose executables are to be used as part of current rendering state.</param>
		/// <returns></returns>
		bool UseProgram(GLProgram_p PROGRAM);

		/// <summary>
		/// Create and initialize a texture with local loacation of the file.
		/// </summary>
		GLTexture_p CreateTextureFromFile(
			const std::string &FILE_LOCATION,
			GLTexture::SAMPLER TEXTURE_SAMPLAR = GLTexture::SAMPLER{ 
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

		/// <summary>
		/// Create a skybox texture object.
		/// </summary>
		/// <param name="IAMGE_SOURCES"> The loaction of the image source, in ordered of right, left, top, bottom, back and front.</param>
		GLSkyBox_p CreateSkyBoxFromFile(const std::vector<std::string> &IAMGE_SOURCES) const;
		void BindSkybox(GLSkyBox_p DEST);


		void DrawArrays(GLenum arg_mode, GLint arg_first, GLsizei arg_count);

	private:
		GLTexture_p CreateEmptyTexture() const;

		bool CompileShader(GLuint arg_handle, const GLchar *arg_src, GLint arg_len, std::string &arg_msg) const;

		void Init();

	public:
		//Used for debug error.
		static bool __GetRenderError(const std::string &who);
		static void __ResetErrorMessage();

	};

}