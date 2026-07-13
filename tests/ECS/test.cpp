#include <gtest/gtest.h>

#include "Registry.h"

TEST(ECSTest, Entity) {
	ECS::Registry reg;
	ECS::Entity e1 = reg.Create();
	ECS::Entity e2 = reg.Create();

	EXPECT_NE(e1, e2);
	EXPECT_TRUE(reg.Valid(e1));
	
	reg.Destory(e1);
	EXPECT_FALSE(reg.Valid(e1));
}

TEST(ECSTest, ComponentPool) {
	struct Component0
	{
		float x;

		Component0()
			:x(0.f)
		{}

		Component0(float X)
			:x(X)
		{}
	};

	struct Component1
	{
		float x;
		float y;

		Component1()
			:x(0.f), y(0.f)
		{}

		Component1(float X, float Y)
			:x(X), y(Y)
		{}
	};

	ECS::Registry reg;
	ECS::Entity e1 = reg.Create();

	Component0& c1 = reg.Emplace<Component0>(e1, 1.f);
	Component1& c2 = reg.Emplace<Component1>(e1, 2.f, 1.f);
	
	Component0& c3 = reg.Get<Component0>(e1);

	EXPECT_EQ(c1.x, c3.x);
	EXPECT_EQ(c3.x, 1.f);
}