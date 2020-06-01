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
	class _i_event_task{
	private:
		bool _abort;
	public:
		_i_event_task();
		~_i_event_task();
		void excute();
		void abort();
	protected:
		virtual void process();
	};
	typedef std::shared_ptr<_i_event_task> event_task_p;

	/*
	 * A generic task for main thread.
	 */
	template<class T>
	class generic_event_task : public _i_event_task {
	public:
		typedef std::function<void(T)> task_process;
	private:
		T _task;
		task_process _process;
	public:
		static event_task_p create(T arg_task, task_process ard_proc) {
			return std::make_shared<generic_event_task<T>>(arg_task, ard_proc);
		}
		generic_event_task(T arg_task, task_process ard_proc){
			_task = arg_task;
			_process = ard_proc;
		}
		~generic_event_task() {
		}
	protected:
		virtual void process() override {
			_process(_task);
		}
	};

	/*
	 * An interface class of thread context.
	 * Used for excuting the mission in several thread.
	 */
	class _i_event_context {	
	private:
		bool _abort;
		std::mutex _mutex_event_task;
		std::queue<event_task_p> _arr_event_task;
		std::mutex _mutex_cond_var;
		std::condition_variable _cond_var;
	protected:
		std::thread *context_thread_p;
	public:
		_i_event_context();
		~_i_event_context();
		void push(event_task_p command);
	protected:
		void abort();
		bool stop_if_need();
		event_task_p pop();
		virtual void process();	
	};

}