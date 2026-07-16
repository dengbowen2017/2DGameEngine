#pragma once

namespace GE
{
	struct TransformComponent
	{
		float x, y, z;
		TransformComponent()
			:x(0.f), y(0.f), z(0.f)
		{}
		TransformComponent(float x, float y, float z = 0.f)
			:x(x), y(y), z(z)
		{}
	};
}