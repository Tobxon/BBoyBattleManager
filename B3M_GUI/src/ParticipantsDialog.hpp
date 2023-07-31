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



class ParticipantsDialog : public QWidget
{
	Q_OBJECT;

public:
	explicit ParticipantsDialog(QWidget* const = nullptr);
	~ParticipantsDialog();

private:
	Ui::ParticipantsDialog* m_ui;
	QAbstractTableModel* m_model;
};

class ParticipantsDialogModel : public QAbstractTableModel
{
	Q_OBJECT;

public:
	explicit ParticipantsDialogModel(QObject* parent = nullptr);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

private:
    std::map< std::size_t, std::string > m_participantAttributeTitles;
    std::vector< std::map< std::size_t, QString >> m_participantsData;
};



} //gui
} //b3m


#endif //B3M_GUI__PARTICIPANTS_DIGALOG_HPP__
 //END OF FILE --------------------------------------------------------------------------------------