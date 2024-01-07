find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)
qt_standard_project_setup()


qt_add_library(B3M_Presentation STATIC)
target_sources(B3M_Presentation
	PUBLIC FILE_SET headers TYPE HEADERS FILES
		"src/Presentation/SlideSelector.hpp"
	PRIVATE FILE_SET implementations TYPE CXX_MODULES FILES
		"src/Presentation/SlideSelector.cpp"
)
target_include_directories(B3M_Presentation
	PUBLIC
		"src/Presentation"
)
target_link_libraries(B3M_Presentation
	PUBLIC
		Qt::Widgets
)



qt_add_library(EY2023_Presentation STATIC)
target_sources(EY2023_Presentation
	PUBLIC FILE_SET headers TYPE HEADERS FILES
		"src/ExpressYourself2023/StartupSlideSelector.hpp"
		"src/ExpressYourself2023/RankingSlideSelector.hpp"
		"src/ExpressYourself2023/MatchSlideSelector.hpp"
	PRIVATE FILE_SET implementations TYPE CXX_MODULES FILES
		"src/ExpressYourself2023/StartupSlideSelector.cpp"
		"src/ExpressYourself2023/RankingSlideSelector.cpp"
		"src/ExpressYourself2023/MatchSlideSelector.cpp"
)
target_include_directories(EY2023_Presentation
	PUBLIC
		"src/ExpressYourself2023"
		"src/TournamentManagement" //TODO to boost::signals - signal results changed from Match itself
)
target_link_libraries(EY2023_Presentation
	PUBLIC
		Qt::Core
		B3M_Presentation
		B3M_Common
		B3M_Logic
)



qt_add_executable(B3M_GUI MACOSX_BUNDLE WIN32
	"src/B3M_GUI_main.cpp"
)
target_sources(B3M_GUI
	PUBLIC FILE_SET headers TYPE HEADERS FILES
		"src/MainWindow.hpp"
		"src/ParticipantsDialog.hpp"
		"src/TeamsView.hpp"
		"src/TournamentManagement/Window.hpp"
		"src/TournamentManagement/TournamentRoundWidget.hpp"
		"src/TournamentManagement/MatchResultDialog.hpp"
		"src/Presentation/ManagementWindow.hpp"
	PRIVATE FILE_SET implementations TYPE CXX_MODULES FILES
		"src/MainWindow.cpp"
		"src/ParticipantsDialog.cpp"
		"src/TeamsView.cpp"
		"src/TournamentManagement/Window.cpp"
		"src/TournamentManagement/TournamentRoundWidget.cpp"
		"src/TournamentManagement/MatchResultDialog.cpp"
		"src/Presentation/ManagementWindow.cpp"
)

set_target_properties(B3M_GUI
	PROPERTIES
		AUTOMOC TRUE
		AUTOUIC TRUE
) 

target_link_libraries(B3M_GUI 
	PRIVATE
		Qt::Widgets Qt::Gui Qt::Core
		B3M_Common
		B3M_Database
		EY2023_Presentation
)