add_executable(ECS_test
	"test.cpp"
)

target_link_libraries(ECS_test
	ECS_lib
	GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ECS_test)