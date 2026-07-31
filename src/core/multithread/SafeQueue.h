#pragma once

#include <iostream>
#include <chrono>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace VS
{
	class BaseTask
	{
	public:
		virtual ~BaseTask() = default;
		virtual void Run() = 0;
	};

	class Task : public BaseTask
	{
	public:
		virtual void Run() override
		{
			InnerRun();
		}
		
	private:
		void InnerRun()
		{
			std::this_thread::sleep_for(std::chrono::seconds(2));
			std::cout << "Task Complete" << std::endl;
		}
	};

	class SafeQueue
	{
	public:
		SafeQueue() = default;

		void Push(std::shared_ptr<BaseTask> task)
		{
			std::unique_lock<std::mutex> lock(queue_mutex_);
			queue_.push(task);
			lock.unlock();
			queue_condition_.notify_one();
		}
	
		std::shared_ptr<BaseTask> Pop()
		{
			std::unique_lock<std::mutex> lock(queue_mutex_);
			queue_condition_.wait(lock, [this] {
				return !queue_.empty();
				});

			std::shared_ptr<BaseTask> task;
			if (!queue_.empty())
			{
				task = queue_.front();
				queue_.pop();
			}
			return task;
		}

	private:
		std::queue <std::shared_ptr<BaseTask>> queue_;
		std::mutex queue_mutex_;
		std::condition_variable queue_condition_;
	};
}