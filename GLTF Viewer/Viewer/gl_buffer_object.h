#pragma once
#include <vector>
#include "gl_entity.h"

namespace vnaon_gl {

	class GLVertexArray;
	typedef std::shared_ptr<GLVertexArray> GLVertexArray_p;

	class GLIndiciesBuffer;
	typedef std::shared_ptr<GLIndiciesBuffer> GLIndiciesBuffer_p;

	class GLVertexBuffer;
	typedef std::shared_ptr<GLVertexBuffer> GLVertexBuffer_p;



	/// <summary>
	/// An package of the array buffer object, containing vertex buffer.
	/// </summary>
	class GLVertexBuffer : public GLResource{
	
	private:
		GLenum _usage;

	public:
		GLVertexBuffer(GLuint arg_handle, GLenum arg_usage);
		~GLVertexBuffer();

		static GLVertexBuffer_p Create(GLuint arg_handle, GLenum arg_usage);

	};



	/// <summary>
	/// An package of the array buffer object, containing indicies buffer.
	/// </summary>
	class GLIndiciesBuffer : public GLResource {

	private:
		GLenum _usage;

	public:
		GLIndiciesBuffer(GLuint arg_handle, GLenum arg_usage);
		~GLIndiciesBuffer();

		static GLIndiciesBuffer_p Create(GLuint arg_handle, GLenum arg_usage);

	};



	/// <summary>
	/// An package of the vertex array object.
	/// </summary>
	class GLVertexArray : public GLResource {
	
	public:
		/// <summary>
		/// A struct containing the buffers and some pointer of buffer view.
		/// NOTE: stride is based on length of bytes.
		/// </summary>
		struct VertexAttributeInfomation {
			GLVertexBuffer_p vertex_buffer;
			GLuint index;
			GLint size;
			GLenum type;
			GLboolean normalized;
			GLsizei stride;
			GLsizeiptr offset;
		};
	private:
		std::vector<VertexAttributeInfomation> _attrib_info;
		GLIndiciesBuffer_p _indicies_buffer;

	public:
		GLVertexArray(GLuint arg_handle);
		~GLVertexArray();

		static GLVertexArray_p Create(GLuint arg_handle);

	protected:
		/// <summary>
		/// Bind an array of buffer information to vertex array object.
		/// </summary>
		/// <param name="arg_info"> Specifies an array of vertex informations.</param>
		/// <param name="arg_ibo"> Specifies an indicies buffer object, can be nullptr.</param>
		void AttachVertexBuffer(VertexAttributeInfomation arg_info);

		void AttachIndiciesBuffer(GLIndiciesBuffer_p arg_ibo);

		friend class GLManager;
	};

}