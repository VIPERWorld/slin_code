#ifndef __CLASS_MYSTRING_HH__
#define  __CLASS_MYSTRING_HH__

#include <iostream>
#include <string>

class CMyString
{
public:
	//��ͨ���캯��
	CMyString(const char* str = NULL);
	//�������캯��
	CMyString(const CMyString& other);
	//��������
	virtual ~CMyString();
public:
	//��ֵ����
	CMyString& operator=(const CMyString& other);
private:
	char* m_pData;
};



/*
��C++�е�����һ������ʱ��C++�ͻ�Ĭ�ϵ�Ϊ����ഴ��4��������
Ĭ�ϵĹ��캯���������������������캯�����Լ���ֵ��������
*/
class CEmpty
{
public:
	//Ĭ�ϵĹ��캯��
	CEmpty(){;}
	//Ĭ�ϵĿ������캯��
	CEmpty(const CEmpty& rhs){;}
	//Ĭ�ϵ���������
	virtual ~CEmpty(){;}
public:
	//Ĭ�ϵ� ��ֵ������
	CEmpty& operator=(const CEmpty& other){;}
	//ȡ��ַ
	CEmpty* operator&(){return this;}
	//ȡ��ַ��const 
	//����ֵ��const�� �����޸�
	//this ָ����const �����޸����Ա��ֵ Ҳ���ܵ��÷�const�ĳ�Ա����
	const CEmpty* operator&() const {return this;}
};


#endif //__CLASS_MYSTRING_HH__