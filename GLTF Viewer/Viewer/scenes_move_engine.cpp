#include "scenes_move_engine.h"


#include "_DEBUG_OBJECT.hpp"


namespace vnaon_scenes {

	scenes_move_engine::scenes_move_engine() {
		_pos = glm::vec3(1, sin(glm::radians(30.0f)), 1);
		_moving_function[PANNING] = std::make_shared<move_pannig>();
	}

	scenes_move_engine::~scenes_move_engine() {
	}

	glm::vec3 scenes_move_engine::get_pos() const {
		return _pos;
	}

	void scenes_move_engine::do_moving(double arg_tick_count, glm::vec2 arg_parm) {
		for ( auto func : _moving_function ) {
			func.second->moving(_pos, arg_tick_count, arg_parm);
		}
	}

	void scenes_move_engine::stop() {
		_moving_function.clear();
	}

	void scenes_move_engine::left_mouse_down(double arg_tick_count, glm::vec2 arg_parm) {
		_moving_function[PANNING]->begin(arg_tick_count, arg_parm);
	}

	void scenes_move_engine::left_mouse_up() {
		_moving_function[PANNING]->stop();
	}


	//===
	scenes_move_engine::move_function::move_function() {
	}

	scenes_move_engine::move_function::~move_function() {
	}

	void scenes_move_engine::move_function::moving(glm::vec3 &arg_out, double arg_tick_count, glm::vec2 arg_parm) {
		adjust_param(arg_tick_count, arg_parm);
		do_moving(arg_out);
	}

	void scenes_move_engine::move_function::begin(double arg_tick_count, glm::vec2 arg_parm) {
	}

	void scenes_move_engine::move_function::stop() {
	}

	void scenes_move_engine::move_function::do_moving(glm::vec3 &arg_out) {
	}

	void scenes_move_engine::move_function::adjust_param(double arg_tick_count, glm::vec2 arg_parm) {
	}
	

	//===
	scenes_move_engine::move_pannig::move_pannig() : move_function() {
		_clear();
	}

	scenes_move_engine::move_pannig::~move_pannig() {
	}

	void scenes_move_engine::move_pannig::begin(double arg_tick_count, glm::vec2 arg_parm) {
		_clear();
		_mouse_down = true;
		_history_pos = arg_parm;
	}

	void scenes_move_engine::move_pannig::stop() {
		_mouse_down = false;
	}

	void scenes_move_engine::move_pannig::_clear() {
		_mouse_down = false;
		_vert_speed = 0;
		_hori_speed = 0;
		_history_pos = glm::vec2(0.0);
	}

	void scenes_move_engine::move_pannig::do_moving(glm::vec3 &arg_out) {
		if ( _hori_speed != 0 ) { 
			glm::dmat4 rot = glm::rotate(glm::dmat4(1.0), _hori_speed, glm::dvec3(0.0, 1.0, 0.0));
			arg_out = rot * glm::dvec4(arg_out, 1.0);
		}
		if ( _vert_speed != 0 ) {
			glm::dmat4 rot = glm::rotate(glm::dmat4(1.0), _vert_speed, glm::dvec3(1.0, 0.0, 0.0));
			arg_out = rot * glm::dvec4(arg_out, 1.0);
		}
	}

	void scenes_move_engine::move_pannig::adjust_param(double arg_tick_count, glm::vec2 arg_parm) {

		if ( _mouse_down && arg_tick_count > 0 ) {

			auto x_difference = arg_parm.x - _history_pos.x;
			auto y_difference = arg_parm.y - _history_pos.y;

			_hori_speed = x_difference * 90.0 / arg_tick_count;
			_vert_speed = y_difference * 90.0 / arg_tick_count;

			_history_pos = arg_parm;
		}
	}

}