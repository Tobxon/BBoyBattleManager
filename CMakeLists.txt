
cmake_minimum_required(VERSION 3.23)

project(BBoyBattleManager VERSION 0.1.0 LANGUAGES CXX)

set(B3M_use_cxx_modules true)
# C++20 as base language version for this project
set(CMAKE_CXX_STANDARD 20)
if(B3M_use_cxx_modules)
	set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "3c375311-a3c9-4396-a187-3227ef642046")
	if(WIN32)
	  include("cmake/msvc_modules.cmake")
	else()
	  include("cmake/gcc_modules.cmake")
	endif()
endif()

# to get a more clean solution overview (e.g. CMakePredefinedTargets as a folder)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Start Up Project - B-Boy Battle Manager                                                     ######
add_subdirectory(B3M_GUI)
# Settings for Visual Studio 
if (CMAKE_GENERATOR MATCHES "Visual Studio")
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT B3M_GUI)
endif()

add_subdirectory(B3M_Database)
add_subdirectory(B3M_Engine)