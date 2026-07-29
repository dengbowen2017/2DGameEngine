#pragma once

#include <SDL3/SDL.h>

namespace GE
{
	struct TransformComponent
	{
		float x, y, w, h;
		TransformComponent()
			:x(0.f), y(0.f), w(0.f), h(0.f)
		{}
		TransformComponent(float x, float y, float w, float h)
			:x(x), y(y), w(w), h(h)
		{}
	};

	struct TextureComponent
	{
		SDL_Texture* texture = nullptr; // GPU 贴图句柄

		// 裁剪区域 (Source Rect)
		SDL_FRect srcRect{ 0.0f, 0.0f, 0.0f, 0.0f };
		bool useSrcRect = false;        // true: 使用 srcRect 局部裁剪 (例如 Sprite 切片)
		// false: 渲染整张图片 (传 NULL 给 SDL)

		int renderLayer = 0;            // 渲染层级 (排序用，例如：0=背景, 1=角色, 2=UI)
		bool visible = true;            // 是否显示

		SDL_RenderTex
	};
}