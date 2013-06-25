# Require a recent version of cmake
cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)
# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (HPXCOL)

find_package(OpenGL REQUIRED)

# Compile external dependencies 
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-1c73e35")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)



include_directories(
	external/AntTweakBar-1.16/include/
	external/glfw-2.7.6/include/
	external/glm-0.9.4.0/
	external/glew-1.9.0/include/
	external/assimp-3.0.1270/include/
	external/bullet-2.81-rev2613/src/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	GLFW_276
	GLEW_190
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)


# This adds the HPX cmake configuration directory to the search path.
set(CMAKE_MODULE_PATH
    $ENV{HPX_DIR}/share/cmake-2.8/Modules)

# Instruct cmake to find the HPX settings
find_package(HPX)

include_directories(${HPX_INCLUDE_DIR})
link_directories(${HPX_LIBRARY_DIR})

set (sources 
	playground/playground.cpp
	playground/util.cpp
	playground/util.hpp
	playground/vert.glsl
	playground/frag.glsl
	common/controls.cpp
	common/controls.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/shader.cpp
	common/shader.hpp
	common/texture.cpp
	common/texture.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp)

# add example executable
add_hpx_executable(playground
             SOURCES ${sources}
             ${PLAYGROUND_FLAGS} 
             FOLDER 
             COMPONENT_DEPENDENCIES ${ALL_LIBS} assimp)

create_target_launcher(playground_exe WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/playground/")

