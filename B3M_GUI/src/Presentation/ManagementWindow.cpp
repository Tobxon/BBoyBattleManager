//--------------------------------------------------------------------------------------------------
// For explanation see interface file (.ixx). (or header file if modules aren't working for it yet)


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------
#include "ManagementWindow.hpp"

//Qt
#include <QScreen>
#include <QGuiApplication>
#include <QPixmap>


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
	});
	connect(m_ui->lowRightButton, &QPushButton::clicked, [this](){
		m_presentationWindow->hide();
		emit slidesVisible(false);
	});

	connect(m_ui->upLeftButton, &QPushButton::clicked, [this](){
		const auto numOfScreens = QGuiApplication::screens().size();
		m_presentationWindowScreeIndex = (m_presentationWindowScreeIndex == 0) ? numOfScreens-1 : --m_presentationWindowScreeIndex%(numOfScreens);
		initializeScreen();
	});
	connect(m_ui->upRightButton, &QPushButton::clicked, [this](){
		m_presentationWindowScreeIndex = ++m_presentationWindowScreeIndex%(QGuiApplication::screens().size());
		initializeScreen();
	});
}

b3m::gui::PresentationManagementWindow::~PresentationManagementWindow()
{
	if(m_presentationWindow){ delete m_presentationWindow; }
	delete m_ui;
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
	delete m_presentationWindow;
	m_presentationWindow = i_newSlide;
	initializeScreen();
}


//END OF FILE --------------------------------------------------------------------------------------