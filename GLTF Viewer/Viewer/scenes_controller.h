#pragma once
#include <glad/glad.h>
#include "scenes_engine.h"

namespace vnaon_scenes {

	class view_controller {
	protected:
		scenes_engine *p_scenes_engine;

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