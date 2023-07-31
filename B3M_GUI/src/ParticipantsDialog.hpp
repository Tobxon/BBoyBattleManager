//--------------------------------------------------------------------------------------------------
/**
 * \brief ParticipantsDialog is used to input participant which further can be registered to 
 *        tournaments and be challengers in battles.
 *
 */


#ifndef B3M_GUI__PARTICIPANTS_DIALOG_HPP__
#define B3M_GUI__PARTICIPANTS_DIALOG_HPP__

//--------------------------------------------------------------------------------------------------
//------ Dependencies                                                                         ------
//--------------------------------------------------------------------------------------------------

//Qt
#include <QWidget>
#include <QAbstractTableModel>

#include <ui_ParticipantsDialog.h>

//b3m
import b3m.database;


//--------------------------------------------------------------------------------------------------
//------ Declarations                                                                         ------
//--------------------------------------------------------------------------------------------------
namespace b3m
{
namespace gui
{



using ParticipantsContainer = b3m::database::ParticipantsDepot;

//ParticipantsDialog -------------------------------------------------------------------------------
class ParticipantsDialog : public QWidget
{
	Q_OBJECT;

public:
	explicit ParticipantsDialog(ParticipantsContainer&, QWidget* const = nullptr);
	~ParticipantsDialog();

private:
	Ui::ParticipantsDialog* m_ui;
	QAbstractTableModel* m_model;
};


//ParticipantsDialogModel --------------------------------------------------------------------------
class ParticipantsDialogModel : public QAbstractTableModel
{
	Q_OBJECT;

public:
	explicit ParticipantsDialogModel(ParticipantsContainer&, QObject* parent = nullptr);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    using participantIndex = std::size_t;
    using attributeIndex = std::size_t;

    std::map< attributeIndex, QString > m_participantAttributeTitles;
    std::map< participantIndex, std::map< attributeIndex, QString >> m_participantsData;

    ParticipantsContainer* m_participantContainer{nullptr};
};



} //gui
} //b3m


#endif //B3M_GUI__PARTICIPANTS_DIALOG_HPP__
 //END OF FILE --------------------------------------------------------------------------------------