#include <benchmark/benchmark.h>
#include <random>

#include "Registry.h"

struct TransformComponent
{
	float x, y, z;

	void Add()
	{
		x += 0.1f;
		y += 0.1f;
		z += 0.1f;
	}
};

class GameEntity
{
public:
	GameEntity(bool has)
	{
		if (has)
		{
			component_ = std::make_unique<TransformComponent>();
		}
	}

	void Add()
	{
		if (component_)
		{
			component_->Add();
		}
	}

private:
	std::unique_ptr<TransformComponent> component_;
};


static void BM_Pointer(benchmark::State& state) 
{
	int n = state.range(0);
	
	std::vector<GameEntity> entities;
	entities.reserve(n);

	std::mt19937 rng(42);
	std::uniform_int_distribution<int> dist(0, 9);
	for (int i = 0; i < n; i++)
	{
		if (dist(rng) == 0) 
		{
			entities.push_back(GameEntity(true));
		}
		else
		{
			entities.push_back(GameEntity(false));
		}
	}

	for (auto _ : state)
	{
		for (auto& e : entities)
		{
			e.Add();
		}
	}
}

static void BM_ECS(benchmark::State& state)
{
	int n = state.range(0);

	std::mt19937 rng(42);
	std::uniform_int_distribution<int> dist(0, 9);

	ECS::Registry reg;
	for (int i = 0; i < n; i++)
	{
		ECS::Entity e = reg.Create();
		if (dist(rng) == 0)
		{
			reg.Emplace<TransformComponent>(e);
		}
	}

	auto view = reg.View<TransformComponent>();

	for (auto _ : state )
	{
		for (auto e : view)
		{
			TransformComponent& c = view.Get<TransformComponent>(e);
			c.Add();
		}
	}
}

#define BENCHMARK_CONFIG(name) \
  BENCHMARK(name) \
    ->RangeMultiplier(10) \
    ->Range(100000, 10000000) \
    ->Unit(benchmark::kMillisecond)

BENCHMARK_CONFIG(BM_Pointer);
BENCHMARK_CONFIG(BM_ECS);