#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



namespace vnaon_common {

	class camera {

	private:
		double _rad_fov;
		double _aspect;
		double _far;
		double _near;
		glm::vec3 _pos;
		glm::vec3 _dir;
		glm::vec3 _ahd;

		glm::mat4 _view_matrix;
		glm::mat4 _proj_matrix;
		glm::mat4 _viewproj_matrix;

	public:
		camera();
		~camera();

		void set_perspective(double arg_degFOV, double arg_aspect, double arg_near, double arg_far);

		void set_camera(const glm::vec3 &arg_pos, const glm::vec3 &arg_dir, const glm::vec3 &arg_ahd);

		glm::mat4 get_model_offset_matrix(const glm::vec3 &arg_position) const;

		glm::vec3 get_pos() const;

	private:
		void _init_view_matrix();
		void _init_proj_matrix();
		void _init_viewproj_matrix();

	};

}