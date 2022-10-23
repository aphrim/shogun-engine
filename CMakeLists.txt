cmake_minimum_required(VERSION 2.8)

project(Shogun_Engine)

file(GLOB_RECURSE editorSrc
	CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE playerSrc
	CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

list(REMOVE_ITEM editorSrc "${CMAKE_CURRENT_SOURCE_DIR}/src/player.cpp")
list(REMOVE_ITEM playerSrc "${CMAKE_CURRENT_SOURCE_DIR}/src/editor.cpp")

add_executable(SHOGUN_EDITOR ${editorSrc})
add_executable(SHOGUN_PLAYER ${playerSrc})

add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
target_link_libraries(SHOGUN_EDITOR PRIVATE glfw)
target_link_libraries(SHOGUN_PLAYER PRIVATE glfw)

add_subdirectory(lib/glad)
target_link_libraries(SHOGUN_EDITOR PRIVATE glad)
target_link_libraries(SHOGUN_PLAYER PRIVATE glad)

add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
target_link_libraries(SHOGUN_EDITOR PRIVATE glm)
target_link_libraries(SHOGUN_PLAYER PRIVATE glm)
