#include "TestWorkerOTLBlob.h"

#include <iostream>
#include <sstream>
#include <time.h>
#include <vector>	
#include <list>  
#include <time.h>
#include <sys/timeb.h>
#include <limits.h>
#include <float.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ProjectCommonData.h"
#include "BaseLogger.h"
#include "BuildSQLHelper.h"
#include "BuildSQLHelperBlob.h"



//TestClass
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <otlv4.h> // include the OTL 4 header file


//////////////////////////////////////////////////////////////////////////



CTestWorkerOTLBlob::CTestWorkerOTLBlob( void )
{
	m_nDBType = DB_ORACLE;
	m_pConnection = NULL;
	m_pBuildSQLHelperBlob = NULL;
	m_pBuildSQLHelperBlob = new CBuildSQLHelperBlob();
	m_pBuildSQLHelperBlob->setDBType(m_nDBType);

}

CTestWorkerOTLBlob::~CTestWorkerOTLBlob( void )
{
	if (NULL != m_pConnection)
	{
		delete m_pConnection;
		m_pConnection = NULL;
	}

	if (NULL != m_pBuildSQLHelperBlob)
	{
		delete m_pBuildSQLHelperBlob;
		m_pBuildSQLHelperBlob = NULL;
	}
}


void CTestWorkerOTLBlob::SetDBType( enDBType nDBType )
{
	m_nDBType = nDBType;
	m_pBuildSQLHelperBlob->setDBType(m_nDBType);

}

//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
template<class T>
std::string CTestWorkerOTLBlob::t_to_string(const T& t)
{
	std::string strValue;
	std::ostringstream oss;//创建一个流
	oss<<t;//把值传递如流中
	strValue = oss.str();//获取转换后的字符转并将其写入result
	return strValue;
}

