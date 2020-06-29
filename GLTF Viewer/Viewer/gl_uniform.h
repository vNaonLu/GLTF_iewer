#pragma once
#include <string>



#include "gl_entity.h"



namespace vnaon_gl {

	class GLUniform;
	typedef std::shared_ptr<GLUniform> p_uniform;

	

	class GLUniform {

	private:
		std::string _name;
		GLuint _location;

	public:
		GLUniform(std::string arg_name, GLuint arg_location);
		~GLUniform();

		virtual void SetValue(const void *arg_value);

	protected:
		static p_uniform Create(GLenum arg_type, std::string arg_name, GLuint arg_location);

		GLuint GetLocation() const;

		friend class GLProgram;
	};

	// Vector 1i
	class GLUniform1i : public GLUniform {
	public:
		GLUniform1i(std::string arg_name, GLuint arg_location);
		~GLUniform1i();
		virtual void SetValue(const void *arg_value) override;
	};


	// Matrix 4x4f
	class GLUniformMatrix4fv : public GLUniform {
	public:
		GLUniformMatrix4fv(std::string arg_name, GLuint arg_location);
		~GLUniformMatrix4fv();
		virtual void SetValue(const void *arg_value) override;
	};

}
