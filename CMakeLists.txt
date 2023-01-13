
cmake_minimum_required(VERSION 3.6)
# C++20 as base language version for this project
set (CMAKE_CXX_STANDARD 20)

project(BBoyBattleManager VERSION 0.1.0)

# to get a more clean solution overview (e.g. CMakePredefinedTargets as a folder)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Start Up Project - B-Boy Battle Manager                                                     ######
add_subdirectory(B3M_BBoyBattleManager)
# Settings for Visual Studio 
if (CMAKE_GENERATOR MATCHES "Visual Studio")
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT BBoyBattleManager)
endif()

add_subdirectory(B3M_GUI)
add_subdirectory(B3M_Database)
add_subdirectory(B3M_Engine)