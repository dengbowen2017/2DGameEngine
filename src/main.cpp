#include <iostream>

#include "ECS/Registry.h"

using namespace ECS;

struct TestComp
{
	float x;
	float y;

	TestComp()
		:x(0), y(0)
	{}

	TestComp(float x_, float y_)
		:x(x_), y(y_)
	{}
};

struct tmp
{
	float x;
};

struct T3
{
	int x;
};


int main()
{	
	Registry reg;

	Entity e1 = reg.Create();
	Entity e2 = reg.Create();
	Entity e3 = reg.Create();

	decltype(auto) c1 = reg.Emplace<TestComp>(e1, 1.f, 1.f);
	decltype(auto) c2 = reg.Emplace<T3>(e1);

	decltype(auto) c3 = reg.Get<TestComp>(e1);

	reg.Emplace<TestComp>(e2, 2.f, 2.f);

	reg.Emplace<T3>(e2);
	reg.Emplace<TestComp>(e3);

	reg.Destory(e1);

	return 0;
}