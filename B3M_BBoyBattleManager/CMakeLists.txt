set(BBoyBattleManager_public_headers
    
)

set(BBoyBattleManager_sources
    src/BBoyBattleManager.cpp
)


add_executable(BBoyBattleManager
    ${BBoyBattleManager_public_headers}
    ${BBoyBattleManager_sources}
)

target_link_libraries(BBoyBattleManager
    PRIVATE
        B3M_GUI
)

