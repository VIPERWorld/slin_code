#include "MyString.h"

CMyString::CMyString( const char* str /*= NULL*/ )
{
	m_pData = NULL;
	if (NULL == str)
	{
		m_pData = new char[1];
		(*m_pData) = '\0';
	}
	else
	{
		int nLength = 0;
		nLength = strlen(str);
		m_pData = new char[nLength + 1];
		strcpy(m_pData, str);//
	}
}
/*
��Ϊ�������캯���Ƿ��ڱ����������ģ�
�����еĺ������Է��������Ķ�������г�Ա����Ȼ����˽�г�Ա�ˡ�
���ò�������Ҳ��String��ģ�����û����

���⣨֪ʶ�㣩������ 
a�� ��C++����ĳ�Ա�����У�����ֱ�ӷ��ʸ���Ķ����˽�г�Ա������ 
b�� ����ĳ�Ա�����п��Է���ͬ����ʵ����˽�б����� 
c�� �������캯�������ֱ�ӷ�������һ��ͬ��������ã���˽�г�Ա�� 
d�� ��ĳ�Ա��������ֱ�ӷ�����Ϊ�������ͬ���Ͷ����˽�г�Ա�� 
*/
CMyString::CMyString( const CMyString& other )
{
	int nLength = 0;
	nLength = strlen(other.m_pData);
	m_pData = NULL;
	m_pData = new char[nLength + 1];
	strcpy(m_pData, other.m_pData);//
}

CMyString::~CMyString()
{
	if (NULL != m_pData)
	{
		//����m_pData���ڲ��������ͣ�Ҳ����д��delete m_pData;//malloc/free new/delete
		delete[] m_pData;
		m_pData = NULL;

	}
}

CMyString& CMyString::operator=( const CMyString& other )
{
	//����Ը�ֵ
	if (this == &other)
	{
		return *this;
	}
	//free memory first
	if (NULL != m_pData)
	{
		delete[] m_pData;
		m_pData = NULL;
	}

	int nLength = 0;
	nLength = strlen(other.m_pData);
	m_pData = NULL;
	m_pData = new char[nLength + 1];
	strcpy(m_pData, other.m_pData);//
	return *this;
}

