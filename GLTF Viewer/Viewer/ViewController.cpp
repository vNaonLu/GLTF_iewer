#include "ViewController.h"

namespace vNaonScenes {

	CViewContorller::CViewContorller() {
		pViewEngine = new CViewEngine();
	}

	CViewContorller::~CViewContorller() {
	}

	bool CViewContorller::Render() {
		pViewEngine->Draw();
		return true;
	}

	void CViewContorller::close() {
		if ( pViewEngine != nullptr ) delete pViewEngine;
	}

	void CViewContorller::resizeViewer(const int &w, const int &h) {
		pViewEngine->resizeViewer(w, h);
	}

}