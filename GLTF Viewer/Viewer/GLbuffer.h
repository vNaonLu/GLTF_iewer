#pragma once
#include <vector>
#include "GLobject.h"

namespace vnaon_gl {

	class GLvertexarray;
	typedef std::shared_ptr<GLvertexarray> p_vertex_arr;

	class GLindiciesbuffer;
	typedef std::shared_ptr<GLindiciesbuffer> p_indicies_buf;

	class GLvertexbuffer;
	typedef std::shared_ptr<GLvertexbuffer> p_vertex_buf;



	/// <summary>
	/// An package of the array buffer object, containing vertex buffer.
	/// </summary>
	class GLvertexbuffer : public GLresource{
	
	private:
		GLenum _usage;

	public:
		GLvertexbuffer(GLuint arg_handle, GLenum arg_usage);
		~GLvertexbuffer();

		static p_vertex_buf create(GLuint arg_handle, GLenum arg_usage);

	};



	/// <summary>
	/// An package of the array buffer object, containing indicies buffer.
	/// </summary>
	class GLindiciesbuffer : public GLresource {

	private:
		GLenum _usage;

	public:
		GLindiciesbuffer(GLuint arg_handle, GLenum arg_usage);
		~GLindiciesbuffer();

		static p_indicies_buf create(GLuint arg_handle, GLenum arg_usage);

	};



	/// <summary>
	/// An package of the vertex array object.
	/// </summary>
	class GLvertexarray : public GLresource {
	
	public:
		/// <summary>
		/// A struct containing the buffers and some pointer of buffer view.
		/// NOTE: stride is based on length of bytes.
		/// </summary>
		struct ATTRIB_INFO {
			p_vertex_buf vertex_buf;
			GLuint index;
			GLint size;
			GLenum type;
			GLboolean normalized;
			GLsizei stride;
			GLsizeiptr offset;
		};
	private:
		std::vector<ATTRIB_INFO> _attrib_info;
		p_indicies_buf _ind_buf_obj;

	public:
		GLvertexarray(GLuint arg_handle);
		~GLvertexarray();

		static p_vertex_arr create(GLuint arg_handle);

	protected:
		/// <summary>
		/// Bind an array of buffer information to vertex array object.
		/// </summary>
		/// <param name="arg_info"> Specifies an array of vertex informations.</param>
		/// <param name="arg_ibo"> Specifies an indicies buffer object, can be nullptr.</param>
		void attach_buf_info(ATTRIB_INFO arg_info);

		void attach_ind_buf(p_indicies_buf arg_ibo);

		friend class GLcontroller;
	};

}