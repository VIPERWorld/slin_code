#include "core/CppSendEmailLib/src/MailSender.h"
#include "core/CppSendEmailLib/src/MailWrapper.h"
#include "core/CppSendEmailLib/src/Base64Helper.h"
#include "core/CppSendEmailLib/src/ErrorMessage.h"

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <winsock2.h>

//
NS_BEGIN(TA_Base_Core)

static const int MAX_BUFFER_SIZE = 255;


// Member functions of class MailSender
/////////////////////////////////////

MailSender::MailSender(const std::string server_name, 
                       const std::string user_name, 
                       const std::string user_pwd)
    : m_strServerName(server_name), m_strUserName(user_name), 
      m_strUserPwd(user_pwd), m_pMail(0)
{
    _ConnectToSmtpServer();

    _SendSmtpHello();

	if ( !user_name.empty() )
	{
		_SendSmtpLogin();
	}
}

MailSender::~MailSender()
{
    _SendSmtpQuit();
}

void MailSender::setMail(MailWrapper* mail)
{
    m_pMail = mail;
}

void MailSender::sendMail()
{
    if (!m_pMail)
        return;

    _SendEmailHeader();
    _SendEmailContent();
    _SendEmailEnd();
}

void MailSender::_ConnectToSmtpServer()
{
    struct hostent* host = gethostbyname(m_strServerName.c_str());
    if (host == 0)
    {
        throw std::exception("Get server infomation error");
    }

    m_nSocketHandle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = *(ULONG *)host->h_addr_list[0];
	server_addr.sin_port = ::htons(SERVICE_PORT);

    ::connect(m_nSocketHandle, (struct sockaddr *)&server_addr, sizeof(server_addr));
    _RcvResponseFromServer("220");
}

void MailSender::_SendSmtpHello()
{
    char local_host[MAX_BUFFER_SIZE];
	if (::gethostname(local_host, MAX_BUFFER_SIZE) != 0 )
    {
        throw std::exception("Get local host name error");
    }

    std::string msg;

    msg  = "HELO ";
    msg += std::string(local_host) + "\r\n";
    _SendRequestToServer(send_helo_cmd, msg);
    _RcvResponseFromServer("250");
}

void MailSender::_SendSmtpLogin()
{
    std::string msg;

    msg = "AUTH LOGIN\r\n";
    _SendRequestToServer(send_auth_cmd, msg);
    _RcvResponseFromServer("334");

    msg = Base64Helper::encode(m_strUserName) + "\r\n";
    _SendRequestToServer(send_username, msg);
    _RcvResponseFromServer("334");

    msg = Base64Helper::encode(m_strUserPwd) + "\r\n";
    _SendRequestToServer(send_password, msg);
    _RcvResponseFromServer("235");
}

void MailSender::_SendEmailHeader()
{
    std::string msg;

	//==========================================
    msg  = "MAIL FROM: ";
    msg += m_pMail->getSenderAddress() + "\r\n";
    _SendRequestToServer(send_mail_cmd, msg);
    _RcvResponseFromServer("250");

	//==========================================
    m_pMail->traverseReceiver();
    while ( m_pMail->hasMoreReceiver() )
    {
        msg  = "RCPT TO: ";
        msg += m_pMail->nextReceiverAddress() + "\r\n";
        _SendRequestToServer(send_rcpt_cmd, msg);
        _RcvResponseFromServer("250");
    }

	//==========================================
    msg  = "DATA\r\n";
    _SendRequestToServer(send_data_cmd, msg);
    _RcvResponseFromServer("354");

	//==========================================
    _SendRequestToServer(send_header, m_pMail->getHeader());
	//==========================================
}

void MailSender::_SendEmailContent()
{
    m_pMail->traverseContent();
    while ( m_pMail->hasMoreContent() )
    {
        _SendRequestToServer(send_content, m_pMail->nextContent());
    }
}

void MailSender::_SendEmailEnd()
{
    _SendRequestToServer(send_end, m_pMail->getEnd());
    _RcvResponseFromServer("250");
}

void MailSender::_SendSmtpQuit()
{
    _SendRequestToServer(send_quit_cmd, "QUIT\r\n");
    _RcvResponseFromServer("221");

    closesocket(m_nSocketHandle);
}

