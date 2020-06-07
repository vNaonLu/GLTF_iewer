#include "scenes_engine.h"
#include "GLprogram.h"
#include "GLobject.h"

#include "_DEBUG_OBJECT.hpp"

namespace vnaon_scenes {

	scenes_engine::scenes_engine() {
		_last_engine_time = clock::now();
		_fps = 0.0;
		_p_glcontroller = nullptr;
		_p_skybox_program = nullptr;
		_p_skybox = nullptr;
		_p_skybox_arr = nullptr;
		_degfov = 45;
		_aspect = 1;

		_init();
	}

	scenes_engine::~scenes_engine() {
		if ( _p_glcontroller != nullptr ) delete _p_glcontroller;
	}

	void scenes_engine::draw() {

		if ( _p_glcontroller == nullptr ) return;
		_clac_fps();

		_p_glcontroller->set_clean_color(vnaon_gl::GLcolor("#505050"));
		_p_glcontroller->clear();

		if ( _p_skybox != nullptr && _p_skybox_program != nullptr ) {
			_p_glcontroller->use_program(_p_skybox_program);
			_p_glcontroller->bind_vertex_array(_p_skybox_arr);
			_p_glcontroller->bind_skybox_object(_p_skybox);
			glm::mat4 view(1.0);
			glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float) _aspect, 0.1f, 100.0f);
			glUniformMatrix4fv(_p_skybox_program->_unifors_info["mat4_proj_view"].location, 1, GL_FALSE, glm::value_ptr(proj * view));
			_p_glcontroller->draw_array(GL_TRIANGLES, 0, 36);
		} else {
			_init_gl_resource();
		}

	}

	void scenes_engine::adjust_viewport(const int &arg_width, const int &arg_height) {
		if ( arg_height > 0 ) {
			_aspect = (double) (arg_width / arg_height);
			_p_glcontroller->adjust_viewport(arg_width, arg_height);
		}
	}

	void scenes_engine::_init() {
		_p_glcontroller = new vnaon_gl::GLcontroller();

		// camera init
		_pos = glm::vec3(1, 1, 1);
		_dir = glm::vec3(-1, -1, -1);
		_dir = glm::normalize(_dir);
		_ahd = glm::vec3(0, 0, 1);
		_ahd = _ahd - glm::dot(_ahd, _dir) * _dir;
		_ahd = glm::normalize(_ahd);
		_near = 0.1;
		_far = 10.0;
		_init_camera();
		

	}

	bool scenes_engine::_init_gl_resource() {
		_p_skybox_program = _p_glcontroller->create_shader_program("SKY_SHADER");
		_p_skybox_program->attach_vertex_shader_from_file(R"(glsl\skybox.vs)");
		_p_skybox_program->attach_fragment_shader_from_file(R"(glsl\skybox.fs)");
		_p_glcontroller->compile_program(_p_skybox_program);

		std::vector<std::string> img_file;
		img_file.push_back(R"(image\right.jpg)");
		img_file.push_back(R"(image\left.jpg)");
		img_file.push_back(R"(image\top.jpg)");
		img_file.push_back(R"(image\bottom.jpg)");
		img_file.push_back(R"(image\back.jpg)");
		img_file.push_back(R"(image\front.jpg)");
		_p_skybox = _p_glcontroller->create_skybox_from_file(img_file);

		_p_skybox_arr = _p_glcontroller->create_vertex_array();
		float skyboxVertices[] = {
			// positions          
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};
		auto buf = _p_glcontroller->create_vertex_buffer(GL_STATIC_DRAW, skyboxVertices, 108 * sizeof(float));
		_p_glcontroller->init_vertex_array(_p_skybox_arr,
			vnaon_gl::GLcontroller::attribute_information{
				{buf, 0, 3, GL_FLOAT, GL_FALSE, 0, 0 }
			}
		);
		return true;
	}

	void scenes_engine::_init_camera() {
		_camera.set_camera(_pos, _dir, _ahd);
		_camera.set_perspective(_degfov, _aspect, _near, _far);
	}

	void scenes_engine::_clac_fps() {
		using namespace std;
		using namespace std::chrono;
		clock::time_point nowTimePoint = clock::now();
		double timeLag = duration<double, milli>(nowTimePoint - _last_engine_time).count();
		_last_engine_time = nowTimePoint;

		_fps = 1000.0 / timeLag;

		//DEBUGConsole::log({ _fps });
	}

}