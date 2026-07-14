add_executable(ECS_benchmark
	"benchmark.cpp"
)

target_link_libraries(ECS_benchmark
	ECS_lib
	benchmark::benchmark_main
)