int CTestWorkerOTLBlob::_GetColumnCount(otl_stream* pQuery)
{
	otl_column_desc* p_otl_column_desc = NULL;
	int nColumnCount = 0;//nColumnCount;
	p_otl_column_desc = pQuery->describe_select(nColumnCount);
	if(!p_otl_column_desc)
	{
		throw otl_exception(otl_error_msg_21,otl_error_code_21);
	}
	return nColumnCount;

}
std::string CTestWorkerOTLBlob::_GetColumnName(otl_stream* pQuery, int nColumnIndex)
{
	std::string strValue;
	otl_column_desc* p_otl_column_desc = NULL;
	int nColumnCount = 0;//nColumnCount;
	p_otl_column_desc = pQuery->describe_select(nColumnCount);
	if(!p_otl_column_desc)
	{
		throw otl_exception(otl_error_msg_21,otl_error_code_21);
	}

	const otl_column_desc& curr_var=p_otl_column_desc[nColumnIndex];
	strValue = curr_var.name;
	return strValue;
}
std::string CTestWorkerOTLBlob::_GetColumnValue(otl_stream* pQuery, int nColumnIndex)
{
	std::string strValue;
	otl_column_desc* p_otl_column_desc = NULL;
	int nColumnCount = 0;//nColumnCount;
	p_otl_column_desc = pQuery->describe_select(nColumnCount);
	if(!p_otl_column_desc)
	{
		throw otl_exception(otl_error_msg_21,otl_error_code_21);
	}

	otl_long_string* p_otl_long_string = NULL;
	char* pszTemp = NULL;
	otl_datetime* p_otl_datetime = NULL;
	double varValue_double = 0;
	float varValue_float = 0;			
	int varValue_int = 0;
	unsigned int varValue_unsigned_int = 0;
	short int varValue_short_int = 0;
	long varValue_long = 0;
	std::ostringstream datatime_ss;//创建一个流
	char* szTemp = NULL;
	std::basic_string<unsigned char> uchArray;
	std::string strArray;


	//otl_null();
	if(pQuery->is_null())
	{
		strValue = "column have not data, NULL";
		return strValue;
	}

	//for(int nColumnIndex = 0; nColumnIndex < nColumnCount; ++nColumnIndex)
	{
		const otl_column_desc& curr_var=p_otl_column_desc[nColumnIndex];
		switch(curr_var.otl_var_dbtype)
		{
		case otl_var_char:
			{
				pszTemp=new char[curr_var.dbsize];
				*pszTemp=0;
				(*pQuery)>>pszTemp;

				strValue = t_to_string(pszTemp);

				delete[] pszTemp;
				pszTemp = NULL;
			}
			break;
		case otl_var_raw:
			p_otl_long_string = new otl_long_string(curr_var.dbsize);
			(*pQuery)>>(*p_otl_long_string);

			delete p_otl_long_string;
			p_otl_long_string = NULL;
			break;
		case otl_var_double:
			(*pQuery)>>varValue_double;
			strValue = t_to_string(varValue_double);
			break;
		case otl_var_float:
			(*pQuery)>>varValue_float;
			strValue = t_to_string(varValue_float);
			break;
		case otl_var_int:
			(*pQuery)>>varValue_int;
			strValue = t_to_string(varValue_int);
			break;
		case otl_var_unsigned_int:
			(*pQuery)>>varValue_unsigned_int;
			strValue = t_to_string(varValue_unsigned_int);
			break;
		case otl_var_short:
			(*pQuery)>>varValue_short_int;
			strValue = t_to_string(varValue_short_int);
			break;
		case otl_var_long_int:
			(*pQuery)>>varValue_long;
			strValue = t_to_string(varValue_long);
			break;
		case otl_var_timestamp:
		case otl_var_db2time:
		case otl_var_db2date:
		case otl_var_tz_timestamp:
		case otl_var_ltz_timestamp:
			p_otl_datetime = new otl_datetime();
			(*pQuery)>>(*p_otl_datetime);
			//strValue = t_to_string(varValue);
			datatime_ss<<p_otl_datetime->year<<"-"<<p_otl_datetime->month<<"-"<<p_otl_datetime->day
				<<" "<<p_otl_datetime->hour<<":"<<p_otl_datetime->minute<<":"<<p_otl_datetime->second;
			strValue = datatime_ss.str();
			delete p_otl_datetime;
			p_otl_datetime = NULL;
			break;
		case otl_var_varchar_long:
		case otl_var_raw_long:
		case otl_var_clob:
		case otl_var_blob:
			p_otl_long_string = new otl_long_string(pQuery->get_adb_max_long_size());
			(*pQuery)>>(*p_otl_long_string);

			szTemp = new char[p_otl_long_string->len() + 1];
			memset(szTemp, 0, p_otl_long_string->len() + 1);

			memcpy(szTemp, p_otl_long_string->v, p_otl_long_string->len());


			uchArray.clear();
			uchArray.append(p_otl_long_string->v, p_otl_long_string->len());


			strValue.clear();
			strValue.append((char*)(p_otl_long_string->v), p_otl_long_string->len());

			delete[] szTemp;
			szTemp = NULL;

			delete p_otl_long_string;
			p_otl_long_string = NULL;
			break;
#if defined(OTL_BIGINT)
		case otl_var_bigint:
			//out_vars_arr_[nColumnIndex]=OTL_RCAST(unsigned char*,new OTL_BIGINT(0));
			break;
#endif
#if defined(OTL_UBIGINT)
		case otl_var_ubigint:
			//out_vars_arr_[nColumnIndex]=OTL_RCAST(unsigned char*,new OTL_UBIGINT(0));
			break;
#endif
#if defined(OTL_NUMERIC_TYPE_1) && defined(OTL_STR_TO_NUMERIC_TYPE_1) && defined(OTL_NUMERIC_TYPE_1_TO_STR) && defined(OTL_NUMERIC_TYPE_1_ID)
		case otl_var_numeric_type_1:
			//out_vars_arr_[nColumnIndex]=OTL_RCAST(unsigned char*,new OTL_NUMERIC_TYPE_1(0));
			break;
#endif
#if defined(OTL_NUMERIC_TYPE_2) && defined(OTL_STR_TO_NUMERIC_TYPE_2) && defined(OTL_NUMERIC_TYPE_2_TO_STR) && defined(OTL_NUMERIC_TYPE_2_ID)
		case otl_var_numeric_type_2:
			//out_vars_arr_[nColumnIndex]=OTL_RCAST(unsigned char*,new OTL_NUMERIC_TYPE_2(0));
			break;
#endif
#if defined(OTL_NUMERIC_TYPE_3) && defined(OTL_STR_TO_NUMERIC_TYPE_3) && defined(OTL_NUMERIC_TYPE_3_TO_STR) && defined(OTL_NUMERIC_TYPE_3_ID)
		case otl_var_numeric_type_3:
			//out_vars_arr_[nColumnIndex]=OTL_RCAST(unsigned char*,new OTL_NUMERIC_TYPE_3(0));
			break;
#endif
		}//switch
	}//for

	return strValue;
}//construct_elements



