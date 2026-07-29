add_executable(${PROJECT_NAME})

set(SCENE_FILES
	"scene/ecs/Registry.h"
	"scene/ecs/Entity.h" 
	"scene/ecs/EntityManager.h" 
	"scene/ecs/ComponentPool.h" 
	"scene/ecs/View.h" 
	"scene/ecs/ComponentManager.h"
	"scene/Component.h"
)

set(CORE_FILES
	"base/Game.h"
	"base/Game.cpp"
	"base/main.cpp"
)

set(RENDER_FILES
	"render/RenderSystem.h"
	"render/RenderSystem.cpp"
	"render/WindowSystem.h"
	"render/WindowSystem.cpp"
)

target_sources(${PROJECT_NAME} PRIVATE 
	${SCENE_FILES} 
	${CORE_FILES}
	${RENDER_FILES})

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