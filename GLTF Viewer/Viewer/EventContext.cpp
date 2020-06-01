#include "EventContext.h"

namespace vnaon_common {
	// ---
	_i_event_task::_i_event_task() {
		_abort = false;
	}
	_i_event_task::~_i_event_task() {
	}
	void _i_event_task::excute() {
		if ( !_abort ) process();
	}
	void _i_event_task::abort() {
		_abort = true;
	}
	void _i_event_task::process() {
	}

	// ---
	_i_event_context::_i_event_context() {
		_abort = false;
		context_thread_p = new std::thread (&_i_event_context::process, this);
	}
	_i_event_context::~_i_event_context() {
		abort();
		context_thread_p->join();
		delete context_thread_p;
	}
	void _i_event_context::push(event_task_p command) {
		if ( command == nullptr ) return;

		_mutex_event_task.lock();
		_arr_event_task.push(command);
		_mutex_event_task.unlock();

		_cond_var.notify_one();
	}
	void _i_event_context::abort() {
		_abort = true;
		_cond_var.notify_one();
	}
	bool _i_event_context::stop_if_need() {
		_mutex_event_task.lock();
		bool empty = _arr_event_task.empty();
		_mutex_event_task.unlock();
		if ( empty ) {
			std::unique_lock<std::mutex> lock(_mutex_cond_var);
			_cond_var.wait(lock);
		}
		return !_abort;
	}
	event_task_p _i_event_context::pop() {
		_mutex_event_task.lock();
		event_task_p task = _arr_event_task.front();
		_arr_event_task.pop();
		_mutex_event_task.unlock();
		return task;
	}
	void _i_event_context::process() {
		while ( stop_if_need() ) {
			event_task_p task = pop();
			task->excute();
		}
	}


}