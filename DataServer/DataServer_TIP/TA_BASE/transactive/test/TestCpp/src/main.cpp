#include <iostream>
#include <string>
#include <stdio.h>

#include "TestConstMutable.h"

void testAddress()
{
	unsigned int a = 0xFFFFFFF7;
	unsigned char i = (unsigned char)a;
	char* b = (char*)&a;

	//int 4B
	//1B=8bit
	//4B=32bit
	//int a=2                       00000000 00000000 00000000 00000010

	//unsigned int a = 0xFFFFFFF7   11111111 11111111 11111111 11110111
	//

	/*
	���˽��ڴ���뷽ʽǰ���Ƚ��ܼ�����Ĵ洢��ʽ��Big Endian��Little Endian��
	Big Endian   �����ݵĸ�λ�ڵ͵�ַ����λ�ڸߵ�ַ�����Ұ�����ֽڵĵ�ַ��Ϊ�������׵�ַ
	Little Endian �����ݵĸ�λ�ڸߵ�ַ�����ݵĵ�λ�ڵ͵�ַ�����Ұ�����ֽڵĵ�ַ��Ϊ�����׵�ַ��
	��ʵ�У�ĳЩ����RISC(����ָ�)��cpu����SPARC��PowerPC�ȣ�����Big Endian��
	��Intelϵ��cpu����Little Endian�������Ҫ֪���Լ��ĵ�����ʲô�洢��ʽֻ��Ҫ�������´��룺
	*/
	printf("\n%08x, %08x\n", i, *b);



	char ch[]={0x12,0x34,0x56,0x78};
	int* p=(int*)ch;
	std::cout<<std::hex<<*p<<std::endl;//�����78563412��˵���� Little Endian,�����12345678������Big Endian


}

void testDuiQi()
{
	/*
	http://blog.csdn.net/tengweitw/article/details/8913566

	��Ȼ���룺���һ���������ڴ��ַ����λ�����ֽڳ��ȵ������������ͱ�������Ȼ����
	���ڱ�׼�������ͣ����ĵ�ַֻҪ�����ĳ��ȵ������������Ǳ�׼�������Ͱ������ԭ����룺
	���� �����ջ����������Ͷ��룬ֻҪ��һ������������ȻҲ�Ͷ��롣 
	���� ����������ĳ��������������Ͷ��롣 
	�ṹ�壺 �ṹ����ÿ���������Ͷ�Ҫ���롣        

	�ֽڶ���ĺô���
	��  �ֽڶ���ĸ���ԭ������CPU�������ݵ�Ч�����⡣ѧ��΢��ԭ��Ķ�֪�������ֺͷǹ����֣�
	   8086cpu���ʹ�����ֻҪһ�����ڣ������ʷǹ�������Ҫ�������ڡ�
	   ������ԭ��Ҳ��һ���ģ�ֻ����������32λ�Ĳ���ϵͳ�����һ�η���4�ֽڣ�
	   ��8086��16λ�ģ�һ��������2�ֽڡ�
	   �����������ͱ����ĵ�ַ����Ȼ���룬����Ϊ0x00000000��
	   ��CPU���ȡ����ֵ�Ļ���Ҫ����һ���ڴ棬һ��ֱ��ȡ��0x00000000-0x00000003��һ��int�ͣ�
	   ���������0x00000001�����һ�η���0x00000001��char�ͣ�
	   �ڶ���ȡ��0x00000002-0x00000003��short�ͣ���������0x00000004��char�ͣ�
	   Ȼ����ϵõ���Ҫ�����ݣ����������0x00000002��ַ�ϵĻ���Ҫ���������ڴ棬
	   ��һ��Ϊshort���ڶ���Ϊshort��Ȼ����ϵõ��������ݡ����������0x00000003��ַ�ϵĻ���
	   ������ 0x00000001���ơ� 
	   */
	/*
	�� 8086 / 8088 ϵͳ�еĴ洢������ 8 λ(һ���ֽ�)Ϊһ���洢�������ַ�洢��Ԫ��ַ�ġ�
	ÿһ���洢��Ψһ��һ����ַ������ʾ��
	һ���ּ�16λ������ռ��������������Ԫ����������Ԫ���и��Եĵ�ַ��
	���ڵ͵�ַ���ֽڵĵ�ַΪ����ֵĵ�ַ��
	�ڴ洢���У��κ�������ŵ������ֽڶ����Գ�Ϊһ���֡�
	��ż����ַ���ֳ�Ϊ�����֣�������ַ���ֳ�Ϊ�ǹ����֡�
	�ߵ�ַ���ֽ�Ϊ��λ�ֽڣ��͵�ַ���ֽ�Ϊ��λ�ֽڡ�
	��00000H��ַ�д��һ���� 2301H�� ��00000H��Ԫ�д��01H, 00001H��Ԫ�д��23H,
	��2301HΪ�����֣�����4523Ϊ�ǹ����֡�
	*/

	/*
	int a=0x0abcde11;//a b c �ĵ�ַ���μ�С  
	int b=0x012345678;  
	double c=0x0f23456789abcdef1;  
	char d=0x0fa;  

	char *ptr=(char*)&a;  
	printf("a bÿ���ֽڵ����ݣ�\n");  
	printf("  ��ַ  :����\n");  
	for(int i=0;i<8;i++)  
		printf("%x  :%x\n",ptr+3-i,*(ptr+3-i));//˵�������ǰ� little-endian�洢��  


	printf("\na b c d���׵�ַ�͵�ַ���ֽڳ��ȵ���ֵ��\n");  
	printf("a: %x :%d\n",&a,long(&a)%sizeof(a));//��������Կ��ɱ������ڴ��ַ������˳��ݼ���   
	printf("b: %x :%d\n",&b,long(&b)%sizeof(b));//������������һ��������������ڴ浥Ԫ  
	printf("c: %x :%d\n",&c,long(&c)%sizeof(c));  
	printf("d: %x :%d\n",&d,long(&d)%sizeof(d));  

	*/
}




