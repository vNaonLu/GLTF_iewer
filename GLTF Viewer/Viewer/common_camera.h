#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



namespace vnaon_common {

	class Camera {

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
		Camera();
		~Camera();

		void SetPerspective(double arg_degFOV, double arg_aspect, double arg_near, double arg_far);

		void SetPosition(const glm::vec3 &arg_pos);

		glm::mat4 GetRTCMatrix(const glm::vec3 &arg_position) const;

		glm::mat4 GetViewProjectiveMatrix() const;

		glm::vec3 GetPosition() const;

	private:
		void InitViewMatrix();
		void InitProjectiveMatrix();
		void InitViewProjectiveMatrix();

	};

}