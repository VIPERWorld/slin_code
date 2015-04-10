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
		std::cout<<"Father() set m_fMember="<<m_fMember<<std::endl;
	}
	virtual ~Father() 
	{
		std::cout<<"virtual ~Father() m_fMember="<<m_fMember<<std::endl;
	}

public:
	void testFunc()
	{
		std::cout<<"Father void testFunc() m_fMember="<<m_fMember<<std::endl;
	}
	virtual void testVFunc()//�麯����ָ�� 4
	{
		std::cout<<"Father virtual void testVFunc() m_fMember="<<m_fMember<<std::endl;
	}
public:
	int m_fMember;//4
};

class Child : public Father
{
public:
	int m_cMember;//4
public:
	Child()
	{
		m_cMember=2;
		std::cout<<"Child() set m_cMember="<<m_cMember<<std::endl;
	}
	virtual ~Child()
	{
		std::cout<<"virtual ~Child() m_cMember="<<m_cMember<<std::endl;
	}
public:
	virtual void testVFunc()
	{
		std::cout<<"Child() virtual void testVFunc() m_cMember="<<m_cMember<<std::endl;

	}
	void testFunc()
	{
		std::cout<<"Child() void testFunc() m_cMember="<<m_cMember<<std::endl;
	}
	void testNFunc()
	{
		std::cout<<"Child() void testNFunc() m_cMember="<<m_cMember<<std::endl;
	}
};


int main()
{

	/*
	����main��������õ����test*Func�����ɣ������о�̬�Ķ�̬��Ҳ�ж�̬�Ķ�̬�������Ǿ�̬�ģ������Ƕ�̬�ġ����½���C++����������ô�γ���������ġ�
	���Կ�������1��3��testFunc���ã������Ѿ��ڱ�������Ļ�������ж�����
	��������Ѿ�������ͬһ��API������ʵ�֣�����Ǳ����ڵĶ�̬

��2��4��testVFunc������Ȼ���������Ժ�Ҳ��֪���Ժ󾿾��ǵ���Father����Child��testVFuncʵ�֣�
ֱ������ʱ���õ�CPU�Ĵ������ָ���ˣ���֪�����ָ�뾿��ָ��Father����Child��testVFuncʵ�֡�����������ڵĶ�̬�ˡ�
	
	���m_fMember��Father�Ĺ��캯����ʼ��Ϊ1����m_cMember�Ѿ��ڴ�Խ���ˣ�û������32λ�����ϣ�Father����ֻ��8���ֽڣ���Child������12���ֽڣ����ʵ�m_cMember���ǵ�9-12���ֽ�ת���ɵ�int���͡�ͨ�����������ڴ涼��ȫ0�ģ����ԣ�m_cMember��0�����������Child testFunc 0:1��
	
	Ȼ��������testVFunc�ˣ����ִ�и��໹������ģ��Ǹ���ģ���Ϊ���������Father������new������ʱ��Father�Ĺ��캯�����vptlָ��ָ���Լ���testVFuncʵ��Ӵ�����Խ���ִ��C++����
	*/

	Father* pRealFather = new Father();
	Child* pFalseChild = (Child*)pRealFather;
	Father* pFalseFather = new Child();

	std::cout<<"sizeof(Father)="<<sizeof(Father)<<std::endl;//8
	std::cout<<"sizeof(Child)="<<sizeof(Child)<<std::endl;//12


	pFalseFather->testFunc();//1//Father void testFunc() m_fMember=1
	pFalseFather->testVFunc();//2//Child() virtual void testVFunc() m_cMember=2

	pFalseChild->testFunc();//3//Child() void testFunc() m_cMember=-33686019
	pFalseChild->testVFunc();//4//Father virtual void testVFunc() m_fMember=1	
	pFalseChild->testNFunc();//5//Child() void testNFunc() m_cMember=-33686019	
/*
Father() set m_fMember=1
Father() set m_fMember=1
Child() set m_cMember=2
sizeof(Father)=8
sizeof(Child)=12
Father void testFunc() m_fMember=1
Child() virtual void testVFunc() m_cMember=2
Child() void testFunc() m_cMember=-33686019
Father virtual void testVFunc() m_fMember=1
Child() void testNFunc() m_cMember=-33686019


*/
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



