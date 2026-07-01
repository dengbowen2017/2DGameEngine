#include <iostream>

#include "ECS/EntityManager.h"

using namespace ECS;

int main()
{	
	EntityManager mgr;
	Entity e1 = mgr.Generate();
	bool b1 = mgr.Valide(e1);
	Entity e2 = mgr.Generate();
	Entity e3 = mgr.Generate();
	Entity e4 = mgr.Generate();
	Entity e5 = mgr.Generate();

	mgr.Destory(e4);
	mgr.Destory(e1);

	bool b2 = mgr.Valide(e4);

	Entity e6 = mgr.Generate();
	Entity e7 = mgr.Generate();
	Entity e8 = mgr.Generate();

	return 0;
}