#include "common_context.h"



namespace vnaon_common {
	// ---
	InteraceEvent::InteraceEvent() {
		_abort = false;
	}
	InteraceEvent::~InteraceEvent() {
	}
	void InteraceEvent::excute() {
		if ( !_abort ) Process();
	}
	void InteraceEvent::Expire() {
		_abort = true;
	}
	void InteraceEvent::Process() {
	}



	EventContext::EventContext() {
		_abort = false;
		context_thread_p = new std::thread (&EventContext::Process, this);
	}
	EventContext::~EventContext() {
		Expire();
		context_thread_p->join();
		delete context_thread_p;
	}
	bool EventContext::IsValid() const {
		return !_abort;
	}
	void EventContext::PushEvent(InteraceEvent_p command) {
		if ( command == nullptr ) return;

		_mutex_event_task.lock();
		_arr_event_task.push(command);
		_mutex_event_task.unlock();

		_cond_var.notify_one();
	}
	void EventContext::Expire() {
		_abort = true;
		_cond_var.notify_one();
	}
	bool EventContext::IdleIfNeed() {
		_mutex_event_task.lock();
		bool empty = _arr_event_task.empty();
		_mutex_event_task.unlock();
		if ( empty ) {
			std::unique_lock<std::mutex> lock(_mutex_cond_var);
			_cond_var.wait(lock);
		}
		return !_abort;
	}
	InteraceEvent_p EventContext::PopEvent() {
		_mutex_event_task.lock();
		InteraceEvent_p task = _arr_event_task.front();
		_arr_event_task.pop();
		_mutex_event_task.unlock();
		return task;
	}
	void EventContext::Process() {
		while ( IdleIfNeed() ) {
			InteraceEvent_p task = PopEvent();
			task->excute();
		}
	}


}