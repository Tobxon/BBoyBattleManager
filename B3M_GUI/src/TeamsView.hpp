//--------------------------------------------------------------------------------------------------
/**
 * \brief TeamsView is a QWidget to list the currently registered teams. Meant to be used as a
 *        visual feedback to the user to check if a tournament can be started.
 *
 */


#ifndef B3M_GUI_TEAMS_VIEW_HPP_
#define B3M_GUI_TEAMS_VIEW_HPP_

//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//Qt
#include <QListView>
#include <QAbstractListModel>
#include <QList>
#include <QString>

//b3m
import b3m.database;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m::gui
{



using b3m::database::ParticipantsDepot;

class TeamsView : public QListView
{
	Q_OBJECT;

public:
	explicit TeamsView(ParticipantsDepot&, QWidget* = nullptr);

private:
	QAbstractListModel* m_model;
};


class TeamsModel : public QAbstractListModel
{
	Q_OBJECT;

public:
	explicit TeamsModel(ParticipantsDepot&, QObject* = nullptr);

	int rowCount(const QModelIndex& parent = {}) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
//	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
	using teams_t = QList<QString>;

	teams_t m_teams;
	b3m::database::TeamsCollector<teams_t> m_teamsSource;
};



} //namespace b3m::gui


#endif //B3M_GUI_TEAMS_VIEW_HPP_
//END OF FILE --------------------------------------------------------------------------------------