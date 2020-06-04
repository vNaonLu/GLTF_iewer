#pragma once
#include <glad/glad.h>
#include <memory>
#include <functional>

namespace vnaon_gl {

	class GLcontroller;

	class GLresource;
	typedef std::shared_ptr<GLresource> p_res;



	/// <summary>
	/// An interface of OpenGL's the resorce.
	/// </summary>
	class GLresource {
	
	public:
		typedef std::function<void(GLuint*)>  d_destroy_func;

	private:
		GLuint _name_h;
		d_destroy_func destroy_function;

	protected:
		bool valid;

	public:
		GLresource(GLuint arg_handle);
		virtual ~GLresource();

		/// <summary>
		/// Get the handle object of the OpenGL's resource.
		/// </summary>
		/// <returns>(GLint) The handle of OpenGL's object.</returns>
		GLuint get_handle() const;


	protected:
		virtual bool is_valid() const;

		void set_handle(GLuint arg_handle);
		/// <summary>
		/// Attach a function to OpenGL's resource, which will be called when the destruction of the object.
		/// </summary>
		/// <param name="func">(void(GLuint*)) A function with input that is the handle of object, and will not return anything.</param>
		void _attach_destory_func(d_destroy_func arg_func);

		friend class GLcontroller;	
	};

}