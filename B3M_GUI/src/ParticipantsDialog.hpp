//--------------------------------------------------------------------------------------------------
/**
 * \brief ParticipantsDialog is used to input participant which further can be registered to 
 *        tournaments and be challengers in battles.
 *
 */


#ifndef B3M_GUI__PARTICIPANTS_DIGALOG_HPP__
#define B3M_GUI__PARTICIPANTS_DIGALOG_HPP__

//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

import b3m.database;

//std
#include <vector>

//Qt
#include <QWidget>
#include <QAbstractTableModel>

#include <ui_ParticipantsDialog.h>


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m
{
namespace gui
{



using participantsContainer = b3m::database::IParticipantsContainer;

class ParticipantsDialog : public QWidget
{
	Q_OBJECT;

public:
	explicit ParticipantsDialog(participantsContainer&, QWidget* const = nullptr);
	~ParticipantsDialog();

private:
	Ui::ParticipantsDialog* m_ui;
	QAbstractTableModel* m_model;
};

class ParticipantsDialogModel : public QAbstractTableModel
{
	Q_OBJECT;

	static inline const QString nameTitle{ "Name" };

public:
	explicit ParticipantsDialogModel(participantsContainer&, QObject* const parent = nullptr);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex&, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation, int role) const override;
	bool setData(const QModelIndex&, const QVariant&, int role = Qt::EditRole) override;
	Qt::ItemFlags flags(const QModelIndex&) const override;

private:
	participantsContainer* m_data;

	std::vector< QString > m_header;
};



} //gui
} //b3m


#endif //B3M_GUI__PARTICIPANTS_DIGALOG_HPP__
//END OF FILE --------------------------------------------------------------------------------------