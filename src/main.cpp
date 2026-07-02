#include <iostream>

#include "ECS/EntityManager.h"
#include "ECS/ComponentPool.h"

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

struct tmpe
{
	float x;
};

struct T3
{
	int x;
};


int main()
{	
	EntityManager mgr;
	Entity e1 = mgr.Generate();
	bool b1 = mgr.Valide(e1);
	Entity e2 = mgr.Generate();
	Entity e3 = mgr.Generate();
	Entity e4 = mgr.Generate();
	Entity e5 = mgr.Generate();

	//mgr.Destory(e4);
	//mgr.Destory(e1);

	//bool b2 = mgr.Valide(e4);

	//Entity e6 = mgr.Generate();
	//Entity e7 = mgr.Generate();
	//Entity e8 = mgr.Generate();


	ComponentPool<TestComp> p1;

	int id1 = ComponentPool<TestComp>::ID();
	int id2 = ComponentPool<TestComp>::ID();

	int id3 = ComponentPool<T3>::ID();
	int id4 = ComponentPool<T3>::ID();

	int id5 = ComponentPool<tmpe>::ID();
	int id6 = ComponentPool<tmpe>::ID();
	int id7 = ComponentPool<tmpe>::ID();

	p1.Emplace(e1, 1.0f, 1.0f);
	p1.Emplace(e2, 2.f, 2.f);
	p1.Emplace(e3, 3.f, 3.f);
	p1.Emplace(e5);

	for (auto entity : p1)
	{
		std::cout << static_cast<uint32_t>(entity) << std::endl;
	}

	return 0;
}