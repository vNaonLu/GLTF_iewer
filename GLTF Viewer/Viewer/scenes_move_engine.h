#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <memory>
#include <vector>
#include <map>


namespace vnaon_scenes {


	class scenes_move_engine {

	private:
		typedef enum{ PANNING } MOVING_TYPE;
		glm::vec3 _pos;

		class move_function {
		public:
			move_function();
			~move_function();
			void moving(glm::vec3 &arg_out, double arg_tick_count, glm::vec2 arg_parm);
			virtual void begin(double arg_tick_count, glm::vec2 arg_parm);
			virtual void stop();
		protected:
			virtual void do_moving(glm::vec3 &arg_out);
			virtual void adjust_param(double arg_tick_count, glm::vec2 arg_parm);
		};
		typedef std::shared_ptr<move_function> p_moving;

		class move_pannig : public move_function{
		private:
			bool _mouse_down;
			double _vert_speed; // rps
			double _hori_speed;
			glm::vec2 _history_pos;
		public:
			move_pannig();
			~move_pannig();
			virtual void begin(double arg_tick_count, glm::vec2 arg_parm) override;
			virtual void stop() override;
		protected:
			void _clear();
			virtual void do_moving(glm::vec3 &arg_out) override;
			virtual void adjust_param(double arg_tick_count, glm::vec2 arg_parm) override;
		};

		std::map<MOVING_TYPE, p_moving> _moving_function;

	public:
		scenes_move_engine();
		~scenes_move_engine();

		glm::vec3 get_pos() const;

		void do_moving(double arg_tick_count, glm::vec2 arg_parm);

		void stop();

		void left_mouse_down(double arg_tick_count, glm::vec2 arg_parm);
		void left_mouse_up();

	};

}
