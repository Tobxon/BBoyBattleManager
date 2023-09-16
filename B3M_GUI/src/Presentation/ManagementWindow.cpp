//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx). (or header file if modules aren't working for it yet)


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------
#include "ManagementWindow.hpp"

//std
import <algorithm>;
import <ranges>;

//Qt
#include <QScreen>
#include <QGuiApplication>
#include <QPixmap>

//b3m
#include <TournamentRoundWidget.hpp> //TODO to boost::signals - signal results changed from Match itself


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
using b3m::gui::ey2023::MatchSlideSelector;
using b3m::gui::ey2023::RankingSlideSelector;


//--------------------------------------------------------------------------------------------------
//------ Implementations                                                                      ------
//--------------------------------------------------------------------------------------------------

b3m::gui::PresentationManagementWindow::PresentationManagementWindow(QWidget* i_parent)
	: QWidget(i_parent)
{
	m_ui->setupUi(this);

	connect(this, &PresentationManagementWindow::slidesVisible, m_ui->upLeftButton, &QPushButton::setEnabled);
	connect(this, &PresentationManagementWindow::slidesVisible, m_ui->upRightButton, &QPushButton::setEnabled);

	connect(m_ui->lowLeftButton, &QPushButton::clicked, [this](){
		initializeScreen();
		emit slidesVisible(true);
		if(m_curSlide){ m_curSlide->setEnabled(false); } //TODO bad design?
	});
	connect(m_ui->lowRightButton, &QPushButton::clicked, [this](){
		m_presentationWindow->hide();
		emit slidesVisible(false);
	});

	//switching monitors
	connect(m_ui->upLeftButton, &QPushButton::clicked, [this](){
		const auto numOfScreens = QGuiApplication::screens().size();
		m_presentationWindowScreeIndex = (m_presentationWindowScreeIndex == 0) ? numOfScreens-1 : --m_presentationWindowScreeIndex%(numOfScreens);
		initializeScreen();
	});
	connect(m_ui->upRightButton, &QPushButton::clicked, [this](){
		m_presentationWindowScreeIndex = ++m_presentationWindowScreeIndex%(QGuiApplication::screens().size());
		initializeScreen();
	});

	//add slide selectors
	for(auto* const curSlide : m_slides)
	{
		initializeSlide(*curSlide);
	}
}

b3m::gui::PresentationManagementWindow::~PresentationManagementWindow()
{
	std::ranges::for_each(m_slides, [](auto* slide){
		if(slide) delete slide;
		slide = nullptr;
	});
	if(m_presentationWindow){ delete m_presentationWindow; }
	delete m_ui;
}

void b3m::gui::PresentationManagementWindow::addSlideFor(TournamentRound& i_round, const TournamentRoundWidget& i_roundWidget) //TODO to boost::signals - signal results changed from Match itself
{
	auto* const slide = new MatchSlideSelector(i_round, this);
	addNewSlide(*slide);
	connect(&i_roundWidget, &TournamentRoundWidget::scoresUpdated, slide, &MatchSlideSelector::updateScores); //TODO to boost::signals - signal results changed from Match itself
}

void b3m::gui::PresentationManagementWindow::newRanking(const SortedContestantsRanking& i_contestantsRanking)
{
	auto* const slide = new RankingSlideSelector(i_contestantsRanking, this);
	addNewSlide(*slide);
}

void b3m::gui::PresentationManagementWindow::initializeScreen()
{
	const auto *const screen = QGuiApplication::screens()[m_presentationWindowScreeIndex];
	m_presentationWindow->move(screen->geometry().x(), screen->geometry().y());
	m_presentationWindow->resize(screen->geometry().width(), screen->geometry().height());
	m_presentationWindow->showFullScreen();
	raise();
}

void b3m::gui::PresentationManagementWindow::setNewSlide(QWidget* i_newSlide)
{
	if(m_presentationWindow){ m_presentationWindow->hide(); }
	m_presentationWindow = i_newSlide;
	initializeScreen();
}

void b3m::gui::PresentationManagementWindow::addNewSlide(SlideSelector& i_slide)
{
	m_slides.push_back(&i_slide);
	initializeSlide(i_slide);
}

void b3m::gui::PresentationManagementWindow::initializeSlide(SlideSelector& i_slide)
{
	m_ui->verticalLayout->insertWidget(1+m_slides.indexOf(&i_slide), &i_slide);
	connect(&i_slide, &b3m::gui::presentation::SlideSelector::newSlide, this, &PresentationManagementWindow::setNewSlide);
	connect(&i_slide, &b3m::gui::presentation::SlideSelector::newSlide, [this, &i_slide](){
		std::ranges::for_each(m_slides, [&i_slide](auto* const slide){
			if(slide){
				if(slide != &i_slide){ slide->setEnabled(true); }
				else{ slide->setEnabled(false); }
			}});
		m_curSlide = &i_slide;
	});
	connect(this, &PresentationManagementWindow::slidesVisible, &i_slide, &b3m::gui::presentation::SlideSelector::setEnabled);
	//TODO set somewhere general if slides are currently visible
	if(m_ui->upLeftButton->isEnabled())
	{
		i_slide.setEnabled(true);
	}
}


//END OF FILE --------------------------------------------------------------------------------------