#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <fstream>
#include <string>
using namespace std;

#define  DEF_FILE_SENDER    ".\\SparkHo\\sender.txt"
#define  DEF_FILE_ETMP      ".\\SparkHo\\etmp.txt"
#define  DEF_FILE_EMAIL     ".\\SparkHo\\email.txt"


#define FROM       "<linshenglong777@126.com>"
//#define TO         "<linshenglong888@126.com>"
#define TO         "<shenglonglin1986@gmail.com>"
#define CC         "<shenglonglin1986@gmail.com>"

static const char *payload_text[] = 
{
	"Date: Mon, 29 Nov 2010 21:54:29 +1100\r\n",
	"To: " TO "\r\n",
	"From: " FROM "(Example User)\r\n",
	"Cc: " CC "(Another example User)\r\n",
	"Message-ID: <dcd7cb36-11db-487a-9f3a-e652a9458efd@rfcpedant.example.org>\r\n",
	"Subject: SMTP SSL example message\r\n",
	"\r\n", /* empty line to divide headers from body, see RFC5322 */
	"The body of the message starts here.\r\n",
	"\r\n",
	"It could be a lot of lines, could be MIME encoded, whatever.\r\n",
	"Check RFC5322.\r\n",
	NULL
};

struct upload_status 
{
	int lines_read;
};

static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
	struct upload_status *upload_ctx = (struct upload_status *)userp;
	const char *data;

	if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) 
	{
		return 0;
	}

	data = payload_text[upload_ctx->lines_read];

	if(data) 
	{
		size_t len = strlen(data);
		memcpy(ptr, data, len);
		upload_ctx->lines_read++;
		return len;
	}
	return 0;
}




//1�����ǿ��԰ѷ����˵��ʺź����룬�ŵ�һ��txt�ļ��Ȼ��ͨ������ĺ�����������
int getsender(char * strUser,char * strSrv,char * strPass)
{
	char sbuf[100],*token;
	ifstream _sfile(DEF_FILE_SENDER); //��sender.txt���ȡ����������
	if(!_sfile)
	{
		_sfile.close();
		return -1;
	}
	_sfile.seekg(0, ios::beg);
	_sfile.getline(sbuf,100); //��ȡ��һ�У���sparkho@qq.com
	token = strtok(sbuf,"@");
	strcpy(strUser, token);
	token = strtok(NULL,"@");
	strcpy(strSrv, token);
	_sfile.getline(sbuf,100); //��ȡ�ڶ��У����룺��1234567890
	strcpy(strPass, sbuf);
	_sfile.close();
	return 1;
}

//2���ص���������ȡ�������ݣ���libcurl���ã�
size_t read_data(void *ptr, size_t size, size_t nmemb, void *data)
{
	FILE *fp = (FILE *)data;
	size_t return_size = fread(ptr, size, nmemb, fp);
	return return_size;
} 

//3��libcurl���ʼ�����������
int curlMail()
{
	struct upload_status upload_ctx;

	upload_ctx.lines_read = 0;

	char strUser[100],strPass[100],strSrv[100];
	char ebuf[100],RevList[100];
	getsender(strUser, strSrv, strPass);                                      //��sender.txt���ȡ����������
	//std::string strfrom = (std::string)strUser+"@"+(std::string)strSrv;           //��������ַ
	std::string strfrom = (std::string)strUser+"@"+(std::string)strSrv;           //��������ַ
	//string SrvAdd = "smtp://smtp."+(string)strSrv;                   //�ʼ���������ַ
	//std::string SrvAdd = "smtps://smtp."+(std::string)strSrv;                   //�ʼ���������ַ
	std::string SrvAdd = "smtp://smtp.126.com";//+(std::string)strSrv;                   //�ʼ���������ַ
	FILE *fp = fopen(DEF_FILE_ETMP, "rb");               //��ȡ��������
	if (fp == NULL) return -1;
	// ��ʼ��libcurl
	CURL *pCurlHandle;
	CURLcode return_code,res;
	//return_code = curl_global_init(CURL_GLOBAL_WIN32);
	//if (CURLE_OK != return_code) return -1;
	struct curl_slist *slist=NULL;
	ifstream _efile(DEF_FILE_EMAIL);                            //��ȡ�ռ���email��ַ���б�
	if(!_efile)
	{
		_efile.close();
	}
	else
	{
		while(_efile.getline(ebuf,100))
		{
			sprintf(RevList,"<%s>",ebuf);
			slist = curl_slist_append(slist, RevList);  //�ʼ������б�
		}
		_efile.close();
	}
	pCurlHandle = curl_easy_init();
	if(pCurlHandle)
	{
		curl_easy_setopt(pCurlHandle, CURLOPT_URL, SrvAdd.c_str());                                       //�ʼ���������ַ
		curl_easy_setopt(pCurlHandle, CURLOPT_USERNAME, strUser);                                       //�û��ʺ�
		curl_easy_setopt(pCurlHandle, CURLOPT_PASSWORD, strPass);                                      //�û�����
		curl_easy_setopt(pCurlHandle, CURLOPT_MAIL_FROM, FROM);                          //��������ַ
		curl_easy_setopt(pCurlHandle, CURLOPT_MAIL_RCPT, slist);                                           //�ռ����б�

 		curl_easy_setopt(pCurlHandle, CURLOPT_READFUNCTION, read_data);  
 		curl_easy_setopt(pCurlHandle, CURLOPT_READDATA, fp);

		//curl_easy_setopt(pCurlHandle, CURLOPT_READFUNCTION, payload_source);
		//curl_easy_setopt(pCurlHandle, CURLOPT_READDATA, &upload_ctx);
		curl_easy_setopt(pCurlHandle, CURLOPT_UPLOAD, 1L);


		curl_easy_setopt(pCurlHandle, CURLOPT_VERBOSE, 1L);

		//curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
		//curl_easy_setopt(pCurlHandle, CURLOPT_FTPSSLAUTH, CURLFTPAUTH_SSL);
                         //�ص����������ڶ���������
	}
	res = curl_easy_perform(pCurlHandle);
	fclose(fp);
	curl_slist_free_all(slist);
	curl_easy_cleanup(pCurlHandle);
	//curl_global_cleanup();
	return 1;
}


int main()
{
	curlMail();
}




