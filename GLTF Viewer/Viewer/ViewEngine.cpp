#include "ViewEngine.h"

#include "_DEBUG_OBJECT.hpp"

namespace vnaon_scenes {

	CViewEngine::CViewEngine() {
		mLastEngineTime = std::chrono::steady_clock::now();
		mFPS = 0.0;
		pDevice = nullptr;

		initialize();
	}

	CViewEngine::~CViewEngine() {
		if ( pDevice != nullptr ) delete pDevice;
	}

	void CViewEngine::Draw() {

		if ( pDevice == nullptr ) return;
		calculateFPS();

		pDevice->setClearColorBuffer(vNaonGL::GLcolor("#000000"));
		pDevice->clear();

	}

	void CViewEngine::resizeViewer(const int &w, const int &h) {
		pDevice->resizeViewport(w, h);
	}

	void CViewEngine::initialize() {
		pDevice = new vNaonGL::GLdevice();
	}

	void CViewEngine::calculateFPS() {
		using namespace std;
		using namespace std::chrono;
		SteadyTime nowTimePoint = steady_clock::now();
		double timeLag = duration<double, milli>(nowTimePoint - mLastEngineTime).count();		
		mLastEngineTime = nowTimePoint;

		mFPS = 1000.0 / timeLag;

		//DEBUGConsole::log({ mFPS });
	}

}