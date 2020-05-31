#pragma once
#include <vector>
#include <string>

#include "Rect.h"
#include "ViewController.h"
#include "EventContext.h"

namespace vNaonScenes {

	class CRenderContext : public vNaonCommon::CEventContext {
	public:
		static CViewContorller *pController;

	private:
		GLFWwindow *pWindow;
		std::string mWindowName;

		std::mutex mRenderMutex;
		std::condition_variable mRenderConditionVariable;
		vNaonGeometry::Rect mViewPort;

	public:
		CRenderContext( const std::string &windowsName, const double &width, const double &height);
		~CRenderContext();

		void render();

	private:
		bool createWindow();

		bool initializeWindow();

		bool isAlive() const;

		void swapBuffer();

		void setSwapInterval(int interval);

		void terminate();

		bool initialize();

		void attachEvent();

		virtual void process() override;

	public:
		// event
		static void onResizeWindow(GLFWwindow *window, int width, int height);

	};

}