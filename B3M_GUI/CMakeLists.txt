#QT
set(Qt_Version_used 6)

find_package(Qt${Qt_Version_used} REQUIRED COMPONENTS Widgets Gui Core)


qt_add_executable(B3M_GUI MACOSX_BUNDLE WIN32
	"src/B3M_GUI_main.cpp"
)
target_sources(B3M_GUI
	PUBLIC FILE_SET headers TYPE HEADERS FILES
		"src/MainWindow.hpp"
		"src/ParticipantsDialog.hpp"
		"src/TeamsView.hpp"
	PRIVATE FILE_SET implementations TYPE CXX_MODULES FILES
		"src/MainWindow.cpp"
		"src/MainWindow.ui"
		"src/ParticipantsDialog.cpp"
		"src/ParticipantsDialog.ui"
		"src/TeamsView.cpp"
)

set_target_properties(B3M_GUI PROPERTIES  
	AUTOMOC TRUE
	AUTOUIC TRUE
) 

target_link_libraries(B3M_GUI 
	PRIVATE
		Qt::Widgets Qt::Gui Qt::Core
		B3M_Common
		B3M_Database
)