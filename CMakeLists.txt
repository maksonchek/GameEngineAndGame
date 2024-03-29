cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

set(PROJECT_NAME GameEngine)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} 
	src/main.cpp

	src/Resources/ResourceManager.cpp
	src/Resources/ResourceManager.h
	src/Resources/stb_image.h

	src/Renderer/ShaderManager.cpp
	src/Renderer/ShaderManager.h
	src/Renderer/TextureManager.cpp
	src/Renderer/TextureManager.h
	src/Renderer/Sprite.h
	src/Renderer/Sprite.cpp
	src/Renderer/SpriteAnimator.h
	src/Renderer/SpriteAnimator.cpp
	src/Renderer/VertexBuffer.h
	src/Renderer/VertexBuffer.cpp
	src/Renderer/IndexBuffer.h
	src/Renderer/IndexBuffer.cpp
	src/Renderer/VertexArray.h
	src/Renderer/VertexArray.cpp
	src/Renderer/VertexBufferLayout.h
	src/Renderer/VertexBufferLayout.cpp
	src/Renderer/Renderer.h
	src/Renderer/Renderer.cpp

	src/Game/Game.h
	src/Game/Game.cpp
	src/Game/GameObjects/TankGameObject.h
	src/Game/GameObjects/TankGameObject.cpp
	src/Game/GameObjects/GameObjectInterface.cpp
	src/Game/GameObjects/GameObjectInterface.h
	src/Game/GameObjects/WallGameObject.cpp
	src/Game/GameObjects/WallGameObject.h
	src/Game/Level.h
	src/Game/Level.cpp
	src/Game/LevelInterface.h
	src/Game/LevelInterface.cpp
	src/Game/GameObjects/ConcreteWallGameObject.cpp
	src/Game/GameObjects/ConcreteWallGameObject.h
	src/Game/GameObjects/Trees.cpp
	src/Game/GameObjects/Trees.h
	src/Game/GameObjects/Ice.cpp
	src/Game/GameObjects/Ice.h
	src/Game/GameObjects/Water.cpp
	src/Game/GameObjects/Water.h
	src/Game/GameObjects/Eagle.cpp
	src/Game/GameObjects/Eagle.h
	src/Game/GameObjects/Border.cpp
	src/Game/GameObjects/Border.h
	src/Game/GameObjects/Bullet.cpp
	src/Game/GameObjects/Bullet.h

	src/EngineSystem/Timer.cpp
	src/EngineSystem/Timer.h

	src/PhysicsEngine/PhysicsEngine.cpp
	src/PhysicsEngine/PhysicsEngine.h			
)


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)


add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

include_directories(external/glm)
include_directories(external/jsonParser/include)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/install" CACHE PATH "..." FORCE)
endif()

include(GNUInstallDirs)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})


install(TARGETS ${PROJECT_NAME} 
        CONFIGURATIONS Release
        DESTINATION GameEngine)
install(DIRECTORY res/ DESTINATION GameEngine/res)
