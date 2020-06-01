#include "ViewController.h"

namespace vnaon_scenes {

	view_controller::view_controller() {
		pViewEngine = new CViewEngine();
	}

	view_controller::~view_controller() {
	}

	bool view_controller::Render() {
		pViewEngine->Draw();
		return true;
	}

	void view_controller::close() {
		if ( pViewEngine != nullptr ) delete pViewEngine;
	}

	void view_controller::resizeViewer(const int &w, const int &h) {
		pViewEngine->resizeViewer(w, h);
	}

}