void testSizeofClass()
{

	/*
	A�ǽṹ�壬Ĭ������£�Ϊ�˷���Խṹ���ڲ�Ԫ�صķ��ʺ͹���
	���ṹ���ڵ�Ԫ�صĳ��ȶ�С�ڴ�������λ����ʱ�򣬱��Խṹ�������������Ԫ��Ϊ���뵥λ���ṹ��ĳ���һ�����������Ԫ�ص���������
	����ṹ���ڴ��� ���ȴ��ڴ�����λ����Ԫ�أ���ô���Դ�������λ��Ϊ���뵥λ��
	CPU���Ż��������ԭ���������ģ�����n�ֽڵ�Ԫ��(n=2,4,8,...),�����׵�ַ�ܱ�n���������ܻ����õ����ܡ�
	*/
	struct 
	{
		short a1;
		short a2;
		short a3;
	}A;
	int nsizeofValue = sizeof(A);//6


	/*
	�������ǰ�8�ֽڱ߽��������
	���������Ѿ�����Ȼ�����ˣ�Ϊʲôperson�������Ҫ���7�ֽڣ�
	��Ϊ���㶨��person���͵�����ʱ����������7�ֽڣ�
	����˵�һ��Ԫ����������Ԫ�ؾͿ��ܲ�����Ȼ�����ˡ�
	*/
	class CPerson1  
	{  
		bool m_isMan;  
		float m_height;  
		bool m_isFat;  
		double m_weight;  
		unsigned char m_books;  
	};  
	int nSizeofPerson1 = 0;
	nSizeofPerson1 = sizeof(CPerson1);//32=4+4+8+8+8
	std::cout<<nSizeofPerson1<<std::endl;


	/*
	����ͨ��ʹ�ñ���ָ����������뷽ʽ��
	*/
#pragma pack(push,4)// ��4�ֽڱ߽����  
	class person2  
	{  
		bool m_isMan;  
		float m_height;  
		bool m_isFat;  
		double m_weight;  
		unsigned char m_books;  
	};  
	int nSizeofPerson2 = 0;
	nSizeofPerson2 = sizeof(person2);//24=4+4+4+8+4  
	std::cout<<nSizeofPerson2<<std::endl;
#pragma pack(pop)     

	/*
	���������֪�����ڴ�Ĵ�С�ʹ�ȡ��Ч������뷽ʽ�ͱ��������йأ���õķ����ǣ�
	�����ֽڴ�С�Ӵ�С���ζ��������Ա���������ܲ���С�ĳ�Ա���뷽ʽ��
	*/
	//���մ�С�����ֽڳ������������  
	class person4  
	{  
		bool m_isMan;  
		bool m_isFat;  
		unsigned char m_books;  
		float m_height;  
		double m_weight;  
	};  
	int nSizeofPerson4 = 0;
	nSizeofPerson4 = sizeof(person4);//16=1+1+1+1�ֽڵ����+4+8  
	std::cout<<nSizeofPerson4<<std::endl;



	//���մӴ�С�ֽڳ������������  
	class person3  
	{  
		double m_weight;  
		float m_height;  
		unsigned char m_books;  
		bool m_isMan;  
		bool m_isFat;  
	};  
	int nSizeofPerson3 = 0;
	nSizeofPerson3 = sizeof(person3);//16=8+4+1+1+1+1�ֽڵ����   
	std::cout<<nSizeofPerson3<<std::endl;
	/*
	��������Կ���������ռ�ڴ�һ���������ȶ��Ȳ�ͬ����С����ķ�ʽ�Ķ��뷽ʽ�������еĳ�Ա����������Ȼ����
	*/

#pragma pack(push,1)// ��4�ֽڱ߽����  
	class person5  
	{  
		bool m_isMan;  
		bool m_isFat;  
		unsigned char m_books;  
		float m_height;  
		double m_weight;  
	};  
	int nSizeofPerson5 = 0;
	nSizeofPerson5 = sizeof(person5);//15=1+1+1+4+8    
	std::cout<<nSizeofPerson5<<std::endl;

#pragma pack(pop)  
	/*
	������ĳ����У�double��ƫ����Ϊ1+1+1+4=7�����п��ܲ�����Ȼ����,������ò��ôӴ�С�ķ�ʽ�������Ա����
	*/
}


