#include "scenes_controller.h"


#include "_DEBUG_OBJECT.hpp"


namespace vnaon_scenes {

	view_controller::view_controller() {
		_last_engine_time = clock::now();
		p_scenes_engine = new scenes_engine();
		p_move_engine = new scenes_move_engine();
		_fps = 0;
		mouse_pos = glm::vec2(0.5, 0.5);
		viewport = glm::vec2(1280, 1080);
	}

	view_controller::~view_controller() {
	}

	bool view_controller::render() {
		_calc_frame_per_second();
		p_move_engine->do_moving(_last_tick_count, mouse_pos);
		p_scenes_engine->draw(viewport, p_move_engine->get_pos());
		return true;
	}

	void view_controller::close() {
		if ( p_scenes_engine != nullptr ) delete p_scenes_engine;
		if ( p_move_engine != nullptr ) delete p_move_engine;
	}

	void view_controller::adjust_viewer(const int &w, const int &h) {
		if ( h > 0 ) {
			viewport = glm::vec2(w, h);
			p_scenes_engine->adjust_viewport(w, h);
		}
	}

	void view_controller::on_mouse_move(int arg_x, int arg_y) {
		mouse_pos = glm::vec2((float) arg_x / viewport.x - 1.0f, (float) arg_y / viewport.y - 1.0f);
		DEBUGConsole::log("Mouse down: (x:" + std::to_string(mouse_pos.x) + ", y:" + std::to_string(mouse_pos.y) + ")");
	}

	void view_controller::on_left_mouse_down(int arg_x, int arg_y) {
		p_move_engine->left_mouse_down(_last_tick_count, mouse_pos);
	}

	void view_controller::on_left_mouse_up(int arg_x, int arg_y) {
		p_move_engine->left_mouse_up();
	}

	double view_controller::_calc_frame_per_second() {
		using namespace std;
		using namespace std::chrono;
		clock::time_point nowTimePoint = clock::now();
		_last_tick_count = duration<double, milli>(nowTimePoint - _last_engine_time).count();
		_last_engine_time = nowTimePoint;
		_fps = 1000.0 / _last_tick_count;
		return _last_tick_count;
	}

}