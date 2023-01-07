
set(BBoyBattleManager_GUI_sources
    BBoyBattleManager.cpp
)


#QT
set(Qt_Version_used Qt6)

find_package(${Qt_Version_used} COMPONENTS Widgets REQUIRED)
# find_package(${Qt_Version_used} COMPONENTS Core REQUIRED)
qt_standard_project_setup()


add_executable(BBoyBattleManager_GUI
    ${BBoyBattleManager_GUI_sources}
)

set_property(TARGET BBoyBattleManager_GUI PROPERTY CXX_STANDARD 20)


target_link_libraries(BBoyBattleManager_GUI 
    PRIVATE 
        ${Qt_Version_used}::Core
        ${Qt_Version_used}::Widgets
)
