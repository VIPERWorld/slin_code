#include <iostream>
#include "Person.h"


struct CPersonData  // ����˽�����ݳ�Ա����
{
	std::string mszName; // ����
	bool mbSex;    // �Ա�
	int mnAge;     // ����
};

// constructor
CPerson::CPerson ()
{
	d = new CPersonData;
};

// destructor
CPerson::~CPerson ()
{
	delete d;
};

void CPerson::setAge(const int age)
{
	if (age != d->mnAge)
		d->mnAge = age;
}

int CPerson::getAge()
{
	return d->mnAge;
}