void CTestWorkerOTLBlob::fillDataBuffer(otl_connect *pconnection, otl_stream* pQuery, int numColumns, long lMaxRows )
{
	int nColumnCount = 0;//nColumnCount;
	int nRowIndex = 0;
	DataClobArray data;
	//otl_lob_stream lobstr;

	nColumnCount = _GetColumnCount(pQuery);

	_BaseLog(BaseLogSourceFLInfo, DebugDebug, "[nColumnCount=%d]", nColumnCount);

	// Get results from statement
	try
	{
		//nRecordIndex begin with 1   nFieldIndex begin with 1
		nRowIndex = 1;
		_BaseLog(BaseLogSourceFLInfo, DebugTrace,"do_select_data  nRowIndex=%d", nRowIndex);

		//oracle.otl_stream_read_iterator.get 
		if (! pQuery->eof())
		{
			//1
		}

		while(! pQuery->eof())
		{
			for(int nColumnIndex = 0; nColumnIndex < nColumnCount; ++nColumnIndex)
			{
				std::string strColumnName;
				std::string strColumnValue;

				strColumnName = _GetColumnName(pQuery, nColumnIndex);
				strColumnValue = _GetColumnValue(pQuery, nColumnIndex);

				DataClob dataclob;
				std::copy(strColumnValue.begin(), strColumnValue.end(), std::back_inserter(dataclob));
				data.push_back(dataclob);

				_BaseLog(BaseLogSourceFLInfo, DebugDebug, "[nRowIndex=%d][nColumnIndex=%d][strColumnName=%s][strColumnValue=%s]",
					nRowIndex, nColumnIndex, strColumnName.c_str(),strColumnValue.c_str());
			}//for


			++nRowIndex;
		}//while

	}
	catch (otl_exception& p)
	{ 
		// intercept OTL exceptions
		_BaseLog(BaseLogSourceFLInfo, DebugError, 
			"Oracle fillDataBuffer(msg:%s, stm_text: %s, sqlstate: %s, var_info: %s)", 
			p.msg, p.stm_text, p.sqlstate, p.var_info); 
	}
	catch( ... )
	{
		_BaseLog(BaseLogSourceFLInfo, DebugError, "fillDataBuffer UNKNOWN ERROR");
	}

	_BaseLog(BaseLogSourceFLInfo, DebugInfo,"do_select_data  Total=%d", nRowIndex);


}//CTestClass::fillDataBuffer



void CTestWorkerOTLBlob::fetchInitial(otl_connect *pconnection, otl_stream* pQuery, int numColumns, long lMaxRows )
{
	try
	{
		{
			fillDataBuffer(pconnection, pQuery, numColumns, lMaxRows);
		}
	}
	catch(...)
	{
		_BaseLog(BaseLogSourceFLInfo, DebugDebug, "fetchInitial UNKNOWN ERROR");
	}


}//CTestClass::fetchInitial

