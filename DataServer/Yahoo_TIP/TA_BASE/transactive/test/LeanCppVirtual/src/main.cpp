//http://blog.csdn.net/russell_tao/article/details/7167929
#include <iostream>
#include <string>

#include <iostream>
using namespace std;

class Father
{
public:
	Father()
	{
		m_fMember=1;
	}
	virtual ~Father() 
	{

	}

public:
	void testFunc()
	{
		cout<<"Father testFunc "<<m_fMember<<endl;
	}
	virtual void testVFunc()
	{
		cout<<"Father testVFunc "<<m_fMember<<endl;
	}
public:
	int m_fMember;
};

class Child : public Father
{
public:
	int m_cMember;
public:
	Child()
	{
		m_cMember=2;
	}
	virtual ~Child()
	{

	}
public:
	virtual void testVFunc()
	{
		cout<<"Child testVFunc "<<m_cMember<<":"<<m_fMember<<endl;
	}
	void testFunc()
	{
		cout<<"Child testFunc "<<m_cMember<<":"<<m_fMember<<endl;
	}
	void testNFunc()
	{
		cout<<"Child testNFunc "<<m_cMember<<":"<<m_fMember<<endl;
	}
};


int main()
{
	Father* pRealFather = new Father();
	Child* pFalseChild = (Child*)pRealFather;
	Father* pFalseFather = new Child();

	/*
	����main��������õ����test*Func�����ɣ������о�̬�Ķ�̬��Ҳ�ж�̬�Ķ�̬�������Ǿ�̬�ģ������Ƕ�̬�ġ����½���C++����������ô�γ���������ġ�
	���Կ�������1��3��testFunc���ã������Ѿ��ڱ�������Ļ�������ж�����
	��������Ѿ�������ͬһ��API������ʵ�֣�����Ǳ����ڵĶ�̬

��2��4��testVFunc������Ȼ���������Ժ�Ҳ��֪���Ժ󾿾��ǵ���Father����Child��testVFuncʵ�֣�
ֱ������ʱ���õ�CPU�Ĵ������ָ���ˣ���֪�����ָ�뾿��ָ��Father����Child��testVFuncʵ�֡�����������ڵĶ�̬�ˡ�
	
	���m_fMember��Father�Ĺ��캯����ʼ��Ϊ1����m_cMember�Ѿ��ڴ�Խ���ˣ�û����32λ�����ϣ�Father����ֻ��8���ֽڣ���Child������12���ֽڣ����ʵ�m_cMember���ǵ�9-12���ֽ�ת���ɵ�int���͡�ͨ�����������ڴ涼��ȫ0�ģ����ԣ�m_cMember��0�����������Child testFunc 0:1��
	
	Ȼ��������testVFunc�ˣ����ִ�и��໹������ģ��Ǹ���ģ���Ϊ���������Father������new������ʱ��Father�Ĺ��캯�����vptlָ��ָ���Լ���testVFuncʵ��Ӵ�����Խ���ִ��C++����
	*/
	pFalseFather->testFunc();//1//Father testFunc 1
	pFalseFather->testVFunc();//2//child

	pFalseChild->testFunc();//3//Child testFunc -33333:1
	pFalseChild->testVFunc();//4//father	
	pFalseChild->testNFunc();//5//child	

	return 0;
}


//int main(void)
//int main()
//int main(int argc, char *argv[])
// int main(int argc, char *argv[])
// {
// 	int nFunRes = 0;
// 
// 	return nFunRes;
// }




