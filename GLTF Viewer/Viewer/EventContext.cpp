#include "EventContext.h"

namespace vNaonCommon {

	// Event
	CInterfaceEventTask::CInterfaceEventTask() {
		mAbort = false;
	}

	CInterfaceEventTask::~CInterfaceEventTask() {
	}

	void CInterfaceEventTask::excuteTask() {
		if ( !mAbort )
			excute();
	}

	void CInterfaceEventTask::abort() {
		mAbort = true;
	}

	void CInterfaceEventTask::excute() {
	}

	// Context
	CEventContext::CEventContext() {
		mAbort = false;
		pThread = new std::thread(&CEventContext::process, this);
	}

	CEventContext::~CEventContext() {
		abort();
		pThread->join();
		delete pThread;
	}

	void CEventContext::push(EventTask command) {
		if ( command == nullptr ) return;

		mTaskMutex.lock();
		mTaskQueue.push(command);
		mTaskMutex.unlock();

		mConditionVariable.notify_one();
	}

	void CEventContext::abort() {
		mAbort = true;
		mConditionVariable.notify_one();
	}

	bool CEventContext::stopProcessIfNeed() {
		mTaskMutex.lock();
		bool empty = mTaskQueue.empty();
		mTaskMutex.unlock();

		if ( empty ) {
			std::unique_lock<std::mutex> lock(mConditionVariableMutex);
			mConditionVariable.wait(lock);
		}

		return !mAbort;
	}

	EventTask CEventContext::pop() {
		mTaskMutex.lock();
		EventTask task = mTaskQueue.front();
		mTaskQueue.pop();
		mTaskMutex.unlock();

		return task;
	}

	void CEventContext::process() {

		while ( stopProcessIfNeed() ) {
			EventTask task = pop();
			task->excuteTask();
		}

	}


}