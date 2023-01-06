
set(BBoyBattleManager_GUI_sources
    BBoyBattleManager.cpp
)

add_executable(BBoyBattleManager_GUI
    ${BBoyBattleManager_GUI_sources}
)

set_property(TARGET BBoyBattleManager_GUI PROPERTY CXX_STANDARD 20)