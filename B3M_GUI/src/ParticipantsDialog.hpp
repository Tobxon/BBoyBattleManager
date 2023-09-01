//--------------------------------------------------------------------------------------------------
/**
 * \brief ParticipantsDialog is used to input participant which further can be registered to 
 *        tournaments and be challengers in battles.
 *
 */

#ifndef B3M_GUI_PARTICIPANTS_DIALOG_HPP_
#define B3M_GUI_PARTICIPANTS_DIALOG_HPP_


//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//Qt
#include <QWidget>
#include <QAbstractTableModel>

#include <ui_ParticipantsDialog.h>

//b3m
import b3m.common;
import b3m.database;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m::gui
{



//ParticipantsDialog -------------------------------------------------------------------------------
class ParticipantsDialog : public QWidget
{
	Q_OBJECT;

public:
	explicit ParticipantsDialog(b3m::database::ParticipantsDepot&, QWidget* = nullptr);
	~ParticipantsDialog() override;

private:
	Ui::ParticipantsDialog* m_ui;
	QAbstractTableModel* m_model;
};


//ParticipantsDialogModel --------------------------------------------------------------------------
class ParticipantsDialogModel : public QAbstractTableModel
{
	Q_OBJECT;

	static const inline QString nameAttribute{ QString::fromStdString(b3m::common::nameAttribute) };

public:
	explicit ParticipantsDialogModel(b3m::database::ParticipantsDepot&, QObject* parent = nullptr);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

signals:
	void newParticipant(const b3m::common::Participant&, const b3m::common::ParticipantAttributes& = {});
	void participantUpdated(const b3m::common::Participant&, const b3m::common::Attribute&, const std::string&);

private:
	using participantIndex = std::size_t;
	using attributeIndex = std::size_t;

	std::map< attributeIndex, QString > m_participantAttributeTitles;
	std::map< participantIndex, std::map< attributeIndex, QString >> m_participantsData;

	b3m::database::ParticipantsDepot* m_participantsStorage{ nullptr };
};



} //namespace b3m::gui


#endif //B3M_GUI_PARTICIPANTS_DIALOG_HPP_
//END OF FILE --------------------------------------------------------------------------------------