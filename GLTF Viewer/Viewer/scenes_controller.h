#pragma once
#include <glad/glad.h>



#include "scenes_engine.h"
#include "scenes_move_engine.h"



namespace vnaon_scenes {

	class view_controller {
	protected:
		typedef std::chrono::system_clock clock;
		clock::time_point _last_engine_time;
		scenes_engine *_p_scenes_engine;
		scenes_move_engine *_p_move_engine;
		glm::vec2 _viewport;
		glm::vec2 _mouse_pos;
		double _fps;
		double _last_tick_count;

	public:
		view_controller(int arg_x, int arg_y);
		~view_controller();

		//Main function.
		bool render();

		void close();

	public:
		void on_viewport_change(const int &w, const int &h);

		void on_mouse_move(int arg_x, int arg_y);

		void on_left_mouse_down(int arg_x, int arg_y);

		void on_left_mouse_up(int arg_x, int arg_y);

	private:
		/// <summary>
		/// Calculates the frame per second.
		/// </summary>
		/// <returns>a tickcount in this frame</returns>
		double _calc_frame_per_second();

	};

}