void CTestWorkerOTLBlob::exec(otl_connect *pconnection, const std::string& strOracleSQL, bool isQuery)
{
	int prefetch = 100;
	std::string strSql = strOracleSQL;
	long nRowsAffected = 0;
	//LOG_GENERIC(SourceInfo, DebugUtil::DebugSQL, "Begin execute the SQL statement: [[%s]]", strSql.c_str());
	otl_stream* pSelectStream = NULL;



	nRowsAffected = 0;

	try
	{

		if (isQuery) //select *
		{
			pSelectStream = new otl_stream();
			pconnection->auto_commit_off();
			pSelectStream->open(prefetch, strOracleSQL.c_str(), *pconnection);
//			pSelectStream->flush(); //立即执行操作，尽管当前流中只有一条记录
			pconnection->commit();
		}
		else //like the insert command
		{
			// OCI连接器// SQL语句// 禁止OTL异常  
			//nRowsAffected = otl_cursor::direct_exec(*pconnection, strOracleSQL->c_str(),otl_exception::enabled); // drop table
			pconnection->auto_commit_off();
			nRowsAffected = pconnection->direct_exec(strOracleSQL.c_str(), otl_exception::enabled);
			pconnection->commit();
		}
	}
	catch (otl_exception& p)
	{ 
		pconnection->rollback();
		// intercept OTL exceptions
		_BaseLog(BaseLogSourceFLInfo, DebugError, 
			"Oracle exe(msg:%s, stm_text: %s, sqlstate: %s, var_info: %s)", 
			p.msg, p.stm_text, p.sqlstate, p.var_info); 
	}
	catch(...)
	{
		_BaseLog(BaseLogSourceFLInfo, DebugDebug, "exec UNKNOWN ERROR");
	}	

	//isQuery == true
	//just save the pointer, here
	//"SELECT LINE_ID, TEST_TYPE, BLOB_COLUMN, CLOB_COLUMN FROM TABLE_TEST_DAITEST";
	if (isQuery && NULL != pSelectStream)
	{
		std::string strColumnName;
		int numColumns = 0;
		int nRecordCount = 0;
		std::list<std::string> lstColumns;

		strColumnName = "LINE_ID";
		lstColumns.push_back(strColumnName);

		strColumnName = "TEST_TYPE";
		lstColumns.push_back(strColumnName);

		strColumnName = "BLOB_COLUMN";
		lstColumns.push_back(strColumnName);

		strColumnName = "CLOB_COLUMN";
		lstColumns.push_back(strColumnName);


		numColumns = (int)lstColumns.size();
		//pSelectStream->get_prefetched_row_count();
		//nRecordCount = query->recordCount();
		nRecordCount = 10000;

		fetchInitial(pconnection, pSelectStream, numColumns, nRecordCount);

		pSelectStream->close();
		delete pSelectStream;
		pSelectStream = NULL;

		lstColumns.clear();

	}//if ( NULL != query )

}//CTestClass::exec



//////////////////////////////////////////////////////////////////////////


int CTestWorkerOTLBlob::do_disconnect_to_db()
{
	int nFunRes = 0;

	if (NULL != m_pConnection)
	{
		if (m_pConnection->connected)
		{
			m_pConnection->logoff(); // disconnect from Oracle
		}
		delete m_pConnection;
		m_pConnection = NULL;
	}

	return nFunRes;
}

int CTestWorkerOTLBlob::do_connect_to_db()
{
	int nFunRes = 0;
	bool bFunRes = false;

	if (NULL != m_pConnection)
	{
		if (m_pConnection->connected)
		{
			m_pConnection->logoff(); // disconnect from Oracle
		}
		delete m_pConnection;
		m_pConnection = NULL;
	}

	


	try
	{
		int threaded_mode = 1;
		otl_connect::otl_initialize(threaded_mode); // initialize OCI environment

		if (NULL == m_pConnection)
		{	
			//"IT271350_5/IT271350_5@TRANSACT"
			std::string strConstr = m_pBuildSQLHelperBlob->m_strUSR + "/" + m_pBuildSQLHelperBlob->m_strPWD + "@" + m_pBuildSQLHelperBlob->m_databaseName;
			m_pConnection = new otl_connect();
			//[User Name]/[Password]@[TNS Alias]
			//m_pConnection->rlogon("IT271350_5/IT271350_5@TRANSACT", 0); // connect to Oracle
			m_pConnection->rlogon(strConstr.c_str(), 0); // connect to Oracle
			m_pConnection->auto_commit_off();

		}

	}
	catch (otl_exception& p)
	{ 
		
		// intercept OTL exceptions
		_BaseLog(BaseLogSourceFLInfo, DebugError, "Oracle connecterror(msg:%s, stm_text: %s, sqlstate: %s, var_info: %s)", 
			p.msg, p.stm_text, p.sqlstate, p.var_info); 
// 		cerr<<p.msg<<endl; // print out error message
// 		cerr<<p.stm_text<<endl; // print out SQL that caused the error
// 		cerr<<p.var_info<<endl; // print out the variable that caused the error
	}
	catch(...)  
	{  
		_BaseLog(BaseLogSourceFLInfo, DebugError, "COCIConnect::Connect error: Unknown error");	
	}  

	return nFunRes;
}



