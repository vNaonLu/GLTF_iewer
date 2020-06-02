#pragma once
#include <chrono>

#include "GLcontroller.h"

namespace vnaon_scenes {

	/*
	An engine used to control and manage render.
	 */
	class CViewEngine {

	private:
		typedef std::chrono::steady_clock::time_point SteadyTime;
		SteadyTime mLastEngineTime;
		double mFPS;

		vnaon_gl::GLcontroller *pDevice;		

	public:
		CViewEngine();
		~CViewEngine();

		//Main Function.
		void Draw();

		double getFramePerSecond() const;

		void resizeViewer(const int &w, const int &h);

	protected:
		void initialize();

		void calculateFPS();

	};

}