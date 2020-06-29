#include "scenes_move_engine.h"


#include "debug_tools.hpp"


namespace vnaon_scenes {

	MovingEngine::MovingEngine() {
		_pos = glm::vec3(1, sin(glm::radians(30.0f)), 1);
		_moving_entity[PANNING] = std::make_shared<MovingPanning>();
	}

	MovingEngine::~MovingEngine() {
	}

	glm::vec3 MovingEngine::GetPosition() const {
		return _pos;
	}

	void MovingEngine::DoMoving(double arg_tick_count, glm::vec2 arg_parm) {
		for ( auto func : _moving_entity ) {
			func.second->Moving(_pos, arg_tick_count, arg_parm);
		}
	}

	void MovingEngine::Stop() {
		_moving_entity.clear();
	}

	void MovingEngine::LeftMouseDown(double arg_tick_count, glm::vec2 arg_parm) {
		_moving_entity[PANNING]->Begin(arg_tick_count, arg_parm);
	}

	void MovingEngine::LeftMouseUp() {
		_moving_entity[PANNING]->Stop();
	}


	//===
	MovingEngine::MovingEntity::MovingEntity() {
	}

	MovingEngine::MovingEntity::~MovingEntity() {
	}

	void MovingEngine::MovingEntity::Moving(glm::vec3 &arg_out, double arg_tick_count, glm::vec2 arg_parm) {
		AdjustParameter(arg_tick_count, arg_parm);
		DoMoving(arg_out);
	}

	void MovingEngine::MovingEntity::Begin(double arg_tick_count, glm::vec2 arg_parm) {
	}

	void MovingEngine::MovingEntity::Stop() {
	}

	void MovingEngine::MovingEntity::DoMoving(glm::vec3 &arg_out) {
	}

	void MovingEngine::MovingEntity::AdjustParameter(double arg_tick_count, glm::vec2 arg_parm) {
	}
	

	//===
	const double MovingEngine::MovingPanning::DIF_PER_MILLI = 0.25 / 1000.0;
	MovingEngine::MovingPanning::MovingPanning() : MovingEntity() {
		Clear();
	}

	MovingEngine::MovingPanning::~MovingPanning() {
	}

	void MovingEngine::MovingPanning::Begin(double arg_tick_count, glm::vec2 arg_parm) {
		Clear();
		_mouse_down = true;
		_history_pos = arg_parm;
	}

	void MovingEngine::MovingPanning::Stop() {
		_mouse_down = false;
	}

	void MovingEngine::MovingPanning::Clear() {
		_mouse_down = false;
		_vert_speed = 0;
		_hori_speed = 0;
		_history_pos = glm::vec2(0.0);
	}

	void MovingEngine::MovingPanning::DoPhysical(double &arg_angle, double arg_tick_count) {
		if ( arg_angle > 0 ) {
			arg_angle -= DIF_PER_MILLI * arg_tick_count;
			if ( arg_angle < 0 ) arg_angle = 0;
		} else {
			arg_angle += DIF_PER_MILLI * arg_tick_count;
			if ( arg_angle > 0 ) arg_angle = 0;
		}
	}

	void MovingEngine::MovingPanning::DoMoving(glm::vec3 &arg_out) {
		if ( _hori_speed != 0 ) { 
			glm::dmat4 rot = glm::rotate(glm::dmat4(1.0), _hori_speed, glm::dvec3(0.0, 1.0, 0.0));
			arg_out = rot * glm::dvec4(arg_out, 1.0);
		}
		if ( _vert_speed != 0 ) {
			glm::dmat4 rot = glm::rotate(glm::dmat4(1.0), _vert_speed, glm::dvec3(1.0, 0.0, 0.0));
			arg_out = rot * glm::dvec4(arg_out, 1.0);
		}
	}

	void MovingEngine::MovingPanning::AdjustParameter(double arg_tick_count, glm::vec2 arg_parm) {

		if ( _mouse_down && arg_tick_count > 0 ) {

			auto x_difference = arg_parm.x - _history_pos.x;
			auto y_difference = arg_parm.y - _history_pos.y;

			_hori_speed = x_difference * 90.0 / arg_tick_count;
			_vert_speed = y_difference * 90.0 / arg_tick_count;

			_history_pos = arg_parm;
		} else {
			if ( _hori_speed != 0 )
				DoPhysical(_hori_speed, arg_tick_count);
			if ( _vert_speed != 0 )
				DoPhysical(_vert_speed, arg_tick_count);
		}

	}

}