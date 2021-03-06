#ifndef __CLASS__CLIENT_LOGIN_DIALOG_H__
#define __CLASS__CLIENT_LOGIN_DIALOG_H__


#include <QtCore/QString>

#include <QtGui/QMainWindow>
#include <QtGui/QDialog>


QT_BEGIN_NAMESPACE
class QFormLayout;
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QComboBox;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE



//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CClientLoginParam;
class CServerSettingDialog;
class CPwdLineEdit;

class CClientLoginDialog : public QDialog
{
    Q_OBJECT

public:
    CClientLoginDialog(QWidget *parent = 0);
	~CClientLoginDialog();

public:
	void setupUi();
	void translateLanguage();

public slots:
	void slotButtonSettingClicked(bool checked);
	void slotButtonLoginClicked(bool checked);
	void slotButtonCancelClicked( bool checked );

public slots:
	void slotServerInfoChanged(CClientLoginParam* pClientLoginParam);
	void slotLoginToServerResult(int nLoginResust);
private:
	void _CreateConnect();
private:
	CServerSettingDialog* m_pServerSettingDialog;
private:
	QString m_pComboBox_UserName_Value;
	QString m_pLineEdit_Password_Value;

private:
	CClientLoginParam* m_pClientLoginParam;
private:
	QLabel* m_pLabel_UserName;
	QComboBox* m_pComboBox_UserName;

	QLabel* m_pLabel_Password;
	CPwdLineEdit* m_pLineEdit_Password;

	QPushButton* m_pPushButtonSetting;
	QPushButton* m_pPushButtonLogin;
	QPushButton* m_pPushButtonCancle;
};

//QT_END_NAMESPACE


#endif//__CLASS__CLIENT_LOGIN_DIALOG_H__
