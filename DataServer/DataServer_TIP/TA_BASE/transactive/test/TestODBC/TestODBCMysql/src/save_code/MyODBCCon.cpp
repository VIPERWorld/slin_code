CREATE TABLE `testTable` (              
						  `TestTEXT` text,                      
						  `TestBigInt` bigint(20) default NULL  
						  )

						  ʹ���ҵķ�װ��ķ������£�

#include "query.h"
#include <iostream>
						  using namespace std;

int main(int argc, char* argv[])
{
	int nConnectTimeOut = 5;
	int nLoginTimeOut = 3;
	int nQueryTimeOut = 3;

	CConnection * pCon = NULL;
	CDBAccess dbAccess;

	//��ʼ��
	if(!dbAccess.Init(NULL, &pCon, nConnectTimeOut, nLoginTimeOut, nQueryTimeOut))
	{
		cout << dbAccess.GetLastError()<<endl;
		return -1;
	}
	//�������ݿ�
	if(!dbAccess.Connect("DNSName", "UserName", "Password"))
	{
		cout << dbAccess.GetLastError()<<endl;
		return -1; 
	}
	//oK�����ӳɹ��ˣ����Խ������sql�����ˡ�
	char pszSQL[256];
	memset(pszSQL, 0x00, sizeof(pszSQL)); 

	sprintf((char*)pszSQL, "SELECT * FROM %s", "testTable");

	if(dbAccess.ExecuteSQL(pszSQL))
	{ //ִ�в�ѯ�����ϣ���ʼȡ����
		if(dbAccess.FetchFirst())
		{
			do 
			{
				long nRetLen = 0;

				char pszTest[300];
				memset((char*)pszTest, 0x00, sizeof(pszTest));

				if(!dbAccess.GetData("TestTEXT", pszTest, sizeof(pszTest), &nRetLen))
				{
					cout << "�޷�ȡ��TestTEXT�ֶ���Ϣ!"<<endl;
					break;
				}
				cout << "get TestTEXT data:" << pszTest << endl;


				_INT64 lTestBigInt = 0;
				if(!dbAccess.GetData("TestBigInt", &(lTestBigInt), sizeof(_INT64), &nRetLen, SQL_C_SBIGINT))
				{
					cout << "�޷�ȡ��TestBigInt�ֶ���Ϣ!"<<endl;
					break;
				}  
				char pszTemp[30];
				memset(pszTemp, 0x00, 24);
				_i64toa(lTestBigInt, (char*)pszTemp, 10);    
				cout << "get TestBigInt data:" << pszTemp <<endl;    
			} 
			while(dbAccess.Fetch());

		}
		else
		{
			cout <<dbAccess.GetLastError()<<endl;
		}

	}

	//����رվ�����������ַ��ʷǷ����ǳ���Ҫ��
	dbAccess.CloseStmt();

	//�Ͽ������ݿ������
	if(!dbAccess.Disconnect())
	{
		cout <<"error disconnect" <<dbAccess.GetLastError()<<endl;
		return -1;
	}

	dbAccess.Close();

	return 0;
}

������Query.h�ļ����ݣ�

// Query.h: interface for the CQuery class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUERY_H__CAEAF203_40C0_4C32_BA76_9A4B0245984B__INCLUDED_)
#define AFX_QUERY_H__CAEAF203_40C0_4C32_BA76_9A4B0245984B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef WIN32
#include "windows.h"
#endif
//ODBC API
#include <sql.h> 
#include <sqlext.h>
#include <odbcinst.h>

//--
#pragma comment(lib,"odbc32.lib")

#pragma comment(lib,"OdbcCP32.Lib")

#ifdef WIN32
typedef __int64 _INT64;
#endif

#ifdef GCC
typedef long long int _INT64;
#endif

//--

#define SQL_COMMIT          0 //�ύ
#define SQL_ROLLBACK        1 //�ع�
//
//////////////////////////////////////////////////////////////////////////
//������붨��
//������붨�����ERROR_����_������_�����ڱ��
//�ݶ���λ������
#define BASE_ERROR      100000

//���ݿ�ģ��������
#define DATABASE_BASE_ERROR    BASE_ERROR + 0


//CConnection���еĴ������
#define CON_BASE_ERROR   DATABASE_BASE_ERROR + 0

#define ERROR_CON_INIT_1  CON_BASE_ERROR + 1 
#define ERROR_CON_INIT_2  CON_BASE_ERROR + 2 
#define ERROR_CON_INIT_3  CON_BASE_ERROR + 3 
#define ERROR_CON_CONNECT_1  CON_BASE_ERROR + 4 
#define ERROR_CON_CONNECT_2  CON_BASE_ERROR + 5 
#define ERROR_CON_DISCONNECT_1 CON_BASE_ERROR + 6
#define ERROR_CON_DISCONNECT_2 CON_BASE_ERROR + 7
#define ERROR_CON_BEGINTRAN_1 CON_BASE_ERROR + 8
#define ERROR_CON_ENDTRAN_1  CON_BASE_ERROR + 9
#define ERROR_CON_ENDTRAN_2  CON_BASE_ERROR + 10
#define ERROR_CON_SETTIMEOUT_1 CON_BASE_ERROR + 11
#define ERROR_CON_SETTIMEOUT_2 CON_BASE_ERROR + 12
#define ERROR_CON_SETTIMEOUT_3 CON_BASE_ERROR + 13
#define ERROR_CON_SETTIMEOUT_4 CON_BASE_ERROR + 14
#define ERROR_CON_CONNECT_3  CON_BASE_ERROR + 15
#define ERROR_CON_DISCONNECT_3 CON_BASE_ERROR + 16
#define ERROR_CON_BEGINTRAN_2 CON_BASE_ERROR + 17
#define ERROR_CON_ENDTRAN_3  CON_BASE_ERROR + 18
#define ERROR_CON_SETTIMEOUT_5 CON_BASE_ERROR + 19
#define ERROR_CON_CONNECT_4  CON_BASE_ERROR + 20 
#define ERROR_CON_BEGINTRAN_3 CON_BASE_ERROR + 21
#define ERROR_CON_ENDTRAN_4  CON_BASE_ERROR + 22
#define ERROR_CON_ISCONNECT_1 CON_BASE_ERROR + 23
#define ERROR_CON_ISCONNECT_2 CON_BASE_ERROR + 24

//CQuery���еĴ������
#define QUERY_BASE_ERROR  DATABASE_BASE_ERROR + 100

