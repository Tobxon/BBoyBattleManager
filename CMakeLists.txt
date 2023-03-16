cmake_minimum_required(VERSION 3.26)

project(BBoyBattleManager VERSION 0.1.0 LANGUAGES CXX)

# C++20 as base language version for this project
set(CMAKE_CXX_STANDARD 20)
#C++20 Modules
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1) #request experimental C++20 modules support
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  include(clang_modules.cmake)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  include(gcc_modules.cmake)
endif()


# to get a more clean solution overview (e.g. CMakePredefinedTargets as a folder)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#subprojects
add_subdirectory(B3M_Common)

add_subdirectory(B3M_Database)
add_subdirectory(B3M_Engine)

add_subdirectory(B3M_ConsoleApp)

# Start Up Project - B-Boy Battle Manager                                                     ######
add_subdirectory(B3M_GUI)
# Settings for Visual Studio 
if (CMAKE_GENERATOR MATCHES "Visual Studio")
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT B3M_GUI)
endif()