cmake_minimum_required(VERSION 3.28)

project(BBoyBattleManager VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)


#to get a more clean solution overview (e.g. CMakePredefinedTargets as a folder)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#subprojects
add_subdirectory(Utility)
add_subdirectory(B3M_Common)
add_subdirectory(B3M_Logic)
add_subdirectory(B3M_Database)

add_subdirectory(B3M_ConsoleApp)

#Start Up Project - B-Boy Battle Manager                                                      ######
add_subdirectory(B3M_GUI)
#Settings for Visual Studio 
if (CMAKE_GENERATOR MATCHES "Visual Studio")
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT B3M_GUI)
endif()