#define ERROR_QUERY_INIT_1   QUERY_BASE_ERROR + 1
#define ERROR_QUERY_INIT_2   QUERY_BASE_ERROR + 2
#define ERROR_QUERY_INIT_3   QUERY_BASE_ERROR + 3
#define ERROR_QUERY_GETCOLCOUNT_1 QUERY_BASE_ERROR + 4
#define ERROR_QUERY_GETCOLCOUNT_2 QUERY_BASE_ERROR + 5
#define ERROR_QUERY_GETCROWCOUNT_1 QUERY_BASE_ERROR + 6
#define ERROR_QUERY_GETCROWCOUNT_2 QUERY_BASE_ERROR + 7
#define ERROR_QUERY_EXECSQL_1  QUERY_BASE_ERROR + 8
#define ERROR_QUERY_EXECSQL_2  QUERY_BASE_ERROR + 9
#define ERROR_QUERY_FETCH_1   QUERY_BASE_ERROR + 10
#define ERROR_QUERY_FETCH_2   QUERY_BASE_ERROR + 11
#define ERROR_QUERY_FETCHNEXT_1  QUERY_BASE_ERROR + 12
#define ERROR_QUERY_FETCHNEXT_2  QUERY_BASE_ERROR + 13
#define ERROR_QUERY_FETCHPRE_1  QUERY_BASE_ERROR + 14
#define ERROR_QUERY_FETCHPRE_2  QUERY_BASE_ERROR + 15
#define ERROR_QUERY_FETCHFIRST_1 QUERY_BASE_ERROR + 16
#define ERROR_QUERY_FETCHFIRST_2 QUERY_BASE_ERROR + 17
#define ERROR_QUERY_FETCHLAST_1  QUERY_BASE_ERROR + 18
#define ERROR_QUERY_FETCHLAST_2  QUERY_BASE_ERROR + 19
#define ERROR_QUERY_FETCHROW_1  QUERY_BASE_ERROR + 20
#define ERROR_QUERY_FETCHROW_2  QUERY_BASE_ERROR + 21
#define ERROR_QUERY_CANCEL_1  QUERY_BASE_ERROR + 22
#define ERROR_QUERY_CANCEL_2  QUERY_BASE_ERROR + 23
#define ERROR_QUERY_GETDATA_1  QUERY_BASE_ERROR + 24
#define ERROR_QUERY_GETDATA_2  QUERY_BASE_ERROR + 25
#define ERROR_QUERY_GETDATA_3  QUERY_BASE_ERROR + 26
#define ERROR_QUERY_GETDATA_4  QUERY_BASE_ERROR + 27
#define ERROR_QUERY_GETCOLBYNAME_1 QUERY_BASE_ERROR + 28
#define ERROR_QUERY_GETCOLNAME_1 QUERY_BASE_ERROR + 29
#define ERROR_QUERY_GETCOLNAME_2 QUERY_BASE_ERROR + 30
#define ERROR_QUERY_INIT_4   QUERY_BASE_ERROR + 31
#define ERROR_QUERY_GETCOLCOUNT_3 QUERY_BASE_ERROR + 32
#define ERROR_QUERY_GETCROWCOUNT_3 QUERY_BASE_ERROR + 33
#define ERROR_QUERY_EXECSQL_3  QUERY_BASE_ERROR + 34
#define ERROR_QUERY_FETCH_3   QUERY_BASE_ERROR + 35
#define ERROR_QUERY_FETCHNEXT_3  QUERY_BASE_ERROR + 36
#define ERROR_QUERY_FETCHPRE_3  QUERY_BASE_ERROR + 37
#define ERROR_QUERY_FETCHFIRST_3 QUERY_BASE_ERROR + 38
#define ERROR_QUERY_FETCHLAST_3  QUERY_BASE_ERROR + 39
#define ERROR_QUERY_FETCHROW_3  QUERY_BASE_ERROR + 40
#define ERROR_QUERY_CANCEL_3  QUERY_BASE_ERROR + 41
#define ERROR_QUERY_GETDATA_5  QUERY_BASE_ERROR + 42
#define ERROR_QUERY_GETCOLNAME_3 QUERY_BASE_ERROR + 43
#define ERROR_QUERY_INSERTARRAY_1 QUERY_BASE_ERROR + 44
#define ERROR_QUERY_INSERTARRAY_2 QUERY_BASE_ERROR + 45
#define ERROR_QUERY_INSERTARRAY_3 QUERY_BASE_ERROR + 46
#define ERROR_QUERY_INSERTARRAY_4 QUERY_BASE_ERROR + 47
#define ERROR_QUERY_INSERTARRAY_5 QUERY_BASE_ERROR + 48
#define ERROR_QUERY_INSERTARRAY_6 QUERY_BASE_ERROR + 49
#define ERROR_QUERY_INIT_5   QUERY_BASE_ERROR + 50
//CDBAccess���еĴ������
#define DBACCESS_BASE_ERROR  DATABASE_BASE_ERROR + 200

#define ERROR_DBACCESS_INIT_1   DBACCESS_BASE_ERROR + 1
#define ERROR_DBACCESS_INIT_2   DBACCESS_BASE_ERROR + 2
#define ERROR_DBACCESS_CONNECT_1  DBACCESS_BASE_ERROR + 3
#define ERROR_DBACCESS_CONNECT_2  DBACCESS_BASE_ERROR + 4
#define ERROR_DBACCESS_DISCONNECT_1  DBACCESS_BASE_ERROR + 5
#define ERROR_DBACCESS_DISCONNECT_2  DBACCESS_BASE_ERROR + 6
#define ERROR_DBACCESS_RECONNECT_1  DBACCESS_BASE_ERROR + 7
#define ERROR_DBACCESS_EXECUTESQL_1  DBACCESS_BASE_ERROR + 8
#define ERROR_DBACCESS_EXECUTESQL_2  DBACCESS_BASE_ERROR + 9
#define ERROR_DBACCESS_EXECUTESQL_3  DBACCESS_BASE_ERROR + 10
#define ERROR_DBACCESS_EXECUTESQL_4  DBACCESS_BASE_ERROR + 11
#define ERROR_DBACCESS_EXECUTESQL_5  DBACCESS_BASE_ERROR + 12
#define ERROR_DBACCESS_INIT_3   DBACCESS_BASE_ERROR + 13
#define ERROR_DBACCESS_INIT_4   DBACCESS_BASE_ERROR + 14
#define ERROR_DBACCESS_GETTASKDATA_1 DBACCESS_BASE_ERROR + 15
#define ERROR_DBACCESS_GETTASKDATA_2 DBACCESS_BASE_ERROR + 16
#define ERROR_DBACCESS_GETTASKDATA_3 DBACCESS_BASE_ERROR + 17
#define ERROR_DBACCESS_GETTASKDATA_4 DBACCESS_BASE_ERROR + 18
#define ERROR_DBACCESS_GETTASKDATA_5 DBACCESS_BASE_ERROR + 19
#define ERROR_DBACCESS_GETTASKDATA_6 DBACCESS_BASE_ERROR + 20
#define ERROR_DBACCESS_GETTASKDATA_7 DBACCESS_BASE_ERROR + 21
#define ERROR_DBACCESS_GETTASKDATA_8 DBACCESS_BASE_ERROR + 22
#define ERROR_DBACCESS_GETTASKDATA_9 DBACCESS_BASE_ERROR + 23
#define ERROR_DBACCESS_GETTASKDATA_10 DBACCESS_BASE_ERROR + 24
#define ERROR_DBACCESS_GETTASKDATA_11 DBACCESS_BASE_ERROR + 25
#define ERROR_DBACCESS_GETTASKDATA_12 DBACCESS_BASE_ERROR + 26
#define ERROR_DBACCESS_GETTASKDATA_13 DBACCESS_BASE_ERROR + 27

//////////////////////////////////////////////////////////////////////////

class CConnection
{
public:
	CConnection();
	virtual ~CConnection();
public:
	//�ύ������.����: SQL_COMMITΪ�ύ��SQL_ROLLBACKΪ�ع�.����ֵ:�Ƿ��ύ�ɹ�
	bool EndTran(short nAction);

	//��ʼ������.����ֵ:�Ƿ�ɹ�
	bool BeginTran();

	//�Ͽ�����. �Ͽ�����ǰ��Ҫȷ���Ƿ��ύ�����񡣷���ֵ:�Ƿ�ɹ�
	bool Disconnect();

	//���ӵ�DNS������:DNS�����û���������, ����ֵ:�Ƿ����ӳɹ�
	bool Connect(const char* pszDNS, const char* pszUser, const char* pszPwd);

	//ȡ������Ϣ,����ֵ:������Ϣ
	const char* GetLastError(){return (char*)m_pszLastError;}

	//�Ƿ����ӵ����ݿ�,����ֵ:�Ƿ����ӵ����ݿ�
	bool IsConnect();

	//���ó�ʱ�������ֱ�Ϊ���ӳ�ʱ����¼��ʱ.���Ϊ-1����ʾ�ò�����������,����ֵ:�Ƿ����óɹ�
	bool SetTimeOut(int nConnect = -1, int nLogin  = -1);

	//�Ƿ����ڽ���������,����ֵ:�Ƿ����������.
	bool IsInTran(){return m_bTraning;}

	//�����������ݿ�,����ֵ:�Ƿ������ɹ�
	bool ReConnect(); 

