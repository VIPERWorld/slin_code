#ifndef  __DEF__CLASS__PERSON_HH__
#define  __DEF__CLASS__PERSON_HH__

struct CPersonData; // ����˽�����ݳ�Ա����

class CPerson
{
public:
	CPerson ();   // constructor
	virtual ~CPerson ();  // destructor
public:
	void setAge(const int);
	int getAge();

protected:
	CPersonData* d;
};


#endif //__DEF__CLASS__PERSON_HH__




