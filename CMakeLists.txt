cmake_minimum_required(VERSION 2.8)

project(OPENGL_PROJ)

file(GLOB_RECURSE src
	CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

message(${src})

add_executable(main ${src})

add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glfw)

add_subdirectory(lib/glad)
target_link_libraries(main PRIVATE glad)

add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
target_link_libraries(main PRIVATE glm)
