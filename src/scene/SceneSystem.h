#pragma once

#include "render/FrameContext.h"

namespace VS
{
	class SceneSystem
	{
	public:
		SceneSystem(FrameContext* context)
			:context_(context)
		{}

		void Update()
		{
			FrameResource& res = context_->GetLogicFrameResource();
			res.sprites.clear();
			res.sprites.emplace_back(100.f, 100.f, 100.f, 100.f);
			res.sprites.emplace_back(300.f, 100.f, 100.f, 100.f);
			res.sprites.emplace_back(300.f, 300.f, 100.f, 100.f);

			context_->SwapContext();
		}

	private:
		FrameContext* context_;
	};
}