
set(BBoyBattleManager_GUI_sources
    BBoyBattleManager.cpp
)


#QT
set(Qt_Version_used Qt5)

find_package(${Qt_Version_used} COMPONENTS Widgets REQUIRED)
find_package(${Qt_Version_used} COMPONENTS Core REQUIRED)


add_executable(BBoyBattleManager_GUI
    ${BBoyBattleManager_GUI_sources}
)

set_property(TARGET BBoyBattleManager_GUI PROPERTY CXX_STANDARD 17)


target_link_libraries(BBoyBattleManager_GUI Qt5::Widgets)