#include "scenes_engine.h"
#include "GLprogram.h"
#include "GLobject.h"
#include "scenes_skybox.h"



#include "_DEBUG_OBJECT.hpp"



namespace vnaon_scenes {

	scenes_engine::scenes_engine() {
		_p_glcontroller = nullptr;
		_near = 0.1;
		_far = 10.0;

		_first_render = true;
		entities.clear();

		_init();
	}

	scenes_engine::~scenes_engine() {
		if ( _p_glcontroller != nullptr ) delete _p_glcontroller;
	}

	void scenes_engine::draw(glm::ivec2 arg_viewport, glm::vec3 arg_frustum_pos) {
		_set_camera(arg_viewport, arg_frustum_pos, _near, _far);

		if ( _p_glcontroller == nullptr ) return;

		if ( _first_render ) {
			_first_render = false;
			_init_render();
		}

		_p_glcontroller->adjust_viewport(arg_viewport.x, arg_viewport.y);
		_p_glcontroller->set_clean_color(vnaon_gl::GLcolor("#505050"));
		_p_glcontroller->clear();

		for ( auto entity : entities ) {
			entity->draw_scenes(_p_glcontroller, _camera);
		}

	}

	void scenes_engine::_init() {
		_p_glcontroller = new vnaon_gl::GLcontroller();

		entities.push_back(scenes_skybox::create());
	}

	void scenes_engine::_set_camera(glm::ivec2 arg_viewport, glm::vec3 arg_pos, double arg_near, double arg_far){
		if ( arg_viewport.y > 0 ) {
			_camera.set_camera(arg_pos);
			_camera.set_perspective(45.0, (double) arg_viewport.x / (double) arg_viewport.y, arg_near, arg_far);
		}
	}

	void scenes_engine::_init_render() {
		for ( auto entity : entities )
			entity->init(_p_glcontroller);
	}

}