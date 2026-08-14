#pragma once

#include <chrono>
#include <string>
#include <spdlog/spdlog.h>

//#define PROFILING
#ifdef PROFILING
#define PROFILE_SCOPE(name)	ProfileTimer timer(name)
#define PROFILE_FUNC() PROFILE_SCOPE(__FUNCTION__)
#else
#define PROFILE_SCOPE(name)
#define PROFILE_FUNC()
#endif // PROFILING

namespace VS
{
	class Timer
	{
	public:
		Timer()
		{
			Reset();
		}

		virtual ~Timer() = default;

		void Reset()
		{
			time_start_ = std::chrono::high_resolution_clock::now();
		}

		float Elapsed()
		{
			auto now_time_point = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float> time_span = now_time_point - time_start_;
			float dt = time_span.count();
			return dt;
		}

	protected:
		std::chrono::time_point<std::chrono::high_resolution_clock> time_start_;
	};

	class ProfileTimer : public Timer
	{
	public:
		ProfileTimer(const std::string& name)
			:name_(name)
		{}

		~ProfileTimer()
		{
			Stop();
		}

	private:
		void Stop()
		{
			float dt = Elapsed();
			spdlog::info("Name: {0}, DeltaTime: {1}ms", name_, dt * 1000);
		}

		std::string name_;
	};
}