#include "scenes_controller.h"


#include "debug_tools.hpp"


namespace vnaon_scenes {

	ScenesViewController::ScenesViewController(int arg_x, int arg_y) {
		this->_p_scenes_engine = new ScenesEngine();
		this->_p_move_engine = new MovingEngine();
		this->_last_engine_time = clock::now();
		this->_last_tick_count = 0.0;
		this->_fps = 0;
		this->_mouse_pos = glm::vec2(0.5, 0.5);
		this->_viewport = glm::vec2(arg_x, arg_y);
	}

	ScenesViewController::~ScenesViewController() {
	}

	bool ScenesViewController::Render() {
		CalculateFps();
		_p_move_engine->DoMoving(_last_tick_count, _mouse_pos);
		_p_scenes_engine->Draw(_viewport, _p_move_engine->GetPosition());
		return true;
	}

	void ScenesViewController::Close() {
		if ( _p_scenes_engine != nullptr ) delete _p_scenes_engine;
		if ( _p_move_engine != nullptr ) delete _p_move_engine;
	}

	void ScenesViewController::OnViewportChange(const int &w, const int &h) {
		if ( h > 0 ) {
			_viewport = glm::vec2(w, h);
		}
	}

	void ScenesViewController::OnMouseMove(int arg_x, int arg_y) {
		_mouse_pos = glm::vec2((float) arg_x / _viewport.x - 1.0f, (float) arg_y / _viewport.y - 1.0f);
	}

	void ScenesViewController::OnLeftMouseDown(int arg_x, int arg_y) {
		_p_move_engine->LeftMouseDown(_last_tick_count, _mouse_pos);
	}

	void ScenesViewController::OnLeftMouseUp(int arg_x, int arg_y) {
		_p_move_engine->LeftMouseUp();
	}

	double ScenesViewController::CalculateFps() {
		using namespace std;
		using namespace std::chrono;
		clock::time_point nowTimePoint = clock::now();
		_last_tick_count = duration<double, milli>(nowTimePoint - _last_engine_time).count();
		_last_engine_time = nowTimePoint;
		_fps = 1000.0 / _last_tick_count;
		_DebugTools_::Log("FPS: " + std::to_string(_fps));
		return _last_tick_count;
	}

}