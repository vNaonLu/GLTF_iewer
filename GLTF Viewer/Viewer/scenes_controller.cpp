#include "scenes_controller.h"


#include "_DEBUG_OBJECT.hpp"


namespace vnaon_scenes {

	view_controller::view_controller(int arg_x, int arg_y) {
		this->_p_scenes_engine = new scenes_engine();
		this->_p_move_engine = new scenes_move_engine();
		this->_last_engine_time = clock::now();
		this->_last_tick_count = 0.0;
		this->_fps = 0;
		this->_mouse_pos = glm::vec2(0.5, 0.5);
		this->_viewport = glm::vec2(arg_x, arg_y);
	}

	view_controller::~view_controller() {
	}

	bool view_controller::render() {
		_calc_frame_per_second();
		_p_move_engine->do_moving(_last_tick_count, _mouse_pos);
		_p_scenes_engine->draw(_viewport, _p_move_engine->get_pos());
		return true;
	}

	void view_controller::close() {
		if ( _p_scenes_engine != nullptr ) delete _p_scenes_engine;
		if ( _p_move_engine != nullptr ) delete _p_move_engine;
	}

	void view_controller::adjust_viewer(const int &w, const int &h) {
		if ( h > 0 ) {
			_viewport = glm::vec2(w, h);
			_p_scenes_engine->adjust_viewport(w, h);
		}
	}

	void view_controller::on_mouse_move(int arg_x, int arg_y) {
		_mouse_pos = glm::vec2((float) arg_x / _viewport.x - 1.0f, (float) arg_y / _viewport.y - 1.0f);
	}

	void view_controller::on_left_mouse_down(int arg_x, int arg_y) {
		_p_move_engine->left_mouse_down(_last_tick_count, _mouse_pos);
	}

	void view_controller::on_left_mouse_up(int arg_x, int arg_y) {
		_p_move_engine->left_mouse_up();
	}

	double view_controller::_calc_frame_per_second() {
		using namespace std;
		using namespace std::chrono;
		clock::time_point nowTimePoint = clock::now();
		_last_tick_count = duration<double, milli>(nowTimePoint - _last_engine_time).count();
		_last_engine_time = nowTimePoint;
		_fps = 1000.0 / _last_tick_count;
		DEBUGConsole::log("FPS: " + std::to_string(_fps));
		return _last_tick_count;
	}

}