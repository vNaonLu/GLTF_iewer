#pragma once
#include <vector>
#include <memory>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <thread>
#include <functional>

namespace vnaon_common {

	/*
	 * An interface class of task.
	 * Used for delivering and excutint in thread loop.
	 */
	class InteraceEvent{
	private:
		bool _abort;
	public:
		InteraceEvent();
		~InteraceEvent();
		void excute();
		void Expire();
	protected:
		virtual void Process();
	};
	typedef std::shared_ptr<InteraceEvent> InteraceEvent_p;

	/*
	 * A generic task for main thread.
	 */
	template<class T>
	class GenericEvent : public InteraceEvent {
	public:
		typedef std::function<void(T)> EventProccessor;
	private:
		T _task;
		EventProccessor _process;
	public:
		static InteraceEvent_p Create(T arg_task, EventProccessor ard_proc) {
			return std::make_shared<GenericEvent<T>>(arg_task, ard_proc);
		}
		GenericEvent(T arg_task, EventProccessor ard_proc){
			_task = arg_task;
			_process = ard_proc;
		}
		~GenericEvent() {
		}
	protected:
		virtual void Process() override {
			_process(_task);
		}
	};

	/*
	 * An interface class of thread context.
	 * Used for excuting the mission in several thread.
	 */
	class EventContext {	
	private:
		bool _abort;
		std::mutex _mutex_event_task;
		std::queue<InteraceEvent_p> _arr_event_task;
		std::mutex _mutex_cond_var;
		std::condition_variable _cond_var;
	protected:
		std::thread *context_thread_p;
	public:
		EventContext();
		~EventContext();
		bool IsValid() const;
		void PushEvent(InteraceEvent_p command);
		void Expire();
	protected:
		bool IdleIfNeed();
		InteraceEvent_p PopEvent();
		virtual void Process();	
	};

}