void testOperator()
{
	/*
	unsigned char a=0xA5;
	unsigned char b = ~a>>4+1;
	a 4 1  to int  then unsigned char to b
	~ > + > >>

	unsigned char b = ((~a)>>(4+1));
	vs2008  eax ��16λ�ļĴ���
	a    0xA5    0000 0000 1010 0101
	~a           1111 1111 0101 1010
	~a>>5        0000 0111 1111 1010 1 1010
	~a>>5        0000 0111 1111 1010 

	1111 1010
	0000 0111

	unsigned char b = 1111 1010
	b= 128+64+32+16+8+0+2+0 = 250
	*/
	unsigned char a=0xA5;
	unsigned char b = ~a>>4+1;
	printf("\n b=%d\n", b);//vs2008 250



	/*X 2~N   
	2     10       2-1       01       10&01=00     
	4    100       4-1       011       100&011=000
	8   1000       8-1      0111      1000&0111=0000
	16 10000       16-1    01111      10000&01111=00000
	X & (X - 1) == 0

	*/

	/*
	x & y ȡ��ͬ��λ�� 
	x ~ y ȡx��y�Ĳ�ͬλ �����൱�ڳ���2
	(x & y) + ((x ~ y) >> 1)
	*/


}

void testSizeofClassTest2()
{
	class CTestA
	{
	public:
		bool m_bValueA;//4
		int m_nValueInt;//4
		bool m_bValueB;//4
	};//12

	class CTestB
	{
	public:
		int m_nValueInt;//big first//4
		bool m_bValueA;//1
		bool m_bValueB;//3
	};//8

	int nSizeofValue = 0;
	nSizeofValue = sizeof(CTestA);
	printf("sizeof CTestA = %d \n", nSizeofValue);//vs2008 12 Byte   96bit

	nSizeofValue = sizeof(CTestB);
	printf("sizeof CTestB = %d \n", nSizeofValue);//vs2008 8 Byte    64bit


	/*
	//��̬�����Ǵ����ȫ���������� sizeof����ջ�з���Ĵ�С
	*/
	class A1
	{
	public:
		A1(){}
		~A1(){}
		int a;//4
		//static int b;// error C2246: 'testSizeofClassTest2::A1::b' : illegal static data member in locally defined class
	};//4
	nSizeofValue = sizeof(A1);
	printf("sizeof A1 = %d \n", nSizeofValue);//vs2008 4 Byte   32bit  

	class A2
	{
	public:
		int a;//4
		char c;//4
	};//8
	nSizeofValue = sizeof(A2);
	printf("sizeof A2 = %d \n", nSizeofValue);//vs2008 8 Byte   64bit  


	class A3
	{
	public:
		float a;//4
		char c;//4
	};//8
	nSizeofValue = sizeof(A3);
	printf("sizeof A3 = %d \n", nSizeofValue);//vs2008 8 Byte   64bit  


	class A4
	{
	public:
		float a;//4
		int b;//4
		char c;//4
	};//12
	nSizeofValue = sizeof(A4);
	printf("sizeof A4 = %d \n", nSizeofValue);//vs2008 12 Byte   96bit  


	class A5
	{
	public:
		double d;//8
		float a;//4
		int b;//4
		char c;//8 ������������
	};//24
	nSizeofValue = sizeof(A5);
	printf("sizeof A5 = %d \n", nSizeofValue);//vs2008 24 Byte  192bit  

	class A6
	{
	public:
		double d;//8
		float a;//4
		int b;//4
		char c;//4
		int nValue;//4
	};//24
	nSizeofValue = sizeof(A6);
	printf("sizeof A6 = %d \n", nSizeofValue);//vs2008 24 Byte  192bit  

	class A7
	{
	public:
		double d;//8
		float a;//4
		int b;//4
		char c;//8
		double fValue;//8
	};//32
	nSizeofValue = sizeof(A7);
	printf("sizeof A7 = %d \n", nSizeofValue);//vs2008 32 Byte  256bit  


}


void testFunStringArray()
{
	//To output "TrendMicroSoftUSCN"
	std::string strArri[] = {"Trend", "Micro", "Soft"};
	std::string* pStrArri = new std::string[2];
	double* pDouble = new double[10];
	pStrArri[0] = "US";
	pStrArri[1] = "CN";

	std::cout<<"sizeof(strArri)="<<sizeof(strArri)<<std::endl;//60
	std::cout<<"sizeof(std::string)="<<sizeof(std::string)<<std::endl;//20
	std::cout<<"sizeof(pStrArri)="<<sizeof(pStrArri)<<std::endl;//4
	std::cout<<"sizeof(*pStrArri)="<<sizeof(*pStrArri)<<std::endl;//20
	std::cout<<"sizeof(pDouble)="<<sizeof(pDouble)<<std::endl;//4
	std::cout<<"sizeof(*pDouble)="<<sizeof(*pDouble)<<std::endl;//8


	//sizeof(strArri)=12
	for (int nIndex = 0; nIndex < sizeof(strArri)/sizeof(std::string); nIndex++)
	{
		std::cout<<strArri[nIndex];
	}

	/*
	for (int nIndexj = 0; nIndexj < sizeof(pStrArri)/sizeof(std::string); nIndexj++)
	{
	std::cout<<pStrArri[nIndexj];
	}
	sizeof(pStrArri)=4=sizeof(std::string*)
	*/
	for (int nIndexj = 0; nIndexj < sizeof(*pStrArri)*2/sizeof(std::string); nIndexj++)
	{
		std::cout<<pStrArri[nIndexj];
	}	

	std::cout<<std::endl;
}


