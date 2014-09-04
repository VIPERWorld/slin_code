#ifndef __CLASS__CUSTOM_COLUMNS_DIALOG_H__
#define __CLASS__CUSTOM_COLUMNS_DIALOG_H__



#include <QtGui/QDialog>
#include <QtGui/QWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


class CCustomColumnsDialog : public QDialog
{
    Q_OBJECT

public:
    CCustomColumnsDialog(QWidget *parent = 0);
	~CCustomColumnsDialog();

public:
	void setupUi();
	void translateLanguage();
private:
	void _SetAllDataToListWidget(QListWidget* pListWidget, QStringList& strlstData);
	void _CreateConnect();
	QStringList _GetAllDataFormListWidget(QListWidget* pListWidget);

signals:	
	/*
	class: CCustomColumnsDialog
	signals:
	void signalModifySelectedColumns(QStringList lstAllAvailableColums, QStringList lstSelectedColumns);
	fun send signals: slotActionRemoveHotQuotesTriggered()

	class: CQuotesTableView
	public slots: 
	void slotModifySelectedColumns(QStringList lstAllAvailableColums, QStringList lstSelectedColumns);
	*/
	void signalModifySelectedColumns(QStringList lstAllAvailableColums, QStringList lstSelectedColumns);

private slots:
	/*
	class: QPushButton
	signals:
	void clicked(bool checked = false);
	fun send signals: m_pPushButton_Remove

	class: CCustomColumnsDialog
	private slots: 
	void slotPushButtonRemoveClick(bool checked = false);
	*/
	void slotPushButtonRemoveClick(bool checked = false);
	void slotPushButtonRemoveAllClick(bool checked = false);
	void slotPushButtonAddClick(bool checked = false);
	void slotPushButtonAddAllClick(bool checked = false);
	void slotPushButtonUpClick(bool checked = false);
	void slotPushButtonDownClick(bool checked = false);
	void slotPushButtonOKClick(bool checked = false);
	void slotPushButtonCancelClick(bool checked = false);
	void slotPushButtonDefaultClick(bool checked = false);



private:
	QVBoxLayout* m_pLayout_Main;
	QGroupBox* m_pGroupBox_ColumnConfiguation;
	QLabel* m_pLabel_AllAvailableColums;
	QListWidget* m_pListWidget_AllAvailableColums;
	QLabel* m_pLabel_SelectedColumns;
	QListWidget* m_pListWidget_SelectedColumns;

private:
	QPushButton* m_pPushButton_OK;//����
	QPushButton* m_pPushButton_Cancel;//ȡ��

	QPushButton* m_pPushButton_Add;//"Add";//���
	QPushButton* m_pPushButton_AddAll;//"Add All";//�������
	QPushButton* m_pPushButton_Remove;//"Remove";//�Ƴ�
	QPushButton* m_pPushButton_RemoveAll;//"Remove All";//�Ƴ�����
	QPushButton* m_pPushButton_Default;// = "Default";//�ָ�Ĭ��
	QPushButton* m_pPushButton_Up;// = "Up";//����
	QPushButton* m_pPushButton_Down;// = "Down";//����

};

//QT_END_NAMESPACE


#endif//__CLASS__CUSTOM_COLUMNS_DIALOG_H__
