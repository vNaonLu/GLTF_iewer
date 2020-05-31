#pragma once
#include <glad/glad.h>
#include <memory>
#include <functional>

namespace vNaonGL {
	class GLdevice;

	class GLresource;
	typedef std::shared_ptr<GLresource> pGLresource;

	class GLvertexbuffer;
	typedef std::shared_ptr<GLvertexbuffer> pGLvertexbuffer;

	class GLindiciesbuffer;
	typedef std::shared_ptr<GLindiciesbuffer> pGLindiciesbuffer;

	class GLvertexarray;
	typedef std::shared_ptr<GLvertexarray> pGLvertexarray;

	class GLshaderprogram;
	typedef std::shared_ptr<GLshaderprogram> pGLshaderprogram;

	class GLresource {
	
	protected:
		typedef std::function<void(GLuint*)>  DestroyFunc;
		GLuint hName;
		DestroyFunc pDestroy;

	public:
		GLresource(GLuint handle);
		~GLresource();

		GLuint getHandle() const;

	protected:
		void attachDestoryFunc(DestroyFunc func);

		friend class GLdevice;
	
	};

}