void testFunSizeofClassTest3()
{
	class Base
	{
	public:
		virtual void f(int nValue)
		{
			std::cout<<"Base::f(int nValue)"<<std::endl;
		}

		virtual void f(double fValue)
		{
			std::cout<<"Base::f(double fValue)"<<std::endl;
		}

		virtual void g(int nValue = 10)
		{
			std::cout<<"Base::g(int nValue = 10)"<<std::endl;
		}
		virtual void g2(int nValue = 10)
		{
			std::cout<<"Base::g2(int nValue = 10)"<<std::endl;
		}

		/*
		var[] �ȼ��� *var �Ѿ��˻�Ϊһ��ָ���ˣ���С��4
		*/
		int test(char var[])
		{
			return sizeof(var);
		}
	};

	class Derived : public Base
	{
	public:
		Derived()
		{
			std::cout<<"Derived-ctor"<<std::endl;
		}

		~Derived()
		{
			std::cout<<"Derived-dtor"<<std::endl;
		}


		virtual void g(int nValue = 20)
		{
			std::cout<<"Derived::g(int nValue = 20)"<<nValue<<std::endl;
		}
	};


	Base b;
	Derived d;

	Base* pb = new Derived();

	std::cout<<"sizeof(Base)="<<sizeof(Base)<<std::endl;//4  sizeof(ָ��)
	std::cout<<"sizeof(Derived)="<<sizeof(Derived)<<std::endl;//4  sizeof(ָ��)



	/*
	Ϊʲô��������ֽ���أ���ѧ�߿϶���ܷ���������a��b�����ǿ��࣬���Ĵ�СӦ��ΪΪ����Ϊʲô������������Ľ��Ϊ���أ���������Ǹղ���˵��ʵ������ԭ�򣨿���ͬ�����Ա�ʵ��������ÿ��ʵ�����ڴ��ж���һ����һ�޶��ĵ�ַ��Ϊ�˴ﵽ���Ŀ�ģ��������������һ�����������ļ�һ���ֽڣ�����������ʵ���������ڴ�õ��˶�һ�޶��ĵ�ַ������a��b�Ĵ�СΪ����
	����c������a������������������һ�����麯�����������麯����ԭ����һ��ָ���麯����ָ�루vptr�����ڣ���λ��ϵͳ�����ָ��Ĵ�СΪ�����ֽڣ��������õ�c��Ĵ�СΪ����
	��d�Ĵ�С���ó�ѧ���ɻ�ɣ���d������b��c���������ģ����Ĵ�СӦ��Ϊ����֮�ͣ���Ϊʲôȴ�ǣ������أ�������ΪΪ�����ʵ�����ڴ��еĴ�ȡЧ�ʣ���Ĵ�С������������ϵͳ��������������ȡ�ͽ��ķ������ĸ�����ı��������Ǹ���Ĵ�С��������d�Ĵ�СΪ�����ֽڣ�
	��Ȼ�ڲ�ͬ�ı������ϵõ��Ľ�����ܲ�ͬ���������ʵ��������ǳ�ѧ�ߣ��������Ƿ�Ϊ���࣬���ɱ�ʵ����������Ҳ�ɱ�ʵ��������ÿ����ʵ������һ����һ�޶��ĵ�ַ��
	*/
	class A
	{

	};//1 /*������ռ�Ŀռ�Ϊ1*/
	class A2
	{

	};//1
	class B : public A
	{

	};//1
	class C : public virtual B
	{

	};//4  /*��̳��漰�����ָ�룩*/

	class D :  public A
	{
		virtual void fun()=0;
	};//4  /*��̳��漰�����ָ�룩*/

	class E :  public A
	{
		virtual void fun(){}
	};//4  /*��̳��漰�����ָ�룩*/

	class F : public E, public A2
	{

	};//8

	std::cout<<"sizeof A="<<sizeof(A)<<std::endl;//1
	std::cout<<"sizeof A2="<<sizeof(A2)<<std::endl;//1
	std::cout<<"sizeof B="<<sizeof(B)<<std::endl;//1
	std::cout<<"sizeof C="<<sizeof(C)<<std::endl;//4
	std::cout<<"sizeof D="<<sizeof(D)<<std::endl;//4
	std::cout<<"sizeof E="<<sizeof(E)<<std::endl;//4
	std::cout<<"sizeof F="<<sizeof(F)<<std::endl;//8


	/*
	���������ͺ�Ĳ����ʲô��
	������������ͨ������ȿ��Լӿ��������е��ٶȣ���Ϊ����Ҫ�жϵ��ã�
	�ڱ����ʱ��������������ֱ�ӱ���Ƕ��Ŀ������С�����ֻ��һ���򵥵��滻��
	��������Ҫ���������ͼ�飬������������������ȵ����ơ�
	inline��ָǶ����룬�����ڵ��ú����ĵط�������ת�����ǰѴ���ֱ��д������ȥ��
	inlineһ�����ڣ�һ���������ϱ��ظ����ã� ����ֻ�м򵥵ļ��У��Һ����ڲ�����for,while,switch���

	inline fac(float nIndex) { return nIndex * nIndex;} //û��д����ֵ��
	printf("bb=%d", fac(8));   //����ʱ����ִ�� printf("bb=%d", 8*8);
	*/



}

