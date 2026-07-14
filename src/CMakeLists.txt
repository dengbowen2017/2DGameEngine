add_executable(${PROJECT_NAME})

set(ECS_FILES
	"ECS/Registry.h"
	"ECS/Entity.h" 
	"ECS/EntityManager.h" 
	"ECS/ComponentPool.h" 
	"ECS/View.h" 
	"ECS/ComponentManager.h" 
)

target_sources(${PROJECT_NAME} PRIVATE 
	${ECS_FILES} 
	"main.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	SDL3::SDL3
	imgui
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
	$<$<CONFIG:Debug>:GE_DEBUG>
	$<$<CONFIG:Release>:GE_RELEASE>
)