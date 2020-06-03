#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ViewEngine.h"

namespace vnaon_scenes {

	class view_controller {
	protected:
		CViewEngine *pViewEngine;

	public:
		view_controller();
		~view_controller();

		//Main function.
		bool render();

		void close();

	public:
		void adjust_viewer(const int &w, const int &h);

	};

}