void testPointerBase1()
{
	/*
	һ�����ݶ�����ڴ��ַ��Ϊ�����ݶ����ָ�롣
	ָ����Ա�ʾ�������ݶ�����򵥱��������顢����Ԫ�ء��ṹ�塢������
	���� ����ָ�룬����ָ�룬����ָ�룬thisָ�룬ָ�봫ֵ��ָ��ָ���ָ�롣
	*/
	/*
	ָ������õĲ��
	1���ǿ��������κ�����¶�����ʹ��ָ���ֵ�����á�һ�����ñ�������ָ��ĳЩ����
	��������ʹ��һ������������ָ��һ�����󣬵��Ǹñ�����ĳЩʱ��Ҳ���ܲ�ָ
	���κζ�����ʱ��Ӧ�ðѱ�������Ϊָ�룬��Ϊ��������Ը���ֵ���ñ������෴�����
	�����϶�ָ��һ���������������Ʋ��������Ϊ�գ���ʱ��Ϳ��԰ѱ�������Ϊ���á�
	������ָ���ֵ�����������ʵ��ζ��ʹ�����õĴ���Ч�ʱ�ʹ��ָ��Ҫ�ߡ�
	2���Ϸ���������ʹ������֮ǰ����Ҫ�������ĺϷ��ԡ��෴��ָ����Ӧ�����Ǳ����ԣ���ֹ��Ϊ�ա�
	3�����޸�����ָ����Ա����¸�ֵ��ָ����һ����ͬ�Ķ��󡣵�������������ָ���ڳ�ʼ��ʱ��ָ���Ķ���
	�Ժ��ܸı䣬����ָ���Ķ��������ݿ��Ըı䡣
	4��Ӧ������ ʹ��ָ�룺һ�����ǵ����ڲ�ָ���κζ���Ŀ��ܣ���������ָ��Ϊ�ա�
	������Ҫ�ܹ��ڲ�ͬ��ʱ��ָ��ͬ�Ķ��󣬸ı�ָ���ָ��
	�������ָ��һ��������һ��ָ��һ�������Ͳ���ı�ָ����ôӦ��ʹ�����á�
	*/
}

void testMemoryMalloc()
{
	float *p = NULL;
	while(1)
	{
		p = new float[10000000];
		std::cout<<"eat memory"<<std::endl;
		if ( p == NULL )
		{
			exit(1);
		}
	}
}

void testPointerSubtractionPointer()
{
	/*
	�ӷ� Addition 
	���� Subtraction 
	�˷� Multiplication 
	���� Division	
	*/


	int a[3];
	a[0] = 0;
	a[1] = 1;
	a[2] = 2;
	int *p, *q;
	p = a;//p = a[0]
	std::cout<<p<<'\n';
	std::cout<<*p<<'\n';
	q=&a[2];
	std::cout<<q<<'\n';
	std::cout<<*q<<'\n';
	std::cout<<a[q - p]<<'\n';
	std::cout<<a[*q - *p]<<'\n';

	/*
	p��ʵ�ʵ�ַ 0x22FF70
	q��ʵ�ʵ�ַ 0x22FF78
	0x22FF78 - 0x22FF70 = 0x000008
	q-p��ʵ��������  ��q�ĵ�ֵַ(0x22FF78) - p�ĵ�ֵַ(0x22FF70)) / (sizeof(int)) = 2

	*/
}