	//��ʼ��,����:���ӳ�ʱ����¼��ʱ,����ֵ:�Ƿ��ʼ���ɹ�.
	bool Init(int nConnectTimeOut = -1, int nLoginTimeOut = -1);


	//���Է����ΪCQuery��ʹ�á�
	operator SQLHANDLE(){return m_hCon;}


private:
	//���ô�����Ϣ,����:������Ϣ,�������
	void SetErrorInfo(const char* pszError, long lErrorCode); 

	//ȡ�ô�����Ϣ������:������ͣ�����ľ�����������,����ֵ:�Ƿ�ɹ�
	bool GetErrorInfo(SQLSMALLINT nHandleType, SQLHANDLE nHandle, long lErrorCode);

	//�Ƿ�ɹ�ִ���ˣ�����:��Ҫ�жϵķ���ֵ��������ͣ���Ҫ�жϵľ�����������,����ֵ:�Ƿ�ɹ�
	bool IsSuccess(SQLRETURN nRet, SQLSMALLINT nHandleType, SQLHANDLE nHandle, long lErrorCode);
public:

	SQLHANDLE m_hCon; //���ݿ����Ӿ�� 

protected:

	int m_nLoginTimeOut;
	int m_nConnectTimeOut;

	SQLHANDLE m_hEnv; //�������
	SQLRETURN m_nRet; //����ֵ

protected:
	bool m_bIsConnect; //�Ƿ��������ݿ�
	SQLCHAR m_pszLastError[SQL_MAX_MESSAGE_LENGTH+100]; //������Ϣ

	bool m_bTraning; //�������Ƿ������
	bool m_bInit; //��ʼ���Ƿ�����

	char m_pszDNS[255];   //ODBC DNS��
	char m_pszUser[255];  //ODBC �û���
	char m_pszPwd[255];   //ODBC �û�����
};

class CQuery  
{
public:
	CQuery(CConnection** ppDBCon, int nQueryTimeOut = 3);
	virtual ~CQuery();


	//ȡ�ü�¼��������.����ֵ:����
	unsigned short GetColumnCount();

	//ȡ��Ӱ������,����ֵ:Ӱ������
	long GetChangedRowCount(void);

	//ִ��ָ����sql���,����:Ҫִ�е�sql���,����ֵ:�Ƿ�ɹ�
	bool ExecuteSQL(const char* pszSQL);

	//��һ����¼,����ֵ:�Ƿ�ɹ�
	bool Fetch();

	//ǰһ����¼,����ֵ:�Ƿ�ɹ�
	bool FetchPrevious();

	//��һ����¼,����ֵ:�Ƿ�ɹ�
	bool FecthNext();

	//��AbsoluteΪtrue�ǣ�����nRowָ���ľ����У������ɵ�ǰλ�ù���������FetchOffsetָ��������У�nRow����0��ʾ��ǰ������nRowС��0��ʾ������
	bool FetchRow(unsigned int nRow, bool bAbsolute = true);

	//������һ��,����ֵ:�Ƿ�ɹ�
	bool FetchFirst();

	//�������һ��,����ֵ:�Ƿ�ɹ�
	bool FetchLast();

	//ȡ��,����ֵ:�Ƿ�ɹ�
	bool Cancel();

	//ȡ�õ�ǰ�еĵ�nColumn�е�ֵ�����������У����ջ����������ջ�������С������ֵ��С����������C�������͡�����ֵ:�Ƿ�ɹ�
	bool GetData(unsigned short nColumn, void* pBuffer, 
		unsigned long nBufLen, 
		long * nDataLen = NULL, 
		int nType=SQL_C_DEFAULT);

	//ȡ�õ�ǰ�е�pszName�ֶε�ֵ�����������У����ջ����������ջ�������С������ֵ��С����������C�������͡�����ֵ:�Ƿ�ɹ�
	bool GetData(const char* pszName, void* pBuffer, 
		unsigned long nBufLen,
		long * nDataLen = NULL, 
		int nType=SQL_C_DEFAULT);

	//�ر����ӣ�����ִ��sql���ʱ�������ȶϿ����ӣ�Ȼ���ڷ��������У��������Ƿ����α�
	void Close();

	//ȡ������Ϣ.����ֵ:������Ϣ
	const char* GetLastError(){return (char*)m_pszLastError;}
protected:

	//��ʼ����������.����ֵ:�Ƿ�ɹ�
	bool Init();

	//ȡ��nColumn�е��ֶ���.����:����,�ֶ���,�ֶ�������.����ֵ:�Ƿ�ɹ�
	bool GetColumnName(unsigned short nColumn, char* pszName, short nNameLen);

	//ȡ���ֶ���ΪpszColumn���ڵ���,����:�ֶ���,����ֵ:�ֶ���������
	unsigned short GetColumnByName(const char* pszColumn);

	//���ô�����Ϣ������:������Ϣ���������
	void SetErrorInfo(const char* pszError, long lErrorCode);

	//ȡ�ô�����Ϣ������:������ͣ�����ľ�����������.����ֵ:�Ƿ�ɹ�
	bool GetErrorInfo(SQLSMALLINT nHandleType, SQLHANDLE nHandle, long lErrorCode);

	//�Ƿ�ɹ�ִ���ˣ�����:��Ҫ�жϵķ���ֵ��������ͣ� ��Ҫ�жϵľ�����������,����ֵ:�Ƿ�ɹ�
	bool IsSuccess(SQLRETURN nRet, SQLSMALLINT nHandleType, SQLHANDLE nHandle, long lErrorCode);

	//�Ƿ����.����ֵ:�Ƿ�ɹ�
	bool IsValid();

protected:
	SQLHSTMT m_hStmt; //STMT���
	SQLRETURN m_nRet; //����ֵ

private:
	CConnection** m_ppDBCon;
protected:
	SQLCHAR m_pszLastError[SQL_MAX_MESSAGE_LENGTH+100]; //������Ϣ
	int m_nQueryTimeOut;  //��ѯ��ʱʱ��
};


class CDBAccess  
{
public:
	//ִ��SQL���,����:Ҫִ�е�SQL���.����ֵ:�Ƿ�ִ�гɹ�
	bool ExecuteSQL(const char* pszSQL);

	//�رյ����ݿ������,��������ʹ��,�����ȵ���Init����.
	void Close();

	//�����������ݿ�,����ֵ:�Ƿ������ɹ�
	bool ReConnect();

	//�Ͽ������ݿ������.����ֵ:�Ƿ�Ͽ�����
	bool Disconnect();

	//���ӵ����ݿ�.����:DNS��,�û���,����.����ֵ:�Ƿ����ӵ����ݿ�.
	bool Connect(const char* pszDNS, const char* pszUser, const char* pszPwd);

	//��ʼ��,����:sql��䱣���ļ�,���ӳ�ʱ,��¼��ʱ.����ֵ:�Ƿ��ʼ���ɹ�.
	bool Init(const char* pszSaveSQLFile, CConnection** ppDBCon, int nConnectTimeOut = -1, int nLoginTimeOut = -1, int nQueryTimeOut = 3);

	//�Ƿ��Ѿ��������ݿ���,����ֵ,�Ƿ����ӵ����ݿ�
	bool IsConnect();

	//��ʼ������,����ֵ:�Ƿ�ɹ�
	bool BeginTran(){return (*m_ppDBCon)->BeginTran();}

	//�ύ������,����:�ύ����,����ֵ:�Ƿ�ɹ�
	bool EndTran(short nAction){return (*m_ppDBCon)->EndTran(nAction);}

	//add by stavck at 20051031
	//ȡ�õ�ǰ�е�cszName�ֶε�ֵ�����������У����ջ����������ջ�������С������ֵ��С����������C�������͡�����ֵ:�Ƿ�ɹ�
	bool GetData(const char* pszName, void* pBuffer, unsigned long nBufLen
		, long * nDataLen = NULL, int nType=SQL_C_DEFAULT)
	{return m_pQuery->GetData(pszName, pBuffer, nBufLen, nDataLen, nType);}