int CTestWorkerOTLBlob::do_delete_table()
{
	int nFunRes = 0;
	bool bFunRes = false;
	std::string strSQL;
	bool isQuery = false;

	// Execute a direct query
	strSQL = m_pBuildSQLHelperBlob->build_SQL_DeleteTable();

	isQuery = false;
	exec(m_pConnection, strSQL, isQuery);
	return nFunRes;
}

int CTestWorkerOTLBlob::do_create_table()
{
	int nFunRes = 0;
	bool bFunRes = false;
	std::string strSQL;
	bool isQuery = false;


	// Execute a direct query
	strSQL = m_pBuildSQLHelperBlob->build_SQL_CreateTable();
	isQuery = false;
	exec(m_pConnection, strSQL, isQuery);

	return nFunRes;
}

int CTestWorkerOTLBlob::do_insert_data(int nCount)
{
	int nFunRes = 0;
	bool bFunRes = false;
	std::string strSQL;
	int nParam_LineID_Value = 1000;
	int nIndex = 0;
	bool isQuery = false;


	for (nIndex = 0; nIndex < nCount; nIndex++)
	{

		// Execute a direct query
		nParam_LineID_Value = nIndex;
		strSQL = m_pBuildSQLHelperBlob->build_SQL_InsertData(nParam_LineID_Value);

		isQuery = false;
		exec(m_pConnection, strSQL, isQuery);

		{
			_BaseLog(BaseLogSourceFLInfo, DebugTrace,"do_insert_data  nIndex=%d", nIndex);
		}

	}//for
	_BaseLog(BaseLogSourceFLInfo, DebugInfo,"do_insert_data  Total=%d", nCount);


	return nFunRes;
}

int CTestWorkerOTLBlob::do_select_data()
{
	int nFunRes = 0;
	bool bFunRes = false;
	std::string strSQL;
	int nRowIndex = 0;
	bool isQuery = true;

	// Execute a direct query
	strSQL = m_pBuildSQLHelperBlob->build_SQL_SelectDataFromTable();
	isQuery = true;
	exec(m_pConnection, strSQL, isQuery);

	return nFunRes;
}




int CTestWorkerOTLBlob::do_update_data()
{
	int nFunRes = 0;
	bool bFunRes = false;
	std::string strSQL;
	int nParam_LineID_Value = 1000;
	int nIndex = 0;
	bool isQuery = false;


	//for (nIndex = 0; nIndex < nCount; nIndex++)
	{

		// Execute a direct query
		nParam_LineID_Value = nIndex;
		strSQL = m_pBuildSQLHelperBlob->build_SQL_UpdateData();

		isQuery = false;
		exec(m_pConnection, strSQL, isQuery);

		{
			_BaseLog(BaseLogSourceFLInfo, DebugTrace,"do_update_data  nIndex=%d", nIndex);
		}

	}//for
	_BaseLog(BaseLogSourceFLInfo, DebugInfo,"do_update_data  Total=%d", 1);


	return nFunRes;
}

