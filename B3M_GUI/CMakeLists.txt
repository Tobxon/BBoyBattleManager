#QT
set(Qt_Version_used 6)

#set(CMAKE_PREFIX_PATH "E:/Dev/3rdParty/Qt/Qt6.4.2/6.4.2/msvc2019_64")
find_package(Qt${Qt_Version_used} REQUIRED 
    COMPONENTS Widgets Gui Core
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)


qt_add_executable(B3M_GUI MACOSX_BUNDLE WIN32
    "src/B3M_GUI_main.cpp"
)
target_sources(B3M_GUI
    PRIVATE
        "src/B3M_MainWindow.cpp"
        "src/B3M_MainWindow.ui"
)

if(B3M_use_cxx_modules)
    target_sources(B3M_GUI
        PRIVATE
            FILE_SET cxx_modules TYPE CXX_MODULES FILES
            "src/B3M_MainWindow.ixx"
    )
else()
    target_sources(B3M_GUI
        PRIVATE
            "src/B3M_MainWindow.hpp"
    )
endif()

target_link_libraries(B3M_GUI 
    PRIVATE
        Qt::Widgets Qt::Gui Qt::Core
)
