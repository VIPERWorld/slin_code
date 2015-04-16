#include <stdio.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  

/*
socket����API.cpp
htons();//��short���͵�ֵ�������ֽ���ת��Ϊ�����ֽ���
inet_addr();//��IP��ַ�ַ���ת��Ϊlong���͵������ֽ���
gethostbyname();//������������Ӧ��IP��ַ
inet_ntoa();//��long���͵������ֽ���ת����IP��ַ�ַ���
*/

int main(int argc, char *argv[])  
{  
	int client_sockfd;  
	int len;  
	struct sockaddr_in remote_addr; //�������������ַ�ṹ��  
	int sin_size;  
	char buf[BUFSIZ];  //���ݴ��͵Ļ�����  
	memset(&remote_addr,0,sizeof(remote_addr)); //���ݳ�ʼ��--����  
	remote_addr.sin_family=AF_INET; //����ΪIPͨ��  
	remote_addr.sin_addr.s_addr=inet_addr("127.0.0.1");//������IP��ַ  
	remote_addr.sin_port=htons(8000); //�������˿ں�  

	/*�����ͻ����׽���--IPv4Э�飬����������ͨ�ţ�UDPЭ��*/  
	if((client_sockfd=socket(PF_INET,SOCK_DGRAM,0))<0)  
	{    
		perror("socket");  
		return 1;  
	}  
	strcpy(buf,"This is a test message");  
	printf("sending: '%s'\n",buf);  
	sin_size=sizeof(struct sockaddr_in);  

	/*��������������ݰ�*/  
	if((len=sendto(client_sockfd,buf,strlen(buf),0,(struct sockaddr *)&remote_addr,sizeof(struct sockaddr)))<0)  
	{  
		perror("recvfrom");   
		return 1;  
	}  
	close(client_sockfd);  
	return 0;  
}