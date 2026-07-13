#include <benchmark/benchmark.h>
#include <random>

#include "Registry.h"

#include "entt.hpp"

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
	int max = state.range(1);
	
	std::vector<GameEntity> entities;
	entities.reserve(n);

	std::mt19937 rng(42);
	std::uniform_int_distribution<int> dist(0, max);
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
			benchmark::DoNotOptimize(e);
		}
	}
}

static void BM_ECS(benchmark::State& state)
{
	int n = state.range(0);
	int max = state.range(1);

	std::mt19937 rng(42);
	std::uniform_int_distribution<int> dist(0, max);

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
			benchmark::DoNotOptimize(c);
		}
	}
}

static void BM_ENTT(benchmark::State& state)
{
	int n = state.range(0);
	int max = state.range(1);

	std::mt19937 rng(42);
	std::uniform_int_distribution<int> dist(0, max);

	entt::registry reg;
	for (int i = 0; i < n; i++)
	{
		entt::entity e = reg.create();
		if (dist(rng) == 0)
		{
			reg.emplace<TransformComponent>(e);
		}
	}

	auto view = reg.view<TransformComponent>();
	for (auto _ : state)
	{
		for (auto e : view)
		{
			auto& c = view.get<TransformComponent>(e);
			c.Add();
			benchmark::DoNotOptimize(c);
		}
	}
}

static void BM_ENTT_EACH(benchmark::State& state)
{
	int n = state.range(0);
	int max = state.range(1);

	std::mt19937 rng(42);
	std::uniform_int_distribution<int> dist(0, max);

	entt::registry reg;
	for (int i = 0; i < n; i++)
	{
		entt::entity e = reg.create();
		if (dist(rng) == 0)
		{
			reg.emplace<TransformComponent>(e);
		}
	}

	for (auto _ : state)
	{
		auto view = reg.view<TransformComponent>();

		view.each([](TransformComponent& c) {
			c.Add();
			benchmark::DoNotOptimize(c);
			});
	}
}

constexpr auto DIST_MAX = 9;

#define BENCHMARK_CONFIG(name) \
  BENCHMARK(name) \
    ->Args({10000, DIST_MAX}) \
    ->Args({100000, DIST_MAX}) \
	->Args({1000000, DIST_MAX}) \
    ->Unit(benchmark::kMillisecond)

BENCHMARK_CONFIG(BM_Pointer);
BENCHMARK_CONFIG(BM_ECS);
BENCHMARK_CONFIG(BM_ENTT);
BENCHMARK_CONFIG(BM_ENTT_EACH);