	//��һ����¼,����ֵ:�Ƿ�ɹ�
	bool Fetch(){return m_pQuery->Fetch();}
	//end add
	//������һ��,����ֵ:�Ƿ�ɹ�
	bool FetchFirst(){return m_pQuery->FetchFirst();}

	//ǰһ����¼,����ֵ:�Ƿ�ɹ�
	bool FetchPrevious(){return m_pQuery->FetchPrevious();}

	//��һ����¼,����ֵ:�Ƿ�ɹ�
	bool FecthNext(){return m_pQuery->FecthNext();}

	//��AbsoluteΪtrue�ǣ�����nRowָ���ľ����У������ɵ�ǰλ�ù���������FetchOffsetָ��������У�nRow����0��ʾ��ǰ������nRowС��0��ʾ������
	bool FetchRow(unsigned int nRow, bool bAbsolute = true)
	{return m_pQuery->FetchRow(nRow, bAbsolute);}

	//�������һ��,����ֵ:�Ƿ�ɹ�
	bool FetchLast(){return m_pQuery->FetchLast();} 

	//ȡ������Ϣ.����ֵ:������Ϣ
	const char* GetLastError(){return (char*)m_pszLastError;}

	CDBAccess();
	virtual ~CDBAccess();

	//add at 20051124
	//�ر����������Ϊ�˳�ʱ�رջ��������ÿ�����ݿ�������Ҫʹ�øú������ر�
	void CloseStmt(){m_pQuery->Close();}
protected: 
	int m_nLoginTimeOut;  //��¼��ʱʱ��
	int m_nConnectTimeOut;  //���ӳ�ʱʱ��
	int m_nQueryTimeOut;  //��ѯ��ʱʱ��

	char m_pszLastError[255]; //���������Ĵ�����Ϣ
	CConnection **m_ppDBCon;  //���ݿ�����

	CQuery * m_pQuery;   //��ѯ��������ʱʹ��,��¼��

protected:

	//���ô�����Ϣ,����:������Ϣ,���������λ��,�Ƿ���ӵ���־
	void SetErrorInfo(const char *pszError, long lErrorCode); 

protected:

	bool m_bCreateCon; //�Ƿ����Լ����������ݿ�����
	bool m_bEnd; //��ѯ��������ʱʹ��,�Ƿ������һ����¼��.
};

#endif // !defined(AFX_QUERY_H__CAEAF203_40C0_4C32_BA76_9A4B0245984B__INCLUDED_)
������Query.cpp�ļ����ݣ�

// Query.cpp: implementation of the CQuery class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Query.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConnection::CConnection()
{
	memset(m_pszLastError, 0x00, SQL_MAX_MESSAGE_LENGTH+100);
	memset(m_pszDNS, 0x00, sizeof(m_pszDNS));
	memset(m_pszUser, 0x00, sizeof(m_pszUser));
	memset(m_pszPwd, 0x00, sizeof(m_pszPwd));

	m_bIsConnect = false;

	m_hCon = INVALID_HANDLE_VALUE;
	m_hEnv = INVALID_HANDLE_VALUE;

	m_bTraning = false;
	m_nRet = SQL_SUCCESS;
	m_bInit = false;
}

CConnection::~CConnection()
{
	try
	{
		if(m_bTraning)
		{//���û���ֹ��ϵ����ӣ��������лع�
			EndTran(SQL_ROLLBACK);
		}

		if(IsConnect())
		{//������ӻ�û�жϿ�����ô����Ͽ���
			Disconnect();
		}

		if(m_hEnv != INVALID_HANDLE_VALUE)
		{
			SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
			m_hEnv = INVALID_HANDLE_VALUE;
		}

		if(m_hCon != INVALID_HANDLE_VALUE)
		{
			SQLFreeHandle(SQL_HANDLE_DBC, m_hCon);
			m_hCon = INVALID_HANDLE_VALUE;
		}
	}
	catch (...)
	{
		//
	} 
}


bool CConnection::GetErrorInfo(SQLSMALLINT nHandleType, SQLHANDLE nHandle, long lErrorCode)
{//����������Ҫ��һ��дһ�£�����ֻ��ȡ�����һ�еĴ�����Ϣ,�����󲿷����ʱ������.
	bool bConnInd = nHandleType == SQL_HANDLE_DBC ? true :false;
	SQLRETURN nRet = SQL_SUCCESS;

	SQLCHAR pszSqlState[SQL_MAX_MESSAGE_LENGTH] = "";
	SQLCHAR pszErrorMsg[SQL_MAX_MESSAGE_LENGTH] = "";


	SQLINTEGER nNativeError = 0L;
	SQLSMALLINT nErrorMsg = 0;
	SQLSMALLINT nRecNmbr = 1;

	//ִ�д���ʱODBC���ص���һ��������Ϣ�Ľ��������Ҫ�������������������

	memset(pszSqlState, 0x00, sizeof(pszSqlState));
	memset(pszErrorMsg, 0x00, sizeof(pszErrorMsg));

	nRet = SQLGetDiagRec(nHandleType, nHandle,
		nRecNmbr, pszSqlState, &nNativeError,
		pszErrorMsg, SQL_MAX_MESSAGE_LENGTH - 1,
		&nErrorMsg);


	SetErrorInfo((char*)pszErrorMsg, lErrorCode);

	return true;
}

bool CConnection::IsSuccess(SQLRETURN nRet, SQLSMALLINT nHandleType,
							SQLHANDLE nHandle, long lErrorCode)
{
	if(nRet == SQL_SUCCESS)
	{
		return true;
	}
	else if(nRet == SQL_SUCCESS_WITH_INFO)
	{
		return true;
	}
	else
	{
		GetErrorInfo(nHandleType, nHandle, lErrorCode);
		return false;
	}

	return false; 
}

bool CConnection::Init(int nConnectTimeOut , int nLoginTimeOut )
{ 
	m_nRet = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv);

	if(IsSuccess(m_nRet, SQL_HANDLE_ENV, m_hEnv, ERROR_CON_INIT_1))
	{
		//��ODBC���ó�Ϊ�汾3������ĳЩODBC API �������ܱ�֧�֡�
		m_nRet = SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION,
			(SQLPOINTER)SQL_OV_ODBC3, SQL_IS_UINTEGER);

		if(!IsSuccess(m_nRet, SQL_HANDLE_ENV, m_hEnv, ERROR_CON_INIT_2))
		{
			//ϵͳ��֧��ODBC3
			return false;
		}

		m_nRet = SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hCon);

		if(!IsSuccess(m_nRet, SQL_HANDLE_DBC, m_hCon, ERROR_CON_INIT_3))
		{
			//�������Ӿ�����ɹ���
			return false;
		}

	}
	else
	{
		//���价��������ɹ���
		return false;
	}

	m_nConnectTimeOut = nConnectTimeOut;
	m_nLoginTimeOut = nLoginTimeOut;



	m_bInit = true;
	SetTimeOut(nConnectTimeOut, nLoginTimeOut);

	return true;
}

bool CConnection::Connect(const char *pszDNS, const char *pszUser, const char *pszPwd)
{
	if(!m_bInit)
	{//���û�г�ʼ��,�ǲ������ӵ�!
		SetErrorInfo("û�г�ʼ��,�������ӵ����ݿ⣡", ERROR_CON_CONNECT_4);
		return false;
	}

	if(pszDNS == NULL)
	{//DNS��ôҲ����Ϊ�յİ�
		SetErrorInfo("DNS��Ϊ��,�޷��������ݿ⣡", ERROR_CON_CONNECT_1);
		return false;
	}
	else
	{
		strncpy((char*)m_pszDNS, pszDNS, sizeof(m_pszDNS));
	}

	if(pszUser != NULL)
	{
		strncpy((char*)m_pszUser, pszUser, sizeof(m_pszUser));
	}
	else
	{
		m_pszUser[0] = NULL;
	}

	if(pszPwd != NULL)
	{
		strncpy((char*)m_pszPwd, pszPwd, sizeof(m_pszPwd));
	}
	else
	{
		m_pszPwd[0] = NULL;
	}

	try
	{
		//��ʼ����
		m_nRet = SQLConnect(m_hCon,
			(SQLCHAR*)pszDNS, SQL_NTS,
			(SQLCHAR*)pszUser, SQL_NTS,
			(SQLCHAR*)pszPwd, SQL_NTS);
	}
	catch (...)
	{
		SetErrorInfo("�������ݿ�ʱ��������", ERROR_CON_CONNECT_3);
		return false;
	}

	m_bIsConnect = IsSuccess(m_nRet, SQL_HANDLE_DBC, m_hCon, ERROR_CON_CONNECT_2);

	return m_bIsConnect;
}

