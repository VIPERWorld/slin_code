#ifndef  __CLASS_MY_CLASS_PROTECTED_HH__
#define  __CLASS_MY_CLASS_PROTECTED_HH__



#include <iostream>
#include <string>

class CMyClassProtectedA
{
public:
	CMyClassProtectedA(int nValue):m_nValue(nValue)
	{

	}
	~CMyClassProtectedA()
	{

	}
protected:
	int m_nValue;
};
class CMyClassProtectedB : public CMyClassProtectedA
{
public:
	CMyClassProtectedB(int nValue) : CMyClassProtectedA(nValue)
	{

	}
	~CMyClassProtectedB()
	{

	}
	//void fb(CMyClassProtectedA  &a) 
	//{
	//	std::cout<<a.m_nValue<<std::endl;//error C2248: 'CMyClassProtectedA::m_nValue' : cannot access protected member declared in class 'CMyClassProtectedA'
	//}
	void fb(CMyClassProtectedB  &b) 
	{
		std::cout<<b.m_nValue<<std::endl;//error C2248: 'CMyClassProtectedA::m_nValue' : cannot access protected member declared in class 'CMyClassProtectedA'
	}
};
#endif //__CLASS_MY_CLASS_PROTECTED_HH__

/*
C++�������Ȩ�޿��ƣ�
��һ��private, public, protected ���ʱ�ŵķ��ʷ�Χ����û�м̳е�����£�
private��
ֻ����1.�����еĺ�����2.����Ԫ�������ʡ�
���ܱ��κ��������ʣ�����Ķ���Ҳ���ܷ��ʡ�
protected��
���Ա�1.�����еĺ�����2.����ĺ������Լ�3.����Ԫ�������ʡ�
�����ܱ�����Ķ�����ʡ�
public��
���Ա�1.�����еĺ�����2.����ĺ�����3.����Ԫ�������ʣ�Ҳ������4.����Ķ�����ʡ�
ע����Ԫ��������3�֣���Ϊ��Ԫ����ͨ�ķǳ�Ա��������Ϊ��Ԫ��������ĳ�Ա��������Ϊ��Ԫ���е����г�Ա������
�ڶ�����ļ̳к󷽷����Ա仯������������£�
private �����ǲ��ܹ����̳еģ�protected�̳к�private�̳��ܽ��ͷ���Ȩ�ޡ�
ʹ��private�̳У������protected��public�����������б�Ϊprivate��
ʹ��protected�̳У������protected��public�����������б�Ϊprotected��
ʹ��public�̳У������е�protected��public���Բ������ı�; 
������ʾ�� 
public:        protected:       private:
public�̳�          public        protected        ������ 
protected�̳�       protected     protected        ������ 
private�̳�         private       private          ������ 


class A
{
public:
A(int i) : a(i){}
protected:
int a;
};
class B : public A
{
public:
B(int i) : A(i) {}
void fb(A  &a) {cout<<a.a<<endl;}
};
����������������ڶ��и�Ϊ
void fb(B  &a) {cout<<a.a<<endl;}
��������ж�û���⣺
��������ֻ�ܱ������еķ���������������ʣ����ܱ�����ľ��������ʡ�a����A�ı������ͳ�Ա���ܱ�A�еķ��������������ʣ��ܱ�B����ʣ����ܱ���A�ľ������A a���ʡ�
һ����ı�����Ա��˽�г�Աֻ�ܱ�����ĳ�Ա������������Ԫ���������ʣ��ⲿ���벻�ܷ��ʣ�B���еĺ���fb����A���еı�����Ա����a��˵���ⲿ���벻��ͨ������Ķ���ֱ�ӷ��ʣ�����B�๫�м̳���A�࣬a��A�����Ǳ�����Ա������B����Ҳ�Ǳ�����Ա�����B���еĺ������Է����Լ��ı�����Ա��
*/

