#pragma once

#include <vector>

#include <SDL3/SDL.h>

namespace VS
{
	struct FrameResource
	{
		std::vector<SDL_FRect> sprites;
	};

	class FrameContext
	{
	public:
		void SwapContext()
		{
			std::swap(logic_index, render_index);
		}

		FrameResource& GetLogicFrameResource()
		{
			return resources[logic_index];
		}

		FrameResource& GetRenderFrameResource()
		{
			return resources[render_index];
		}

	private:
		int logic_index = 0;
		int render_index = 1;
		FrameResource resources[2];
	};
}