void CConnection::SetErrorInfo(const char *pszError, long lErrorCode)
{//�ȰѴ�������������Ϣ��,���������Ĵ�����Ϣ
	memset(m_pszLastError, 0x00, sizeof(m_pszLastError));
	char pszErrorCode[20] = "";

	//�����ô������
	sprintf((char*)pszErrorCode, "EC[%ld]", lErrorCode);
	int nLen = strlen((char*)pszErrorCode);

	strncpy((char*)m_pszLastError, (const char*)pszErrorCode, nLen);
	//���ܳ�������󳤶�,Ҫ����һ��
	size_t nMaxSize = sizeof(m_pszLastError)-1-nLen;

	strncat((char*)m_pszLastError, pszError, nMaxSize>strlen(pszError)?strlen(pszError):nMaxSize);

}

bool CConnection::Disconnect()
{
	if(!IsConnect())
	{//���û������,ֻ�Ǽ򵥵ķ���
		return true;
	}

	if(m_bTraning)
	{//������û���ύ��!
		SetErrorInfo("�������ύ���񣬲��ܶϿ���", ERROR_CON_DISCONNECT_1);
		return false;
	}

	try
	{ 
		//�Ͽ�����
		m_nRet = SQLDisconnect(m_hCon);
		if(m_hEnv != INVALID_HANDLE_VALUE)
		{
			SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
			m_hEnv = INVALID_HANDLE_VALUE;
		}

		if(m_hCon != INVALID_HANDLE_VALUE)
		{
			SQLFreeHandle(SQL_HANDLE_DBC, m_hCon);
			m_hCon = INVALID_HANDLE_VALUE;
		}  
		m_bInit = false;

	}
	catch (...)
	{
		SetErrorInfo("�Ͽ����ݿ�����ʱ��������", ERROR_CON_DISCONNECT_3);
		m_bIsConnect = false;

		return false;
	}

	//�ж��Ƿ�ɹ��Ͽ�
	m_bIsConnect = !IsSuccess(m_nRet, SQL_HANDLE_DBC, m_hCon, ERROR_CON_DISCONNECT_2);

	return !m_bIsConnect;
}

bool CConnection::BeginTran()
{
	if(!IsConnect())
	{//���û������,��ô��ʼ������!
		SetErrorInfo("û������,��ô��ʼ������?", ERROR_CON_BEGINTRAN_3);
		return false;
	}

	try
	{ 
		//�����������ֶ��ύ.
		m_nRet= SQLSetConnectAttr(m_hCon,
			SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_OFF,
			SQL_IS_POINTER);
	}
	catch (...)
	{
		SetErrorInfo("��ʼ������ʱ��������", ERROR_CON_BEGINTRAN_2);
		return false;
	}
	//�ж��Ƿ�ɹ�
	m_bTraning = IsSuccess(m_nRet, SQL_HANDLE_DBC, m_hCon, ERROR_CON_BEGINTRAN_1);

	return m_bTraning;
}

bool CConnection::EndTran(short nAction)
{
	if(!IsConnect() || !m_bTraning)
	{
		SetErrorInfo("û������,���߻�û�п�ʼ������!�޷��ύ����", ERROR_CON_ENDTRAN_4);
		return true;
	}

	if(nAction != SQL_COMMIT)
	{//��������ύ,�����ع�����
		nAction = SQL_ROLLBACK;
	}

	try
	{ 
		//�Ƚ���������
		m_nRet = SQLEndTran(SQL_HANDLE_DBC, m_hCon, nAction);
		//�ж��Ƿ�ɹ�
		m_bTraning = !IsSuccess(m_nRet, SQL_HANDLE_DBC, m_hCon, ERROR_CON_ENDTRAN_1);
		//�ٸĳ��Զ��ύ.
		m_nRet= SQLSetConnectAttr(m_hCon,
			SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_ON,
			SQL_IS_POINTER);
	}
	catch (...) 
	{
		SetErrorInfo("����������ʱ��������", ERROR_CON_ENDTRAN_3);
		return false;
	}

	//�޸ĳɹ���û
	IsSuccess(m_nRet, SQL_HANDLE_DBC, m_hCon, ERROR_CON_ENDTRAN_2); 

	return !m_bTraning; 
}

bool CConnection::SetTimeOut(int nConnect, int nLogin)
{
	bool bRet = false;

	if(!m_bInit)
	{//���û�г�ʼ��,����ʹ�øú���!
		SetErrorInfo("���ڳ�ʼ����ʹ�øú���", ERROR_CON_SETTIMEOUT_1);
		return bRet;
	}

	try
	{ 
		if(nLogin >= 0)
		{//����Ǹ���,�Ͳ��ù���!
			if(m_bIsConnect)
			{//���Ӻ�,�������õ�¼��ʱ��.
				SetErrorInfo("���õ�¼��ʱ����������ǰʹ�øú���", ERROR_CON_SETTIMEOUT_2);
			}
			else
			{
				m_nRet = SQLSetConnectAttr(m_hCon, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)nLogin, SQL_IS_INTEGER);
				bRet = IsSuccess(m_nRet, SQL_HANDLE_DBC, m_hCon, ERROR_CON_SETTIMEOUT_3);
			}
		}

		if(nConnect >= 0)
		{//����Ǹ���,�Ͳ��ù���!
			m_nRet = SQLSetConnectAttr(m_hCon, SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)nConnect, SQL_IS_INTEGER);
			bRet = IsSuccess(m_nRet, SQL_HANDLE_DBC, m_hCon, ERROR_CON_SETTIMEOUT_4) || bRet;
		}
		else
		{
			return bRet;
		}
	}
	catch (...)
	{
		SetErrorInfo("����ϵͳ��ʱʱ��������", ERROR_CON_SETTIMEOUT_5);
		return false;
	}

	return bRet;
}


bool CConnection::ReConnect()
{
	try
	{
		//�Ͽ�����
		SQLDisconnect(m_hCon);
		m_bIsConnect = false;

		if(m_hEnv != INVALID_HANDLE_VALUE)
		{
			SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
			m_hEnv = INVALID_HANDLE_VALUE;
		}

		if(m_hCon != INVALID_HANDLE_VALUE)
		{
			SQLFreeHandle(SQL_HANDLE_DBC, m_hCon);
			m_hCon = INVALID_HANDLE_VALUE;
		}  
		m_bInit = false;

		if(!Init(m_nConnectTimeOut, m_nLoginTimeOut))
		{
			return false;
		}

		m_bIsConnect = false;
	}
	catch (...)
	{
		m_bIsConnect = false;
		m_bInit = false;
		return false;
	}

	return Connect(m_pszDNS, m_pszUser, m_pszPwd);
}

