#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ViewContext.h"
#include "Rect.h"

namespace vNaonScenes {

	CViewContorller *CRenderContext::pController = nullptr;
	CRenderContext::CRenderContext(const std::string &windowsName, const double &width, const double &height) {

		pWindow = nullptr;
		mWindowName = windowsName;
		mViewPort.right = width;
		mViewPort.bottom = height;

	}

	CRenderContext::~CRenderContext() {
		terminate();

		if ( CRenderContext::pController != nullptr ) {
			CRenderContext::pController->close();
			delete  CRenderContext::pController;
		}

	}

	void CRenderContext::render() {

		mRenderConditionVariable.notify_one();

		if ( !initialize() ) return;

		setSwapInterval(1);

		while ( isAlive() ) {

			CRenderContext::pController->Render();

			swapBuffer();
		}

	}

	bool CRenderContext::createWindow() {
		using namespace vNaonGeometry;

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		int width = (int) Rect::width(mViewPort);
		int height = (int) Rect::height(mViewPort);
		pWindow = glfwCreateWindow(width, height, mWindowName.c_str(), nullptr, nullptr);

		if ( pWindow == nullptr )
			return false;
		else
			return true;

	}

	bool CRenderContext::initializeWindow() {
		if ( pWindow == nullptr )
			return false;

		glfwMakeContextCurrent(pWindow);

		if ( !gladLoadGLLoader((GLADloadproc) glfwGetProcAddress) )
			return false;

		return true;
	}

	bool CRenderContext::isAlive() const {
		return  !glfwWindowShouldClose(pWindow);
	}

	void CRenderContext::swapBuffer() {
		glfwSwapBuffers(pWindow);
		glfwPollEvents();
	}

	void CRenderContext::setSwapInterval(int interval) {
		glfwSwapInterval(interval);
	}

	void CRenderContext::terminate() {
		glfwTerminate();
		if ( pWindow != nullptr ) glfwDestroyWindow(pWindow);
	}

	bool CRenderContext::initialize() {
		CRenderContext::pController = new vNaonScenes::CViewContorller();

		createWindow();

		initializeWindow();

		bool ret = true;
		return ret;
	}

	void CRenderContext::attachEvent() {
		glfwSetFramebufferSizeCallback(pWindow, onResizeWindow);
	}

	void CRenderContext::process() {

		while ( stopProcessIfNeed() ) {
		}
	}

	void CRenderContext::onResizeWindow(GLFWwindow *window, int width, int height) {
		CRenderContext::pController->resizeViewer(width, height);
	}

}