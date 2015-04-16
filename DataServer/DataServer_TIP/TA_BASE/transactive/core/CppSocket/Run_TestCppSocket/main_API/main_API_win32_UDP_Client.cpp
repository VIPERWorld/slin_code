#include "stdafx.h"  
#include <stdio.h>  
#include <winsock2.h>  

#pragma comment(lib, "ws2_32.lib")   

int main(int argc, char* argv[])  
{  
	WORD socketVersion = MAKEWORD(2,2);  
	WSADATA wsaData;   
	if(WSAStartup(socketVersion, &wsaData) != 0)  
	{  
		return 0;  
	}  
	SOCKET sclient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);  

	sockaddr_in sin;  
	sin.sin_family = AF_INET;  
	sin.sin_port = htons(8888);  
	sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");  
	int len = sizeof(sin);  

	char * sendData = "���Կͻ��˵����ݰ�.\n";  
	sendto(sclient, sendData, strlen(sendData), 0, (sockaddr *)&sin, len);  

	char recvData[255];       
	int ret = recvfrom(sclient, recvData, 255, 0, (sockaddr *)&sin, &len);  
	if(ret > 0)  
	{  
		recvData[ret] = 0x00;  
		printf(recvData);  
	}  

	closesocket(sclient);  
	WSACleanup();  
	return 0;  
}  


/*
����Linux �� Windows Socket ������
1)ͷ�ļ� 
windows��winsock.h��winsock2.h
linux��netinet/in.h���󲿷ֶ����������unistd.h��close�������������sys/socket.h����in.h���Ѿ������ˣ�����ʡ�ˣ�

2)��ʼ��
windows����Ҫ��WSAStartup����Ws2_32.lib������Ҫ��#pragma comment(lib,"Ws2_32")����֪���������Ӹ�lib��
linux�²���Ҫ

3)�ر�socket
windows��closesocket(...)
linux��close(...)

4)����
windows��SOCKET
linux��int����ϲ����long��������֤��4byte����Ϊ-1����ϲ��д��0xFFFF��

5)��ȡ������ 
windows��getlasterror()/WSAGetLastError()
linux�£�δ�ܳɹ�ִ�е�socket�����᷵��-1�����������errno.h���ͻ�����errno����

6)���÷�����
windows��ioctlsocket()
linux��fcntl()����Ҫͷ�ļ�fcntl.h

7)send�������һ������
windows��һ������Ϊ0
linux���������ΪMSG_NOSIGNAL����������ã��ڷ��ͳ�����п��ܻᵼ�³����˳�

8)���뼶ʱ���ȡ
windows��GetTickCount()
linux��gettimeofday()

9)���߳� 
windows�°���process.h��ʹ��_beginthread��_endthread
linux�°���pthread.h��ʹ��pthread_create��pthread_exit

10)��IP����һ����ַ��sockaddr_in�Ľṹ������
windows��addr_var.sin_addr.S_un.S_addr
linux��addr_var.sin_addr.s_addr
����Winsock������Ǹ�32bit��S_addrҲ�м��������ϣ�Union������ʽ���������ڴ�ռ�ĳ�Ա������������������ʽ��ֵ������Linux��Socketû��������ϣ�����һ��32bit��s_addr���������ֵõ�����4��char��IP����ʽ������127һ����0һ����0һ����1һ�����ĸ�char����WinSock����ֱ����4��S_b����ֵ��S_addr�����Linux�£������ñ�������λ��һ��8bit�������£�����ӵķ�����ֵ��

11)�쳣����
linux�µ����ӶϿ����������ݵ�ʱ�򣬲���send()�ķ���ֵ���з�ӳ�����һ�����ϵͳ����һ���쳣��Ϣ�������������ϵͳ���BrokePipe��������˳���Ϊ�ˣ�send()���������һ������������MSG_NOSIGNAL����ֹsend()������ϵͳ�����쳣��Ϣ��

*/