//add by stavck at 20051116
bool CConnection::IsConnect()
{ 
	//��������Ѿ��ֹ��Ͽ��ˣ������û�б�Ҫ�ټ���ˡ�
	if(!m_bIsConnect)
	{
		return false;
	}
	else
	{
		return true;
	}
	//�������������ݿ��������������ɾ����

	SQLINTEGER lRet = SQL_CD_TRUE;
	SQLINTEGER lRetSize = 0;
	try
	{
		//�ж������Ƿ���ţ������Ͽ�ʱһ��Ҫ�ȵ������ݿ���SQL�������п��ԡ�
		m_nRet = SQLGetConnectAttr(m_hCon, SQL_ATTR_CONNECTION_DEAD, (SQLPOINTER)&lRet, SQL_IS_INTEGER, &lRetSize);

		if(!IsSuccess(m_nRet, SQL_HANDLE_DBC, m_hCon, ERROR_CON_ISCONNECT_1))
		{
			return false;
		}

	}
	catch (...)
	{
		SetErrorInfo("��ѯϵͳ����ʱ��������", ERROR_CON_ISCONNECT_2);
		return false; 
	}

	//������Ȼ�ǻ��
	if(lRet == SQL_CD_FALSE)
	{
		return true;
	}

	//�����Ѿ��ϵ���
	return false;
}
//////////////////////////////////////////////////////////////////////////

CQuery::CQuery(CConnection** ppDBCon, int nQueryTimeOut )
{
	memset(m_pszLastError, 0x00, SQL_MAX_MESSAGE_LENGTH+100);
	m_nQueryTimeOut = 3;

	m_ppDBCon = ppDBCon; 

	m_nRet = SQL_SUCCESS;
	m_hStmt = INVALID_HANDLE_VALUE; 

	m_nQueryTimeOut = nQueryTimeOut;
}

CQuery::~CQuery()
{
	Close();
}


bool CQuery::Init()
{
	try
	{ 
		if (m_ppDBCon == NULL || *m_ppDBCon == NULL ||!(*m_ppDBCon)->IsConnect())
		{
			return false;
		}

		//����SQL�����
		m_nRet = SQLAllocHandle( SQL_HANDLE_STMT,
			(*m_ppDBCon)->m_hCon, &m_hStmt );

		if(!IsSuccess(m_nRet, SQL_HANDLE_DBC, 
			(*m_ppDBCon)->m_hCon, ERROR_QUERY_INIT_1))
		{
			m_hStmt = INVALID_HANDLE_VALUE; 
			return false;
		} 

		//ָ��Ҫʹ�õ��α겢������
		m_nRet = SQLSetStmtAttr(m_hStmt, SQL_ATTR_CONCURRENCY, 
			(SQLPOINTER) SQL_CONCUR_ROWVER, 0);
		if(!IsSuccess(m_nRet, SQL_HANDLE_STMT, m_hStmt, ERROR_QUERY_INIT_2))
		{
			Close(); 
			return false;
		}

		//���ù������Ϊ�������,
		//��������ܹ���⵽�е�ɾ�����޸ģ������޷���⵽��⵽�е���Ӻͽ����˳��仯��
		//��Ϊ�ڹ�괴��ʱ�ʹ������������������������м�¼��˳���Ѿ����̶���
		//��һ��;�̬���һ�������Լ���������˵��һ�ֽ��ھ�̬���Ͷ�̬���֮��Ĺ�����͡�
		m_nRet = SQLSetStmtAttr(m_hStmt, SQL_ATTR_CURSOR_TYPE, (SQLPOINTER) 
			SQL_CURSOR_DYNAMIC , 0);
		if(!IsSuccess(m_nRet, SQL_HANDLE_STMT, m_hStmt, ERROR_QUERY_INIT_3))
		{
			Close(); 
			return false;
		}

		m_nRet = SQLSetStmtAttr(m_hStmt, SQL_ATTR_QUERY_TIMEOUT, (SQLPOINTER)m_nQueryTimeOut, SQL_IS_UINTEGER);
		if(!IsSuccess(m_nRet, SQL_HANDLE_STMT, m_hStmt, ERROR_QUERY_INIT_5))
		{
			Close(); 
			return false;
		}

	}
	catch (...)
	{
		SetErrorInfo("��ʼ��ʱ��������", ERROR_QUERY_INIT_4);
		Close();
		return false;
	}

	return true;
}

void CQuery::Close()
{
	try
	{
		if(m_hStmt != INVALID_HANDLE_VALUE)
		{
			//�ͷž��
			//SQLFreeStmt(m_hStmt, SQL_DROP);
			SQLFreeHandle(SQL_HANDLE_STMT,m_hStmt);
			m_hStmt = INVALID_HANDLE_VALUE; 

		}
	}
	catch (...) 
	{
		m_hStmt = INVALID_HANDLE_VALUE;
	}
}


bool CQuery::GetErrorInfo(SQLSMALLINT nHandleType, SQLHANDLE nHandle, 
						  long lErrorCode)
{//����������Ҫ��һ��дһ�£�����ֻ��ȡ�����һ�еĴ�����Ϣ��
	bool bConnInd = nHandleType == SQL_HANDLE_DBC ? true :false;
	SQLRETURN nRet = SQL_SUCCESS;

	SQLCHAR pszSqlState[SQL_MAX_MESSAGE_LENGTH] = "";
	SQLCHAR pszErrorMsg[SQL_MAX_MESSAGE_LENGTH] = "";

	SQLINTEGER nNativeError = 0L;
	SQLSMALLINT nErrorMsg = 0;
	SQLSMALLINT nRecNmbr = 1;

	//ִ�д���ʱODBC���ص���һ��������Ϣ�Ľ��������Ҫ�������������������

	memset(pszSqlState, 0x00, sizeof(pszSqlState));
	memset(pszErrorMsg, 0x00, sizeof(pszErrorMsg));

	nRet = SQLGetDiagRec(nHandleType, nHandle,
		nRecNmbr, pszSqlState, &nNativeError,
		pszErrorMsg, SQL_MAX_MESSAGE_LENGTH - 1,
		&nErrorMsg);


	SetErrorInfo((char*)pszErrorMsg, lErrorCode);

	return true;
}

bool CQuery::IsSuccess(SQLRETURN nRet, SQLSMALLINT nHandleType,
					   SQLHANDLE nHandle, long lErrorCode)
{
	if(nRet == SQL_SUCCESS)
	{
		return true;
	}
	else if(nRet == SQL_SUCCESS_WITH_INFO)
	{//����ִ�гɹ����Ǵ���һ��������Ϣ,��ʱ��Ӧ�ü�¼��log��,����log�����վ���
		//GetErrorInfo(nHandleType, nHandle, lErrorCode, false);
		return true;
	}
	else
	{
		GetErrorInfo(nHandleType, nHandle, lErrorCode);
		return false;
	}

	return false; 
}

void CQuery::SetErrorInfo(const char *pszError, long lErrorCode)
{//�ȰѴ�������������Ϣ��,���������Ĵ�����Ϣ
	memset(m_pszLastError, 0x00, sizeof(m_pszLastError));
	char pszErrorCode[20] = "";
	//�����ô������
	sprintf((char*)pszErrorCode, "EC[%ld]", lErrorCode);
	int nLen = strlen((char*)pszErrorCode);
	strncpy((char*)m_pszLastError, (const char*)pszErrorCode, nLen);
	//���ܳ�������󳤶�,Ҫ����һ��
	size_t nMaxSize = sizeof(m_pszLastError)-1-nLen;

	strncat((char*)m_pszLastError, pszError, 
		nMaxSize>strlen(pszError)?strlen(pszError):nMaxSize);

}

bool CQuery::IsValid()
{
	return m_hStmt != INVALID_HANDLE_VALUE;
}

unsigned short CQuery::GetColumnCount()
{
	if(!IsValid())
	{
		SetErrorInfo("STMT��������ã�", ERROR_QUERY_GETCOLCOUNT_1);
		return 0;
	}

	short nCols=0;

	try
	{
		if(!IsSuccess(m_nRet = SQLNumResultCols(m_hStmt, &nCols), 
			SQL_HANDLE_STMT, m_hStmt, ERROR_QUERY_GETCOLCOUNT_2))
		{
			//������ɹ�,����0��
			return 0;
		}
	}
	catch (...) 
	{
		SetErrorInfo("ȡ���и���ʱ��������", ERROR_QUERY_GETCOLCOUNT_3);
		Close();
		return 0;
	}

	return nCols; 
}

