#include "common_camera.h"



namespace vnaon_common {

	Camera::Camera() {
		_pos = glm::vec3(0.0);
		_dir = glm::vec3(0.0);
		_ahd = glm::vec3(0.0);
		_view_matrix = glm::mat4(1.0);
		_proj_matrix = glm::mat4(1.0);
		_viewproj_matrix = glm::mat4(1.0);
		_rad_fov = 0.0;
		_aspect = 1.0;
		_far = 0.0;
		_near = 0.0;
	}
	Camera::~Camera() {
	}
	void Camera::SetPerspective(double arg_degFOV, double arg_aspect, double arg_near, double arg_far) {

		_rad_fov = glm::radians(arg_degFOV);
		_aspect = arg_aspect;
		_near = arg_near;
		_far = arg_far;
		InitProjectiveMatrix();

	}
	void Camera::SetPosition(const glm::vec3 &arg_pos) {
		_pos = arg_pos;
		_dir = glm::vec3(0.0) - _pos;
		_ahd = glm::vec3(0, 1, 0);
		_ahd = glm::normalize(_ahd - glm::dot(_ahd, _dir) * _dir);
		InitViewMatrix();
	}
	glm::mat4 Camera::GetRTCMatrix(const glm::vec3 &arg_position) const {
		glm::vec3 offset = _pos - arg_position;
		return glm::translate(glm::mat4(1.0), offset);
	}
	glm::mat4 Camera::GetViewProjectiveMatrix() const {
		return _viewproj_matrix;
	}
	glm::vec3 Camera::GetPosition() const {
		return _pos;
	}
	void Camera::InitViewMatrix() {
		_view_matrix = glm::lookAt(_pos, glm::vec3(0.0), _ahd);
		InitViewProjectiveMatrix();
	}
	void Camera::InitProjectiveMatrix() {
		_proj_matrix = glm::perspective(_rad_fov, _aspect, _near, _far);
		InitViewProjectiveMatrix();
	}
	void Camera::InitViewProjectiveMatrix() {
		_viewproj_matrix = _proj_matrix * _view_matrix;
	}
}