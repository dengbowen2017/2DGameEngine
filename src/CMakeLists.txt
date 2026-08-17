add_executable(${PROJECT_NAME})

set(CORE_FILES
	"core/ecs/Registry.h"
	"core/ecs/Entity.h" 
	"core/ecs/EntityManager.h" 
	"core/ecs/ComponentPool.h" 
	"core/ecs/View.h" 
	"core/ecs/ComponentManager.h"
	"core/multithread/SafeQueue.h"
)

set(SCENE_FILES
	"scene/Component.h"
	"scene/GameObject.h"
	"scene/SceneSystem.h"
	"scene/SceneSystem.cpp"
)

set(BASE_FILES
	"base/Game.h"
	"base/Game.cpp"
	"base/main.cpp"
	"base/Timer.h"
	"base/InputSystem.h"
	"base/InputSystem.cpp"
)

set(RENDER_FILES
	"render/RenderSystem.h"
	"render/RenderSystem.cpp"
	"render/WindowSystem.h"
	"render/WindowSystem.cpp"
	"render/FrameContext.h"
)

target_sources(${PROJECT_NAME} PRIVATE 
	${BASE_FILES}
	${CORE_FILES} 
	${SCENE_FILES}
	${RENDER_FILES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	SDL3::SDL3
#	SDL3_image::SDL3_image
#	SDL3_ttf::SDL3_ttf
	imgui
	spdlog::spdlog
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
	$<$<CONFIG:Debug>:GE_DEBUG>
	$<$<CONFIG:Release>:GE_RELEASE>
)