void testConstPointerConst()
{
	//����ָ��
	//void (*f) ();
	//��������ָ��
	//void* f();
	//const ָ��
	//const int* p;
	//ָ��const��ָ��
	//int* const p;
	//ָ��const��const ָ��
	//const int* const;

	/*
	������ָ�롱�͡�ָ�볣�������������
	��ʵ��һ�㽲��������ָ�롱��ָ��ĵ�ַ�ϵ������ǳ�����
	����ָ�볣������ָ��ĵ�ַ�ǳ�������ַ����������ǿ��Ա仯�ġ�
	char *str1={"Hello"};
	char *str2={"Hello World"};
	char * const ptr1 =str1 ;
	char szStrOne[] =  {"aaaaaa"};//ջ
	//ָ�볣������ָ�뱾���ǳ�����ָ��ĵ�ַ�����Ա仯,����ָ��ĵ�ַ����Ӧ�����ݿ��Ա仯
	ptr1 =szStrOne; //���� ��Ϊ����һ������ָ�룬�ı�ָ��ĵ�ַ��

	*ptr1 ='A';// ��ȷ ��Ϊָ��ĵ�ַ�������ǿ��Ա仯��


	const char *ptrTmp2 = str1;
	//����ָ�룭��ָ���ַ�����������ָ����ַ������ݲ��ܱ䣬����ָ��ĵ�ַ���Ա仯
	ptrTmp2=szStrOne;// ��ȷ ��Ϊָ��ĵ�ַ�ǿ��Ա仯��
	*ptrTmp2='A';// ���� ��Ϊָ��ĵ�ַ�������ǲ����Ա仯��


	���Ŵ������ĸ��򵥵����ӿ��Կ������ǲ�һ���ĵط��ѣ�������Ҫ����ע��һ�µĵط��ǣ�

	ָ�볣����������const ����* ��ָ����֮�� Type * const pointer ;

	����ָ���������const��������˵����֮ǰ const Type *pointer ;
	*/

	char *str1={"Hello"};//������
	char *str2={"Hello World"};
	char szStrOne[] =  {"aaaaaa"};//ջ
	char * const ptr1 =szStrOne ;
	//ָ�볣������ָ�뱾���ǳ�����ָ��ĵ�ַ�����Ա仯,����ָ��ĵ�ַ����Ӧ�����ݿ��Ա仯
	*ptr1 ='A';// ��ȷ ��Ϊָ��ĵ�ַ�������ǿ��Ա仯��
	printf("%c \n",*ptr1);

}


void testFunPointerTest1()
{
	/*
	Write in words the data type of the identifier involved in the following definitions.
	1. float(**def)[10];
	def�Ǹ�����ָ�룬��ָ�����һ��һά�����ָ�룬�����Ԫ�ض���float.
	2.double*(*gh)[10];
	gh��һ��ָ�룬��ָ��һ��һά���飬����Ԫ�ض���double*
	3.double(*f[10])();
	f��һ�����飬f��10��Ԫ�أ�Ԫ�ض��Ǻ�����ָ�룬ָ��ĺ���������û�в����ҷ���double�ĺ�����
	4.int*((*b)[10]);
	�͸�"int*(*b)[10]" ��һ���ģ���һά�����ָ�룬
	b��һ��ָ�룬��ָ��һ��һά���飬����Ԫ�ض���double*
	5. Long (*fun)(int)
	����ָ�룬ָ��ĺ��������ǲ���Ϊint,����long�ĺ�����
	6.int(*(F)(int, int))(int)
	F��һ��������ָ�룬ָ��ĺ�����������������int�������ҷ���һ������ָ��ĺ�����
	���صĺ���ָ��ָ����һ��int�������ҷ���int�ĺ�����
	*/
	{
		int v[2][10] = {{1,2,3,4,5,6,7,8,9,10},{11,12,13,14,15,16,17,18,19,20}};
		int (*a)[10] = v;//����ָ�� a��һ��ָ�룬ָ��һ��10��Ԫ�ص����飬����Ԫ��Ϊint
		/*
		a+1����aָ������ƶ�  1*sizeof(�����С)   40Byte
		*a+1 �������һ������ƶ�4���ֽڣ�
		*/

		std::cout<<"**a = "<<**a<<std::endl;//1
		std::cout<<"**(a+1) = "<<**(a+1)<<std::endl;//11
		std::cout<<"*(*a+1) = "<<*(*a+1)<<std::endl;//2
		std::cout<<"*(a[0]+1) = "<<*(a[0]+1)<<std::endl;//2
		std::cout<<"*(a[1]) = "<<*(a[1])<<std::endl;//11
	}
	/*
	int (*ptr)[] ��һ��ָ�����������ָ�롣
	int *ptr[] ��ָ�����飬 ptr[]�������ǵ�ַ����ָ��λ�õ�ֵ����*ptr[0], *ptr[1]
	int *(ptr[]) �� int *ptr[] ��ͬ
	int ptr[] ��һ����������
	*/

	/*
	int *a[] ��ָ������ a��ָ�����飬��ָһ����������װ��ָ��
	int (*a)[] ��һ��ָ�����������ָ�롣
	*/

	{
		static int a[2] = {1, 2};
		int *ptr[5];//ָ������
		int p = 5;
		int p2 = 6;
		int *page = NULL;
		int *page2 = NULL;
		page = &p;
		page2 = &p2;
		ptr[0] = &p;
		ptr[1] = page2;
		std::cout<<"*ptr[0] = "<<*ptr[0]<<std::endl;//5
		std::cout<<"*page = "<<*page<<std::endl;//5
		std::cout<<"*ptr[1] = "<<*ptr[1]<<std::endl;//6

		//�����ö�ά����
		int Test[2][3] = {{1,2,3},{4,5,6}};
		//������һά����
		int Test2[3] = {1,2,3};
		page = &p;
		page2 = &p2;
		ptr[0] = &p;
		ptr[1] = page2;
		//int (*A)[3] = &Test[1];
		//����ָ��
		int (*AA) [3];
		int (*BB) [3];
		AA = &Test[1];
		BB = &Test2;
		std::cout<<"*page = "<<*page<<std::endl;//5
		std::cout<<"(*AA)[0] = "<<(*AA)[0]<<std::endl;//4
		std::cout<<"(*AA)[1] = "<<(*AA)[1]<<std::endl;//5
		std::cout<<"(*AA)[2] = "<<(*AA)[2]<<std::endl;//6
		std::cout<<"(*BB)[3] = "<<(*BB)[3]<<std::endl;//-858993460
	}

}

