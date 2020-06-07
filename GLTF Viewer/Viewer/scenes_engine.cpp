#include "scenes_engine.h"
#include "GLprogram.h"
#include "GLobject.h"
#include "scenes_skybox.h"



#include "_DEBUG_OBJECT.hpp"



namespace vnaon_scenes {

	scenes_engine::scenes_engine() {
		_last_engine_time = clock::now();
		_fps = 0.0;
		_p_glcontroller = nullptr;
		_degfov = 45;
		_aspect = 1;

		_first_render = true;
		entities.clear();

		_init();
	}

	scenes_engine::~scenes_engine() {
		if ( _p_glcontroller != nullptr ) delete _p_glcontroller;
	}

	void scenes_engine::draw() {

		if ( _p_glcontroller == nullptr ) return;
		_clac_fps();

		if ( _first_render ) _init_render();

		_p_glcontroller->set_clean_color(vnaon_gl::GLcolor("#505050"));
		_p_glcontroller->clear();

		for ( auto entity : entities ) {
			entity->draw_scenes(_p_glcontroller, _camera);
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
		_pos = glm::vec3(1, std::sin(glm::radians(30.0f)), 1);
		_near = 0.1;
		_far = 10.0;
		_init_camera();

		entities.push_back(scenes_skybox::create());
	}

	void scenes_engine::_init_camera() {
		_camera.set_camera(_pos);
		_camera.set_perspective(_degfov, _aspect, _near, _far);
	}

	void scenes_engine::_init_render() {
		for ( auto entity : entities )
			entity->init(_p_glcontroller);
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