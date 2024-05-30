find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)
qt_standard_project_setup()


qt_add_library(B3M_Presentation STATIC)
target_sources(B3M_Presentation
	PUBLIC FILE_SET interfaces TYPE CXX_MODULES FILES
		"src/Presentation/Presentation.ixx"
		"src/Presentation/CommonSlidesStyle.ixx"
	PUBLIC FILE_SET headers TYPE HEADERS FILES
		"src/Presentation/SlideSelector.hpp"
	PRIVATE
		"src/Presentation/SlideSelector.cpp"
		"src/Presentation/CommonSlidesStyle.cpp"
)
target_include_directories(B3M_Presentation
	PUBLIC
		"src/Presentation"
)
target_link_libraries(B3M_Presentation
	PUBLIC
		Qt::Widgets
)
target_compile_options(B3M_Presentation PRIVATE -wd5050) #this is currently necessary for targets that are dependent on Qt #TODO remove if Qt works properly with modules



add_library(EY2023_Presentation #TODO proper separation of custom style library and general gui code
	"../EY2023/ey2023_presentation.qrc"
)
target_sources(EY2023_Presentation
	PUBLIC FILE_SET interfaces TYPE CXX_MODULES FILES
		"src/ExpressYourself2023/EY2023.ixx"
		"src/ExpressYourself2023/SlidesStyle.ixx"
	PUBLIC FILE_SET headers TYPE HEADERS FILES
		"src/ExpressYourself2023/StartupSlideSelector.hpp"
		"src/ExpressYourself2023/RankingSlideSelector.hpp"
		"src/ExpressYourself2023/MatchSlideSelector.hpp"
	PRIVATE
		"src/ExpressYourself2023/StartupSlideSelector.cpp"
		"src/ExpressYourself2023/RankingSlideSelector.cpp"
		"src/ExpressYourself2023/MatchSlideSelector.cpp"
		"src/ExpressYourself2023/SlidesStyle.cpp"
)
target_include_directories(EY2023_Presentation
	PUBLIC
		"src/ExpressYourself2023"
		"src/TournamentManagement" #I#5 to boost::signals - signal results changed from Match itself
)
set_target_properties(EY2023_Presentation
	PROPERTIES
		AUTORCC TRUE
)
target_link_libraries(EY2023_Presentation
	PUBLIC
		Qt::Core
		B3M_Presentation
		B3M_Common
		B3M_Logic
)
target_compile_options(EY2023_Presentation PRIVATE -wd5050) #this is currently necessary for targets that are dependent on Qt #TODO remove if Qt works properly with modules



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
	PRIVATE
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
target_compile_options(B3M_GUI PRIVATE -wd5050) #this is currently necessary for targets that are dependent on Qt #TODO remove if Qt works properly with modules