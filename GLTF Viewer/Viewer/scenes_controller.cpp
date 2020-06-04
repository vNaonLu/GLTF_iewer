#include "scenes_controller.h"

namespace vnaon_scenes {

	view_controller::view_controller() {
		pViewEngine = new scenes_engine();
	}

	view_controller::~view_controller() {
	}

	bool view_controller::render() {
		pViewEngine->draw();
		return true;
	}

	void view_controller::close() {
		if ( pViewEngine != nullptr ) delete pViewEngine;
	}

	void view_controller::adjust_viewer(const int &w, const int &h) {
		pViewEngine->adjust_viewport(w, h);
	}

}