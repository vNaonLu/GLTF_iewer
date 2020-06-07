#include "scenes_controller.h"

namespace vnaon_scenes {

	view_controller::view_controller() {
		p_scenes_engine = new scenes_engine();
	}

	view_controller::~view_controller() {
	}

	bool view_controller::render() {
		p_scenes_engine->draw();
		return true;
	}

	void view_controller::close() {
		if ( p_scenes_engine != nullptr ) delete p_scenes_engine;
	}

	void view_controller::adjust_viewer(const int &w, const int &h) {
		p_scenes_engine->adjust_viewport(w, h);
	}

}