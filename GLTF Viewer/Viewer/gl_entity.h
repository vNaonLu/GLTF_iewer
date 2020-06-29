#pragma once
#include <glad/glad.h>
#include <memory>
#include <functional>

namespace vnaon_gl {

	class GLManager;

	class GLResource;
	typedef std::shared_ptr<GLResource> GLResource_p;



	/// <summary>
	/// An interface of OpenGL's the resorce.
	/// </summary>
	class GLResource {
	
	public:
		typedef std::function<void(GLuint*)>  d_destroy_func;

	private:
		GLuint _name_h;
		d_destroy_func _destroy_function;

	protected:
		bool valid;

	public:
		GLResource(GLuint arg_handle);
		virtual ~GLResource();

		/// <summary>
		/// Get the handle object of the OpenGL's resource.
		/// </summary>
		/// <returns>(GLint) The handle of OpenGL's object.</returns>
		GLuint GetHandle() const;


	protected:
		virtual bool IsValid() const;

		void SetHandle(GLuint arg_handle);
		/// <summary>
		/// Attach a function to OpenGL's resource, which will be called when the destruction of the object.
		/// </summary>
		/// <param name="func">(void(GLuint*)) A function with input that is the handle of object, and will not return anything.</param>
		void AttachDestroyFunction(d_destroy_func arg_func);

		friend class GLManager;	
	};

}