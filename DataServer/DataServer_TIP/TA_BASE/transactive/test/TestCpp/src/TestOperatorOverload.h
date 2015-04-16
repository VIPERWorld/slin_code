#ifndef  __CLASS_TEST_OPERATOR_OVERLOAD__HH__
#define  __CLASS_TEST_OPERATOR_OVERLOAD__HH__

#include <iostream>
#include <string>
#include <stdio.h>
#include <typeinfo>



	/*
	�����������  +,-,*,/,%,++,--;
	λ���������: &,|,~,^,<<,>>;
	�߼������: !,&&,||;
	�Ƚ��������<,>, >=,<=,==,!=
	��ֵ�����: =,+=,-=,*=,/=,%=,&=,!=,^=,<<=,>>=;
	���������: [], (), ->, , new, delete, new[], delete[],->*.
	�������������������:
	. .*  :: ?:

	*/

class CTestOperatorOverload
{
private:
	double shibu;
	double xubu;
public:
	CTestOperatorOverload();
	CTestOperatorOverload(double shibuValue, double xubuValue);
	~CTestOperatorOverload();

public:
	CTestOperatorOverload operator+(const CTestOperatorOverload& object);
	CTestOperatorOverload operator-(const CTestOperatorOverload& object);
	CTestOperatorOverload operator*(const CTestOperatorOverload& object);
	CTestOperatorOverload operator/(const CTestOperatorOverload& object);

	friend void do_print(const CTestOperatorOverload& object);

public:
	void operator++()//����һԪ����
	{
		int a = 1;
	}
	void operator++(int)//���Ƕ�Ԫ����
	{
		int a = 1;
	}
};


#endif//__CLASS_TEST_OPERATOR_OVERLOAD__HH__