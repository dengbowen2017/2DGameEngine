#pragma once

#include <vector>
#include <array>

#include <SDL3/SDL.h>

#include "base/timer/Timer.h"
#include "core/multithread/SafeQueue.h"

namespace VS
{
	struct FrameResource
	{
		std::vector<SDL_Texture*> texture;
		std::vector<SDL_FRect> dst_rect;
		std::vector<SDL_FRect> src_rect;
		std::vector<bool> use_src_rect;
		std::vector<int> render_layer;

		FrameResource()
		{
			texture.reserve(100000);
			dst_rect.reserve(100000);
			src_rect.reserve(100000);
			use_src_rect.reserve(100000);
			render_layer.reserve(100000);
		}

		void Clear()
		{
			texture.clear();
			dst_rect.clear();
			src_rect.clear();
			use_src_rect.clear();
			render_layer.clear();
		};
	};

	class FrameContext
	{
	public:
		FrameContext()
		{
			empty_queue_.Push(&frame_resources[0]);
			empty_queue_.Push(&frame_resources[1]);
		}

		FrameResource* GetEmptyResource()
		{
			PROFILE_FUNC();
			return empty_queue_.Pop();
		}

		FrameResource* GetReadyResource()
		{
			PROFILE_FUNC();
			return ready_queue_.Pop();
		}

		void AddEmptyResource(FrameResource* res)
		{
			return empty_queue_.Push(res);
		}

		void AddReadyResource(FrameResource* res)
		{
			return ready_queue_.Push(res);
		}

		void Stop()
		{
			empty_queue_.Stop();
			ready_queue_.Stop();
		}

	private:
		std::array<FrameResource, 2> frame_resources;
		SafeQueue<FrameResource> empty_queue_;
		SafeQueue<FrameResource> ready_queue_;
	};
}
