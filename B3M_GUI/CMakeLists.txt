
set(B3M_GUI_public_headers
    
)

set(B3M_GUI_sources
    src/emtpy.cpp
)


#QT
set(Qt_Version_used Qt6)

find_package(${Qt_Version_used} COMPONENTS Widgets REQUIRED)
# find_package(${Qt_Version_used} COMPONENTS Core REQUIRED)
qt_standard_project_setup()


add_library(B3M_GUI
    ${B3M_GUI_sources}
)


target_link_libraries(B3M_GUI 
    PUBLIC 
        # ${Qt_Version_used}::Core
        ${Qt_Version_used}::Widgets
)