void MailSender::_RcvResponseFromServer(const std::string expected_response)
{
    int recv_bytes = 0;
    char response_buffer[MAX_BUFFER_SIZE];
	int nExpectedResponseSize = 3;
	std::string strRecvResponseFromServer;
	std::string response;

	nExpectedResponseSize = expected_response.size();//3

	recv_bytes = ::recv(m_nSocketHandle, response_buffer, MAX_BUFFER_SIZE, 0); 
    if (recv_bytes < 0)
    {
		std::cout<<"[ErrorMessage]:"<<ErrorMessage::getInstance().response(expected_response)<<std::endl;
        throw std::exception
		( 
            ErrorMessage::getInstance().response(expected_response).c_str()
        );
    }

    response = std::string(response_buffer, recv_bytes);
    std::cout << "[INFO]RECV(" << expected_response << "):" << response << std::endl;

	strRecvResponseFromServer = response.substr(0, nExpectedResponseSize);

    if ( strRecvResponseFromServer != expected_response )
    {
		std::cout<<"[ErrorMessage]:"<<ErrorMessage::getInstance().response(expected_response)<<std::endl;
        throw std::exception
		( 
            ErrorMessage::getInstance().response(expected_response).c_str()
        );
    }
}

void MailSender::_SendRequestToServer(Operaion operation, const std::string content)
{
    std::cout << "[INFO]SEND:" << content << std::endl;
	int nSindRes = 0;

	nSindRes = ::send(m_nSocketHandle, content.c_str(), content.length(), 0);
    if ( nSindRes < 0 )
    {
		std::cout<<"[ErrorMessage]:"<<ErrorMessage::getInstance().request(operation)<<std::endl;
        throw std::exception
		(
            ErrorMessage::getInstance().request(operation).c_str()
        );
    }
}


NS_END(TA_Base_Core)




#if 0


static const char *payload_text[] = 
{
	"Date: Mon, 29 Nov 2010 21:54:29 +1100\r\n",
	"To: " TO "\r\n",
	"From: " FROM "(Example User)\r\n",
	"Cc: " CC "(Another example User)\r\n",
	"Message-ID: <dcd7cb36-11db-487a-9f3a-e652a9458efd@rfcpedant.example.org>\r\n",
	"Subject: SMTP multi example message\r\n",
	"\r\n", /* empty line to divide headers from body, see RFC5322 */
	"The body of the message starts here.\r\n",
	"\r\n",
	"It could be a lot of lines, could be MIME encoded, whatever.\r\n",
	"Check RFC5322.\r\n",
	NULL
};




1.SMTP ��������
HELO/EHLO ���������ʶ�û����
MAIL ��ʼ���ʼ�����
mail from:
RCPT ��ʶ�������ʼ������ˣ�����MAIL �������
���ж��rcpt to:
DATA �ڵ�������RCPT ����󣬱�ʾ���е��ʼ��������ѱ�ʶ������ʼ�����ݴ��䣬��. ������
VRFY ������ָ֤�����û�/ �����Ƿ���ڣ����ڰ�ȫ�����ԭ�򣬷���������ֹ������
EXPN ��֤�����������б��Ƿ���ڣ����������б�Ҳ��������
HELP ��ѯ������֧��ʲô����
NOOP �޲�����������Ӧ��ӦOK
QUIT �����Ự
RSET ���ûỰ����ǰ���䱻ȡ��






