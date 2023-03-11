#QT
set(Qt_Version_used 6)

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
	#C++20 Modules
	PRIVATE
		FILE_SET cxx_modules TYPE CXX_MODULES FILES
		"src/B3M_MainWindow.ixx"
)

target_link_libraries(B3M_GUI 
	PRIVATE
		Qt::Widgets Qt::Gui Qt::Core
		B3M_Common
)