long CQuery::GetChangedRowCount()
{//��select�������Ч��,��ѡ��ʹ��
	if(!IsValid())
	{
		SetErrorInfo("STMT��������ã�", ERROR_QUERY_GETCROWCOUNT_1);
		return 0;
	}

	long nRows=0;

	try
	{
		if(!IsSuccess(m_nRet = SQLRowCount(m_hStmt,&nRows), 
			SQL_HANDLE_STMT, m_hStmt, ERROR_QUERY_GETCROWCOUNT_2))
		{
			return 0;
		}
	}
	catch (...) 
	{
		SetErrorInfo("ȡ��Ӱ���¼���ĸ�����ʱ��������", ERROR_QUERY_GETCROWCOUNT_3);
		Close();
		return 0;
	}

	return nRows; 
}

bool CQuery::ExecuteSQL(const char* pszSQL)
{

	//��Ϊһ�������ֻ��ִ��һ��sql���,����,�����ͷŲ���ִ��
	if(IsValid())
	{//�����Ч,�ȹر�
		Close();
	}

	if(!Init())
	{//�ٳ�ʼ��
		return false;
	}

	if(!IsValid())
	{//��ʱ������?
		SetErrorInfo("STMT��������ã�", ERROR_QUERY_EXECSQL_1);
		return false;
	}

	try
	{
		//ִ����Ӧ��sql���
		m_nRet = SQLExecDirect(m_hStmt, (SQLTCHAR *)pszSQL, SQL_NTS);
	}
	catch (...) 
	{
		SetErrorInfo("ִ��SQL������!", ERROR_QUERY_EXECSQL_3);
		Close();
		return false;
	}

	return IsSuccess(m_nRet, SQL_HANDLE_STMT, m_hStmt, ERROR_QUERY_EXECSQL_2); 
}

bool CQuery::Fetch()
{
	if(!IsValid())
	{
		SetErrorInfo("STMT��������ã�", ERROR_QUERY_FETCH_1);
		return false;
	}

	try
	{
		m_nRet = SQLFetch(m_hStmt);
	}
	catch (...) 
	{
		SetErrorInfo("Fetch����!", ERROR_QUERY_FETCH_3);
		Close();
		return false;
	} 

	return IsSuccess(m_nRet, SQL_HANDLE_STMT, m_hStmt, ERROR_QUERY_FETCH_2);
}

bool CQuery::FecthNext()
{
	if(!IsValid())
	{
		SetErrorInfo("STMT��������ã�", ERROR_QUERY_FETCHNEXT_1);
		return false;
	}

	try
	{
		m_nRet = SQLFetchScroll(m_hStmt, SQL_FETCH_NEXT, 0);
	}
	catch (...) 
	{
		SetErrorInfo("FecthNext����!", ERROR_QUERY_FETCHNEXT_3);
		Close();
		return false; 
	} 

	return IsSuccess(m_nRet, SQL_HANDLE_STMT, m_hStmt, ERROR_QUERY_FETCHNEXT_2); 
}

bool CQuery::FetchPrevious()
{
	if(!IsValid())
	{
		SetErrorInfo("STMT��������ã�", ERROR_QUERY_FETCHPRE_1);
		return false;
	}

	try
	{
		m_nRet = SQLFetchScroll(m_hStmt, SQL_FETCH_PRIOR, 0);
	}
	catch (...) 
	{
		SetErrorInfo("FetchPrevious����!", ERROR_QUERY_FETCHPRE_3);
		Close();
		return false;
	} 

	return IsSuccess(m_nRet, SQL_HANDLE_STMT, m_hStmt, ERROR_QUERY_FETCHPRE_2); 
}

bool CQuery::FetchFirst()
{
	if(!IsValid())
	{
		SetErrorInfo("STMT��������ã�", ERROR_QUERY_FETCHFIRST_1);
		return false;
	}

	try
	{
		m_nRet = SQLFetchScroll(m_hStmt, SQL_FETCH_FIRST, 0);
	}
	catch (...) 
	{
		SetErrorInfo("FetchFirst����!", ERROR_QUERY_FETCHFIRST_3);
		Close();
		return false;
	} 

	return IsSuccess(m_nRet, SQL_HANDLE_STMT, m_hStmt, ERROR_QUERY_FETCHFIRST_2); 
}

bool CQuery::FetchLast()
{
	if(!IsValid())
	{
		SetErrorInfo("STMT��������ã�", ERROR_QUERY_FETCHLAST_1);
		return false;
	}

	try
	{
		m_nRet = SQLFetchScroll(m_hStmt,SQL_FETCH_LAST,0);
	}
	catch (...) 
	{
		SetErrorInfo("FetchLast����!", ERROR_QUERY_FETCHLAST_3);
		Close();
		return false;
	} 

	return IsSuccess(m_nRet, SQL_HANDLE_STMT, m_hStmt, ERROR_QUERY_FETCHLAST_2); 
}

bool CQuery::FetchRow(unsigned int nRow, bool bAbsolute )
{
	if(!IsValid())
	{
		SetErrorInfo("STMT��������ã�", ERROR_QUERY_FETCHROW_1);
		return false;
	}

	try
	{
		m_nRet = SQLFetchScroll(m_hStmt,
			(bAbsolute ? SQL_FETCH_ABSOLUTE : SQL_FETCH_RELATIVE), 
			nRow);
	}
	catch (...) 
	{
		SetErrorInfo("FetchRow����!", ERROR_QUERY_FETCHROW_3);
		Close();
		return false;
	}

	return IsSuccess(m_nRet, SQL_HANDLE_STMT, m_hStmt, ERROR_QUERY_FETCHROW_2);
}

bool CQuery::Cancel()
{
	if(!IsValid())
	{
		SetErrorInfo("STMT��������ã�", ERROR_QUERY_CANCEL_1);
		return true;
	}

	try
	{
		m_nRet = SQLCancel(m_hStmt);
	}
	catch (...)
	{
		SetErrorInfo("Cancel����!", ERROR_QUERY_CANCEL_3);
		Close();
		return false;
	}

	return IsSuccess(m_nRet, SQL_HANDLE_STMT, m_hStmt, ERROR_QUERY_CANCEL_2);
}

bool CQuery::GetData(unsigned short nColumn, void* pBuffer, 
					 unsigned long nBufLen,
					 long * nDataLen ,
					 int nType)
{
	if(nColumn <= 0 || nColumn > GetColumnCount() || pBuffer == NULL)
	{
		SetErrorInfo("�з�Χ���ԣ�����pBufferΪ�գ�", ERROR_QUERY_GETDATA_1);
		return false;
	}

	if(!IsValid())
	{
		SetErrorInfo("STMT��������ã�", ERROR_QUERY_GETDATA_2);
		return true;
	}

	SQLINTEGER nOutLen = 0;

	try
	{
		m_nRet = SQLGetData(m_hStmt, nColumn, nType, pBuffer, nBufLen, &nOutLen);
	}
	catch (...)
	{
		SetErrorInfo("GetData����!", ERROR_QUERY_GETDATA_5);
		Close();
		return false;
	}

	if(!IsSuccess(m_nRet, SQL_HANDLE_STMT, m_hStmt, ERROR_QUERY_GETDATA_3))
	{ 
		return false;
	}

	if(nDataLen)
	{
		*nDataLen=nOutLen;
	}

	return true; 
}

bool CQuery::GetData(const char* pszName, void* pBuffer, 
					 unsigned long nBufLen, 
					 long * nDataLen , 
					 int nType)
{
	if(pszName == NULL || pBuffer == NULL)
	{
		SetErrorInfo("PszName or pBuffer ����Ϊ�գ�", ERROR_QUERY_GETDATA_4);
		return false;
	}

	unsigned short nColumn = GetColumnByName(pszName);
	//��Ч���ж���GetData�Լ��ж�
	return GetData(nColumn, pBuffer, nBufLen, nDataLen, nType);
}

