#pragma once
#include <string>



#include "GLobject.h"



namespace vnaon_gl {

	class GLuniform;
	typedef std::shared_ptr<GLuniform> p_uniform;

	

	class GLuniform {

	private:
		std::string _name;
		GLuint _location;

	public:
		GLuniform(std::string arg_name, GLuint arg_location);
		~GLuniform();

		virtual void set_value(const void *arg_value);

	protected:
		static p_uniform create(GLenum arg_type, std::string arg_name, GLuint arg_location);

		GLuint get_location() const;

		friend class GLshaderprogram;
	};

	// Vector 1i
	class GLint_vector_1 : public GLuniform {
	public:
		GLint_vector_1(std::string arg_name, GLuint arg_location);
		~GLint_vector_1();
		virtual void set_value(const void *arg_value) override;
	};


	// Matrix 4x4f
	class GLfloat_matrix_4x4 : public GLuniform {
	public:
		GLfloat_matrix_4x4(std::string arg_name, GLuint arg_location);
		~GLfloat_matrix_4x4();
		virtual void set_value(const void *arg_value) override;
	};

}
