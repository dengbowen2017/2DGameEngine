#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

namespace VS
{
	template<typename T>
	class SafeQueue
	{
	public:
		SafeQueue()
			:is_stopped_(false)
		{}

		void Push(T* object)
		{
			{
				std::lock_guard<std::mutex> lock(queue_mutex_);
				if (is_stopped_)
				{
					return;
				}
				queue_.push(object);
			}
			queue_condition_.notify_one();
		}
	
		T* Pop()
		{
			std::unique_lock<std::mutex> lock(queue_mutex_);
			queue_condition_.wait(lock, [this] {return !queue_.empty() || is_stopped_; });

			if (queue_.empty())
			{
				return nullptr;
			}

			T* object = queue_.front();
			queue_.pop();
			return object;
		}

		void Stop()
		{
			{
				std::lock_guard<std::mutex> lock(queue_mutex_);
				is_stopped_ = true;
			}
			queue_condition_.notify_all();
		}

	private:
		std::queue <T*> queue_;
		std::mutex queue_mutex_;
		std::condition_variable queue_condition_;
		bool is_stopped_;
	};
}