unsigned short CQuery::GetColumnByName(const char *pszColumn)
{
	if(!IsValid())
	{
		SetErrorInfo("STMT��������ã�", ERROR_QUERY_GETCOLBYNAME_1);
		return true;
	}

	unsigned short nCols = GetColumnCount();

	for(unsigned short i = 1; i < (nCols+1) ; i++)
	{//���εõ�ÿ���е��ֶ�����Ȼ��Ƚϡ�
		TCHAR pszName[256] = "";

		if(GetColumnName(i, pszName, sizeof(pszName)))
		{
			if(stricmp(pszName, pszColumn) == 0)
			{
				return i;
			}
		}
	}

	return 0;
}

bool CQuery::GetColumnName(unsigned short nColumn, char *pszName, short nNameLen)
{
	if(!IsValid())
	{
		SetErrorInfo("STMT��������ã�", ERROR_QUERY_GETCOLNAME_1);
		return true;
	}

	int nType = SQL_C_DEFAULT;
	SQLSMALLINT nSwCol=0, nSwType=0, nSwScale=0, nSwNull=0; //��Щ���ݣ�����������У����ǲ��ù���
	SQLUINTEGER pcbColDef=0;

	try
	{
		m_nRet = SQLDescribeCol( m_hStmt, nColumn,  
			(SQLTCHAR*)pszName, nNameLen,
			&nSwCol, &nSwType, &pcbColDef, 
			&nSwScale, &nSwNull); 
	}
	catch (...) 
	{
		SetErrorInfo("ȡ�ֶ�����ʱ����!", ERROR_QUERY_GETCOLNAME_3);
		Close();
		return false;
	}

	return  IsSuccess(m_nRet, SQL_HANDLE_STMT, m_hStmt, ERROR_QUERY_GETCOLNAME_2);
}

//////////////////////////////////////////////////////////////////////////

CDBAccess::CDBAccess()
{
	m_ppDBCon = NULL;
	memset(m_pszLastError, 0x00, sizeof(m_pszLastError));

	m_nConnectTimeOut = -1;
	m_nLoginTimeOut = -1;
	m_pQuery = NULL;
	m_bEnd = false;
	m_bCreateCon = false;
}

CDBAccess::~CDBAccess()
{
	if(m_pQuery != NULL)
	{
		delete m_pQuery;
		m_pQuery = NULL;
	} 
}

void CDBAccess::SetErrorInfo(const char *pszError, long lErrorCode)
{//�ȰѴ�������������Ϣ��,���������Ĵ�����Ϣ
	memset(m_pszLastError, 0x00, sizeof(m_pszLastError));
	char pszErrorCode[20] = "";
	//�����ô������
	sprintf((char*)pszErrorCode, "EC[%ld]", lErrorCode);
	int nLen = strlen((char*)pszErrorCode);
	strncpy((char*)m_pszLastError, (const char*)pszErrorCode, nLen);
	//���ܳ�������󳤶�,Ҫ����һ��
	size_t nMaxSize = sizeof(m_pszLastError)-1-nLen;

	strncat((char*)m_pszLastError, pszError, nMaxSize>strlen(pszError)?strlen(pszError):nMaxSize);

}

bool CDBAccess::Init(const char* pszSaveSQLFile, CConnection** ppDBCon,
					 int nConnectTimeOut , int nLoginTimeOut ,
					 int nQueryTimeOut )
{
	m_nLoginTimeOut = nLoginTimeOut;
	m_nConnectTimeOut = nConnectTimeOut;
	m_nQueryTimeOut = nQueryTimeOut;

	m_ppDBCon = ppDBCon;


	if((*ppDBCon) != NULL)
	{
		return true;
	}

	try
	{
		(*m_ppDBCon) = new CConnection;

		if ((*m_ppDBCon) == NULL)
		{
			SetErrorInfo("û���㹻���ڴ�!", ERROR_DBACCESS_INIT_1);
			return false;
		}

		m_bCreateCon = true;

		if(!(*m_ppDBCon)->Init(nConnectTimeOut, nLoginTimeOut))
		{
			delete (*m_ppDBCon);
			(*m_ppDBCon) = NULL;

			SetErrorInfo("���ݿ����ӳ�ʼ��ʧ��!", ERROR_DBACCESS_INIT_2);

			m_bCreateCon = false;

			return false;
		}

	}
	catch (...) 
	{
		SetErrorInfo("��ʼ��ʱ����!", ERROR_DBACCESS_INIT_3);
		return false; 
	}

	m_pQuery = new CQuery(m_ppDBCon, m_nQueryTimeOut);

	if(m_pQuery == NULL)
	{
		SetErrorInfo("û���㹻���ڴ�!", ERROR_DBACCESS_INIT_4);
		return false;
	}

	return true;
}

bool CDBAccess::Disconnect()
{
	if((*m_ppDBCon) == NULL)
	{
		SetErrorInfo("�����������ݿ�ʱ����!,���Ժ�����!", ERROR_DBACCESS_DISCONNECT_1);
		return false;
	}

	//ע��,�������Żع���,��ȷ�������Ѿ����ύ.
	if((*m_ppDBCon)->IsInTran())
	{
		(*m_ppDBCon)->EndTran(SQL_ROLLBACK);
	}

	return (*m_ppDBCon)->Disconnect();
}


bool CDBAccess::Connect(const char *pszDNS, const char *pszUser, const char *pszPwd)
{
	if((*m_ppDBCon) == NULL)
	{
		SetErrorInfo("��û�г�ʼ��,�����³�ʼ��������!", ERROR_DBACCESS_CONNECT_1);
		return false;
	}

	if(pszDNS == NULL)
	{
		SetErrorInfo("DNS����Ϊ��!", ERROR_DBACCESS_CONNECT_2);
		return false;
	}

	return (*m_ppDBCon)->Connect(pszDNS, pszUser, pszPwd);

}


bool CDBAccess::ReConnect()
{
	//add at 20051124 for �ر�ǰ�������Źر���������������ݿ�رպ��������Ч��
	m_pQuery->Close();

	return (*m_ppDBCon)->ReConnect();
}

bool CDBAccess::IsConnect()
{
	if((*m_ppDBCon) == NULL)
	{
		return false;
	}
	else
	{
		return (*m_ppDBCon)->IsConnect();
	}
}

void CDBAccess::Close()
{
	try
	{ 
		if(m_pQuery != NULL)
		{
			delete m_pQuery;
			m_pQuery = NULL;
		} 

		if(m_bCreateCon)
		{
			if((*m_ppDBCon) != NULL)
			{
				//ǿ�ƶϿ�,�ܰԵ���,һ��Ҫ��֤���е������ύ�ڶϿ�!
				delete (*m_ppDBCon);
				(*m_ppDBCon) = NULL;
			}
			m_bCreateCon = false;
		}

	}
	catch (...) 
	{
		//
	}
}


bool CDBAccess::ExecuteSQL(const char *pszSQL)
{

	if(!IsConnect())
	{
		SetErrorInfo("û�����ӵ����ݿ�,�޷�ִ��SQL���!", ERROR_DBACCESS_EXECUTESQL_1);
		return false;
	}

	bool bRet = false;

	try
	{ if(m_pQuery == NULL)
	{
		m_pQuery = new CQuery((m_ppDBCon), m_nQueryTimeOut);

		if(m_pQuery == NULL)
		{
			SetErrorInfo("û���㹻���ڴ�!", ERROR_DBACCESS_EXECUTESQL_2);
			return false;
		}
	}

	if (!m_pQuery->ExecuteSQL(pszSQL))
	{
		SetErrorInfo(m_pQuery->GetLastError(), ERROR_DBACCESS_EXECUTESQL_3);
		bRet = false;
	}
	else
	{
		bRet = true;
	}

	}
	catch (...) 
	{
		SetErrorInfo("ִ��ָ����SQL���ʱ����!", ERROR_DBACCESS_EXECUTESQL_5);

		return false; 
	}

	return bRet;
}