int CTestWorkerOTLBlob::do_update_data_ex()
{
	int nFunRes = 0;
	bool bFunRes = false;
	std::string strSQLSelectForUpdate;
	otl_stream strSelectForUpdate;
	std::string strSQLUpdate;
	int nParam_LineID_Value = 1000;
	int nIndex = 0;
	bool isQuery = false;
	int nRowsAffected = 0;
	int buffer_size = 512;
	otl_long_string otlLongStr(buffer_size);

	memcpy(otlLongStr.v, "MMMM", strlen("MMMM"));
	otlLongStr.set_len(strlen("MMMM"));

	strSQLSelectForUpdate = "SELECT BLOB_COLUMN,CLOB_COLUMN FROM TABLE_TEST_DAITEST WHERE LINE_ID=1 FOR UPDATE";
	m_pConnection->auto_commit_off();
	strSelectForUpdate.open(1, strSQLSelectForUpdate.c_str(), *m_pConnection);
	strSelectForUpdate.flush();
	//nRowsAffected = m_pConnection->direct_exec(strSQL.c_str(), otl_exception::enabled);

	strSQLUpdate = "UPDATE TABLE_TEST_DAITEST SET BLOB_COLUMN='BBBB',CLOB_COLUMN='BBBB' WHERE LINE_ID= 1";
	nRowsAffected = m_pConnection->direct_exec(strSQLUpdate.c_str(), otl_exception::enabled);
	m_pConnection->commit();

	_BaseLog(BaseLogSourceFLInfo, DebugInfo,"do_update_data  Total=%d", 1);


	return nFunRes;
}



int CTestWorkerOTLBlob::do_update_data_ex_setdata()
{
	int nFunRes = 0;
	bool bFunRes = false;
	std::string strSQLSelectForUpdate;
	otl_stream strSelectForUpdate;
	otl_stream strUpdate;
	std::string strSQLUpdate;
	
	int nRowsAffected = 0;
	int buffer_size = 512;
	otl_long_string otlLongStr(buffer_size);
	otl_lob_stream blob_lob;
	otl_lob_stream clob_lob;

	memcpy(otlLongStr.v, "MMMM", strlen("MMMM"));
	otlLongStr.set_len(strlen("MMMM"));


	strSQLSelectForUpdate = "SELECT BLOB_COLUMN,CLOB_COLUMN FROM TABLE_TEST_DAITEST WHERE LINE_ID=1 FOR UPDATE";
	//m_pConnection->auto_commit_off();
	strSelectForUpdate.open(1, strSQLSelectForUpdate.c_str(), *m_pConnection);
	strSelectForUpdate.set_commit(0);
	//strSelectForUpdate.flush();
	//nRowsAffected = m_pConnection->direct_exec(strSQL.c_str(), otl_exception::enabled);


	//strSQLUpdate = "UPDATE TABLE_TEST_DAITEST SET BLOB_COLUMN=:BLOBVALUE<BLOB>,CLOB_COLUMN=:CLOBVALUE<CLOB> WHERE LINE_ID= 1";
	//strSQLUpdate = "UPDATE TABLE_TEST_DAITEST SET BLOB_COLUMN=empty_blob(),CLOB_COLUMN=empty_clob() WHERE LINE_ID= 1 returning BLOB_COLUMN into :BLOB_COLUMN<BLOB>, CLOB_COLUMN into :CLOB_COLUMN<CLOB>";//error
	strSQLUpdate = "UPDATE TABLE_TEST_DAITEST SET BLOB_COLUMN=empty_blob(),CLOB_COLUMN=empty_clob() WHERE LINE_ID= 1 returning BLOB_COLUMN, CLOB_COLUMN into :BLOB_COLUMN<BLOB>, :CLOB_COLUMN<CLOB>";
	strUpdate.open(1, strSQLUpdate.c_str(), *m_pConnection);
	strUpdate.set_commit(0);

	strUpdate<<blob_lob;
	strUpdate<<clob_lob;// Initialize otl_lob_stream by writing it into otl_stream.

	blob_lob.set_len(otlLongStr.len());//// setting the total size of of the BLOB to be written
	clob_lob.set_len(otlLongStr.len());//// setting the total size of of the CLOB to be written
	blob_lob<<otlLongStr;
	clob_lob<<otlLongStr;

	//strUpdate<<otlLongStr;
	//strUpdate.flush();
	//nRowsAffected = m_pConnection->direct_exec(strSQLUpdate.c_str(), otl_exception::enabled);
	m_pConnection->commit();

	_BaseLog(BaseLogSourceFLInfo, DebugInfo,"do_update_data  Total=%d", 1);


	return nFunRes;
}


