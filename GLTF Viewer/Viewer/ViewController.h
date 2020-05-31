#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ViewEngine.h"

namespace vNaonScenes {

	class CViewContorller {
	protected:
		CViewEngine *pViewEngine;

	public:
		CViewContorller();
		~CViewContorller();

		//Main function.
		bool Render();

		void close();

	public:
		void resizeViewer(const int &w, const int &h);

	};

}