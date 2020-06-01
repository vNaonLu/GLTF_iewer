#pragma once
#include <memory>
#include <functional>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>

namespace vNaonCommon {

	class CInterfaceEventTask{
	protected:
		bool mAbort;

	public:
		CInterfaceEventTask();
		~CInterfaceEventTask();
		void excuteTask();
		void abort();
	protected:
		virtual void excute();
	};
	typedef std::shared_ptr<CInterfaceEventTask> EventTask;

	template<class T>
	class CEventTask : public CInterfaceEventTask {
	protected:
		typedef std::function<void(T)> Task;
		T mInput;
		Task mProcess;

	public:
		static EventTask create(T value, Task process) {
			return std::make_shared<CEventTask<T>>(value, process);
		}

		CEventTask(T value, Task process){
			this->mInput = value;
			this->mProcess = process;
		}
		~CEventTask() {
		}

	protected:
		virtual void excute() override {
			mProcess(mInput);
		}

	};

	class CEventContext {
	
	protected:
		bool mAbort;
		std::thread *pThread;

		std::mutex mTaskMutex;
		std::queue<EventTask> mTaskQueue;

		std::mutex mConditionVariableMutex;
		std::condition_variable mConditionVariable;

	public:
		CEventContext();
		~CEventContext();

		void push(EventTask command);
		
		void abort();

	protected:
		bool stopProcessIfNeed();
		EventTask pop();
		virtual void process();
	
	};

}