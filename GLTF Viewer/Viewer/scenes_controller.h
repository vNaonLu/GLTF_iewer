#pragma once
#include <glad/glad.h>



#include "scenes_engine.h"
#include "scenes_move_engine.h"



namespace vnaon_scenes {

	class ScenesViewController {
	protected:
		typedef std::chrono::system_clock clock;
		clock::time_point _last_engine_time;
		ScenesEngine *_p_scenes_engine;
		MovingEngine *_p_move_engine;
		glm::vec2 _viewport;
		glm::vec2 _mouse_pos;
		double _fps;
		double _last_tick_count;

	public:
		ScenesViewController(int arg_x, int arg_y);
		~ScenesViewController();

		//Main function.
		bool Render();

		void Close();

	public:
		void OnViewportChange(const int &w, const int &h);

		void OnMouseMove(int arg_x, int arg_y);

		void OnLeftMouseDown(int arg_x, int arg_y);

		void OnLeftMouseUp(int arg_x, int arg_y);

	private:
		/// <summary>
		/// Calculates the frame per second.
		/// </summary>
		/// <returns>a tickcount in this frame</returns>
		double CalculateFps();

	};

}