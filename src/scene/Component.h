#pragma once

#include <SDL3/SDL.h>

namespace VS
{
	struct TransformComponent
	{
		SDL_FRect rect;
		TransformComponent()
			:rect{0.f, 0.f, 0.f, 0.f}
		{}
		TransformComponent(float x, float y, float w, float h)
			:rect{x, y, w, h}
		{}
	};

	struct TextureComponent
	{
		SDL_Texture* texture = nullptr;

		SDL_FRect src_rect{ 0.0f, 0.0f, 0.0f, 0.0f };
		bool use_src_rect = false;

		int render_layer = 0;
		bool visible = true;
	};
}