void testPointerTypes()
{
	/*
	�����������û��Ϊ�����������׼������ô������Ϊʲô����׼���أ�
	*/
	//һ��������
	//int a;//An interger
	//һ��ָ����������ָ��
	//int *a;//A pointer to an integer
	//һ��ָ��ָ���ָ�룬��ָ���ָ����ָ��һ��������
	//int **a;//A pointer to a pointer to an integer
	//һ����10��������������
	//int a[10];//An array of 10 integers
	//һ����10��ָ������飬��ָ����ָ��һ����������
	//int *a[10];//An array of 10 pointers to integers
	//һ��ָ����10�������������ָ��
	//int (*a)[10];//A pointer to an array of 10 integers
	//һ��ָ������ָ�룬�ú�����һ�����Ͳ���������һ��������
	//int (*a)(int);//A pointer to a function that takes an integer argument and returns an interger
	//һ����10��ָ������飬��ָ��ָ��һ���������ú�����һ�����Ͳ���������һ��������
	//int (*a[10])(int);//An array of 10 pointers to functions that take an integer argument
	//return an integer

	/*
	�������������ָ�룬�ټ�һ��&,�ͱ����˫ָ�룬�����˫ָ�����ָ��ά���飬
	��1���������������һ�У�ptrָ��a�ĵ�6��Ԫ��
	*/
}

void test_TestConstMutable()
{
	RunTest_CTestConstMutable runTest;
	RunTest_CTestConstMutable runTest2(runTest);
	runTest2 = runTest;
	runTest.do_Test();


}

void test_struct_Test()
{
	struct Test
	{
		Test(int) 
		{
	
		}
		
		Test()
		{

		}

		void fun()
		{

		}
	};

	Test a(1);
	a.fun();
	//Test b();//error
	//b.fun();//error C2228: left of '.fun' must have class/struct/union
	

}

void test_convert_type_printf()
{
	/*
	5 int  4Byte
	%f   double 8Byte  stack�ڴ����Խ��
	*/
	printf("%f\n", 5);//0.000000
	printf("%d\n", 5.01);//1889785610 һ������

	/*
	static_cast
	const_cast ȥ��const����
	dynamic_cast   ����ǿ��ת�������ܷ���NULL
	reinterpret_cast
	*/

	int firstNumber = 2;
	int secondNumber = 1;
	double resultR = static_cast<double>(firstNumber)/secondNumber;

	class CTestB
	{
	public:
		int m_iNum;
	};
	CTestB b0;
	b0.m_iNum = 100;
	const CTestB b1 = b0;//
	//b1.m_iNum = 100;//����ʧ�ܣ� m_iNum�ǳ������󣬲��ܶ��������޸�//error C3892: 'b1' : you cannot assign to a variable that is const
	const_cast<CTestB&>(b1).m_iNum = 200;//ok
	//��������ʽִ���κ����͵�ת��������static_cast��ʾ���
	int n = 9;
	double d = static_cast<double>(n);


}

void test_Virtual_fun_class()
{
	class A
	{
	public:
		//�麯�� ��̬����
		virtual void foo()
		{
			std::cout<<"A foo"<<std::endl;
		}
		void pp()
		{
			std::cout<<"A pp"<<std::endl;
		}
	};

	class B : public A
	{
	public:
		void foo()
		{
			std::cout<<"B foo"<<std::endl;
		}
		void pp()
		{
			std::cout<<"B pp"<<std::endl;
		}
		void FunctionB()
		{
			std::cout<<"B FunctionB"<<std::endl;
		}
	};

	B b;
	A* pa = &b;
	pa->foo();//���ڴ��ڶ�̬����˵���B::foo()
	pa->pp();//����A::pp()
	(dynamic_cast<B*>(pa))->FunctionB();
}

void test_pointer_int()
{
	int *pa = NULL;//0x00 00 00 00
	int *pb = pa + 15;//15 * sizeof(int) = 15 * 4 = 60   0x3C
	printf("\n %x \n", pb);//0x00 00 00 3C
}

