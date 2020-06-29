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


	class MovingEngine {

	private:
		typedef enum{ PANNING } MOVING_TYPE;
		glm::vec3 _pos;

		class MovingEntity {
		public:
			MovingEntity();
			~MovingEntity();
			void Moving(glm::vec3 &arg_out, double arg_tick_count, glm::vec2 arg_parm);
			virtual void Begin(double arg_tick_count, glm::vec2 arg_parm);
			virtual void Stop();
		protected:
			virtual void DoMoving(glm::vec3 &arg_out);
			virtual void AdjustParameter(double arg_tick_count, glm::vec2 arg_parm);
		};
		typedef std::shared_ptr<MovingEntity> MovingEntity_p;

		class MovingPanning : public MovingEntity{
		private:
			static const double DIF_PER_MILLI;
			bool _mouse_down;
			double _vert_speed; // rps
			double _hori_speed;
			glm::vec2 _history_pos;
		public:
			MovingPanning();
			~MovingPanning();
			virtual void Begin(double arg_tick_count, glm::vec2 arg_parm) override;
			virtual void Stop() override;
		protected:
			void Clear();
			void DoPhysical(double &arg_angle, double arg_tick_count);
			virtual void DoMoving(glm::vec3 &arg_out) override;
			virtual void AdjustParameter(double arg_tick_count, glm::vec2 arg_parm) override;
		};


		std::map<MOVING_TYPE, MovingEntity_p> _moving_entity;

	public:
		MovingEngine();
		~MovingEngine();

		glm::vec3 GetPosition() const;

		void DoMoving(double arg_tick_count, glm::vec2 arg_parm);

		void Stop();

		void LeftMouseDown(double arg_tick_count, glm::vec2 arg_parm);
		void LeftMouseUp();

	};

}
