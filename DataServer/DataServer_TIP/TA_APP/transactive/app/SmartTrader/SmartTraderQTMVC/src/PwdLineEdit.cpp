#include "PwdLineEdit.h"
/*
�Ѻõ���ʾ�û����Ҳ��ɸ��ơ�ճ����ʵ�����������������
�����û���¼�����ʱ���������õ�����������е�һЩ����ҲҪ������ͨ�������ͬ����������ȫѡ�����ơ�ճ�������Ҽ��˵��ȡ��������벻�ɼ��ȹ���
*/


CPwdLineEdit::CPwdLineEdit(QWidget *parent) :
QLineEdit(parent)
{
	//�������Ҽ��˵�
	this->setContextMenuPolicy(Qt::NoContextMenu);
	//����������ʾ
	this->setPlaceholderText(QString("PassWord"));
	//������������
	this->setEchoMode(QLineEdit::Password);
	//�����������ʽ
	this->setStyleSheet("QLineEdit{border-width: 1px; border-radius: 4px; font-size:12px; color: black; border:1px solid gray;}"
		"QLineEdit:hover{border-width: 1px; border-radius: 4px; font-size:12px; color: black; border:1px solid rgb(70, 200, 50);}");
	//������󳤶�16λ
	this->setMaxLength(16);
}

CPwdLineEdit::~CPwdLineEdit()
{

}

//���������ȫѡ�����ơ�ճ������
void CPwdLineEdit::keyPressEvent(QKeyEvent *event)
{
	if(event->matches(QKeySequence::SelectAll))
	{   
		return ;   
	}
	else if(event->matches(QKeySequence::Copy))
	{   
		return ;   
	}
	else if(event->matches(QKeySequence::Paste))
	{   
		return ;   
	}
	else
	{
		QLineEdit::keyPressEvent(event);
	}
} 


//��Ҫ�������λ���������ʱ�����ƶ�
void CPwdLineEdit::mouseMoveEvent(QMouseEvent *event)
{
	return ;
}