2.SMTP �����뺬��
*   �ʼ����񷵻ش��뺬�� 
*   500   ��ʽ���������ʶ�𣨴˴���Ҳ���������й�����
*   501   ������ʽ���� 
*   502   �����ʵ�� 
*   503   ������������� 
*   504   �����������ʵ�� 
*   211    ϵͳ״̬��ϵͳ������Ӧ 
*   214   ������Ϣ 
*   220     ������� 
*   221     ����رմ����ŵ� 
*   421     ����δ�������رմ����ŵ���������ر�ʱ����Ӧ�������Ϊ���κ��������Ӧ�� 
*   250   Ҫ����ʼ�������� 
*   251   �û��Ǳ��أ���ת���� 
*   450   Ҫ����ʼ�����δ��ɣ����䲻���ã����磬����æ�� 
*   550   Ҫ����ʼ�����δ��ɣ����䲻���ã����磬����δ�ҵ����򲻿ɷ��ʣ�
*   451   ����Ҫ��Ĳ�������������г��� 
*   551   �û��Ǳ��أ��볢�� 
*   452   ϵͳ�洢���㣬Ҫ��Ĳ���δִ��
*   552   �����Ĵ洢���䣬Ҫ��Ĳ���δִ�� 
*   553   �����������ã�Ҫ��Ĳ���δִ�У����������ʽ����
*   354   ��ʼ�ʼ����룬��. ���� 
*   554   ����ʧ�� 
*   535   �û���֤ʧ�� 
*   235   �û���֤�ɹ� 
*   334   �ȴ��û�������֤��Ϣ for next connection>;



3. ����SMTP �������
const char HEADER[] = 
"HELO smtpSrv/r/n"
"MAIL FROM: sender@126.com/r/n"
"RCPT TO: recv@gmail.com/r/n"
"DATA/r/n"
"FROM: sender@126.com/r/n"
"TO: recv@gmail.com/r/n"
"SUBJECT: this is a test/r/n"
"Date: Fri, 8 Jan 2010 16:12:30/r/n"
"X-Mailer: shadowstar's mailer/r/n"
"MIME-Version: 1.0/r/n"
"Content-type: text/plain/r/n/r/n";
"./r/n"
"QUIT/r/n"

4. ��������
Ҫʹ��SMTP ���͸���, ��Ҫ��SMTP ͷ��Ϣ����˵��, �ı�Content-type ��Ϊÿһ���������BOUNDARY ��, ʾ������:
"DATA/r/n"
"FROM: sender@126.com/r/n"
"TO: recv@gmail.com/r/n"
"SUBJECT: this is a test/r/n"
"Date: Fri, 8 Jan 2010 16:12:30/r/n"
"X-Mailer: shadowstar's mailer/r/n"
"MIME-Version: 1.0/r/n"
"Content-type: multipart/mixed; boundary=/"#BOUNDARY#/"/r/n/r/n";
// ����
"--#BOUNDARY#/r/n"
"Content-Type: text/plain; charset=gb2312/r/n"
"Content-Transfer-Encoding: quoted-printable/r/n"
//�ʼ����ġ�����.
// ����
"/r/n--#BOUNDARY#/r/n"
"Content-Type: application/octet-stream; name=att.txt/r/n"
"Content-Disposition: attachment; filename=att.txt/r/n"
"Content-Transfer-Encoding: base64/r/n"
"/r/n"
//��������Ϣ(base64 ����)��..



5. ʵ�ֳ��ͼ�����

��SMTP ����в�û��RCPT CC ��RCPT BCC �������, ��Ҫ�����ʵ�ֳ��ͺ����͹�����?

���������ҵ�����һ�仰: �� ���еĽ�����Э�̶�ͨ��RCPT TO ������ʵ�֣������BCC ����Э�̷��ͺ��ڶԷ�����ʱ��ɾ���ŷ�����ߡ�, 
			 ��ʼһֱ��������仰��ʲô��˼? ����ͨ���鿴foxmail ���ʼ�ԭ�ķ���:
Date: Wed, 6 Jan 2010 12:11:48 +0800
From: "carven_li" < carven_li @smtp.com>
To: "carven" <carven@smtp.com>
Cc: "sam" <sam@smtp.com>,
	"yoyo" <yoyo@smtp.com>
BCC: "clara" <clara@tsmtp.com>
Subject: t
		 X-mailer: Foxmail 5.0 [cn]
Mime-Version: 1.0
Content-Type: multipart/mixed;
boundary="=====001_Dragon237244850520_====="
�Ż�Ȼ����, ��ν�ġ� Э�̡� Ӧ�þ���ָ���ͷ���Data ��ָ����ЩΪCC, ��ЩΪBCC, 
Ĭ�������ʲô����д, ֻ���͵�һ��RCPT TO ��mail, �����Ķ������˵�.
#endif