void test_const_volatile_type()
{
	/*
	const��ζ�� ֻ��

	const int a;//a��һ���������� �����޸�ֵ��������
	int const a;//a��һ���������� �����޸�ֵ��������
	const int* a;//a��һ��ָ����������ָ�� �����������޸ģ�ָ����޸�
	int* const a;//a��һ��ָ���������ĳ�ָ��  ���������޸ģ�ָ�벻���޸�
	int const* a const;//a��һ��ָ���������ĳ�ָ��  �����������޸ģ�ָ�벻���޸�
	*/

	/*
	�ؼ���volatile
	һ������Ϊvolatile�ı�����˵��������ܻᱻ���벻���ĸı䣬
	�������������Ͳ���ȥ�������������ֵ�ˡ���ȷ��˵�����ǣ�
	�Ż������õ��������ʱ����ÿ�ζ�С�ĵ����¶�ȡ���������ֵ��
	������ʹ�ñ����ڼĴ�����ı��ݡ�
	���ӣ�
	->�����豸��Ӳ���Ĵ���(�� ״̬�Ĵ���).
	->һ���жϷ����ӳ����л���ʵ��ķ��Զ�����(Non-automatic variables)
	->���߳�Ӧ���б�����������ı���
	*/
	/*
	һ���������Լ���const����volatile�ģ�һ�����Ӿ���ֻ����״̬�Ĵ�����
	����volatile,��Ϊ�����ܱ����벻���ĸı䣻
	����const�ģ���Ϊ����Ӧ����ͼȥ�޸�����
	һ��ָ�������volatile,һ�������ǵ�һ���жϷ����ӳ����޸�һ��ָ��һ��buffer��ָ��ʱ
	*/

	/*
	Ҫ������һ���Ե�ַΪ 0x000067a9 �����ͱ�����ֵΪ0x0000aa66;
	
	int* ptr = NULL;
	ptr = (int *)0x000067a9;//typecastһ��������ǿ��ת��Ϊһ��ָ��
	*ptr = 0x0x0000aa66;

	*(int* const)(0x000067a9) = 0x0000aa66;
	*/
		
	/*
	�ؼ���static��������ʲô��
	��C�����У�static�Ĺؼ����������������ã�
	->��������static���������÷�ΧΪ�ú����壬��ͬ��auto�������ñ������ڴ�ֻ������һ�Σ������ֵ���´ε���ʱ��ά���ϴε�ֵ��
	->��ģ���ڵ�staticȫ�ֱ������Ա�ģ�������к������ʣ������ܱ�ģ���������������ʡ�
	->��ģ���ڵ�static����ֻ�ɱ���һģ���ڵ������������ã����������ʹ�÷�Χ����������������ģ���ڡ�
	->�����е�static��Ա����������������ӵ�У���������ж���ֻ��һ�ݿ�����
	->�����е�static��Ա����������������ӵ�У��������������thisָ�룬���ֻ�ܷ������static��Ա����
	*/

	/*
	static��������Ҫ������3����
	1����չ�����ڣ�
	2������������
	3��Ψһ�ԣ�
	*/
}

void test_Little_endian_Big_endian()
{
	/*
	Little_endian Сβ
	0x12 34 56 78
	�ڴ��ַ   ��ŵ�����
	0x4000     0x78
	0x4001     0x56
	0x4002     0x34
	0x4003     0x12

	Big_endian  ��β
	0x12 34 56 78
	�ڴ��ַ   ��ŵ�����
	0x4000     0x12
	0x4001     0x34
	0x4002     0x56
	0x4003     0x78
	*/
}


void test_dynamic_cast()
{
	class ClassA
	{
	public:
		//1
		virtual void foo()
		{
			std::cout<<"ClassA foo"<<std::endl;
		}
		void pp()
		{
			std::cout<<"ClassA pp"<<std::endl;
		}
	};

	class ClassB : public ClassA
	{
	public:
		void foo()
		{
			std::cout<<"ClassB foo"<<std::endl;
		}
		void pp()
		{
			std::cout<<"ClassB pp"<<std::endl;
		}
		void FunctionB()
		{
			std::cout<<"Excute FunctionB"<<std::endl;
		}
	};

	ClassA a;//use CLASSB b;
	ClassA* pa = &a;
	pa->foo();
	pa->pp();
	ClassB* pB = NULL;
	//2
	pB = NULL;
	//pB = (dynamic_cast<ClassB*>(pa))->FunctionB();
	pB = (dynamic_cast<ClassB*>(pa));//->FunctionB();
	pB->FunctionB();//ok   "Excute FunctionB"   not use any memberdata or virtual fun, not use this pointor
	/*��ΪFunctionB��pp�ĺ���δʹ���κγ�Ա���ݣ�Ҳ�����麯��������Ҫthisָ�룬Ҳ����Ҫ��̬�󶨣������������� */
	//4
	pB = NULL;
	//pB = (dynamic_cast<ClassB*>(pa))->pp();
	pB = (dynamic_cast<ClassB*>(pa));//->pp();
	pB->pp();//ok   "ClassB pp"
	(*pa).foo();//"ClassA foo"

	//3
	pB = NULL;
	//pB = (dynamic_cast<ClassB*>(pa))->foo();
	pB = (dynamic_cast<ClassB*>(pa));
	pB->foo();//error   vitrual table


}//test_dynamic_cast


//page 180
int main(int agrc, char** argv)
{

	// 	testAddress();
	// 	testDuiQi();
	// 	testSizeofClass();
	// 	testOperator();
	// 	testSizeofClassTest2();
	// 	testFunStringArray();
	// 	testFunSizeofClassTest3();
	//	testPointerSubtractionPointer();
	//	testConstPointerConst();
	//testFunPointerTest1();
	//test_TestConstMutable();
	//test_convert_type_printf();
	//test_pointer_int();
	test_dynamic_cast();

	return 0;
}




