#include "ODBC.h"

void ODBC::AllocateHandles()
{
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);


	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
	{
		// ODBC 드라이버 버전 명시

		retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		{

			// 연결 핸들러 할당

			retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);


			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
			{
				printf("Allocate Success\n");
			}

			else
			{

				SQLGetDiagRec(SQL_HANDLE_DBC, hdbc, ++rec, state, &native, message, sizeof(message), &length);

				printf("%s : %ld : %ld : %s\n", state, rec, native, message);

			}

		}

		else
		{

			SQLGetDiagRec(SQL_HANDLE_ENV, henv, ++rec, state, &native, message, sizeof(message), &length);

			printf("%s : %ld : %ld : %s\n", state, rec, native, message);

		}

	}

	else
	{

		SQLGetDiagRec(SQL_HANDLE_ENV, henv, rec, state, &native, message, sizeof(message), &length);

		printf("%s : %ld : %ld : %s\n", state, rec, native, message);

	}
}

void ODBC::ConnectDataSource()
{
	retcode = SQLConnect(hdbc, (SQLWCHAR*)"DESKTOP-MTOM02K", SQL_NTS, (SQLWCHAR*)"gkrhksdn", SQL_NTS, (SQLWCHAR*)"rhksdn", SQL_NTS);
}

void ODBC::ExecuteStatementDirect(SQLWCHAR* sql)
{
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
	{
		retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
		std::cout << "Connect Success" << std::endl;
	}
	else
	{
		SQLGetDiagRec(SQL_HANDLE_DBC, hdbc, ++rec, state, &native, message, sizeof(message), &length);
		printf("%s : %ld : %ld : %s\n", state, rec, native, message);
	}

	// 밑에 함수 호출 전에 명령 핸들 할당
	retcode = SQLExecDirect(hstmt, sql, SQL_NTS);

	if (retcode == SQL_SUCCESS)
		std::cout << "query success" << std::endl;
	else
	{
		SQLGetDiagRec(SQL_HANDLE_STMT, hstmt, ++rec, state, &native, message, sizeof(message), &length);
		printf("%s : %ld : %ld : %s\n", state, rec, native, message);
	}
}

void ODBC::PrepareStatement(SQLWCHAR* sql)
{
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
	{
		retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

		std::cout << "Connect Success" << std::endl;
	}
	else
	{
		SQLGetDiagRec(SQL_HANDLE_DBC, hdbc, ++rec, state, &native, message, sizeof(message), &length);
		printf("%s : %ld : %ld : %s\n", state, rec, native, message);
	}

	retcode = SQLPrepare(hstmt, sql, SQL_NTS);

	if (retcode == SQL_SUCCESS)
		std::cout << "Query prepare success" << std::endl;
	else
	{
		SQLGetDiagRec(SQL_HANDLE_DBC, hdbc, ++rec, state, &native, message, sizeof(message), &length);
		printf("%s : %ld : %ld : %s\n", state, rec, native, message);
	}
}

void ODBC::ExecuteStatement()
{
	retcode = SQLExecute(hstmt);

	if (retcode == SQL_SUCCESS)
		std::cout << "Query Execute Success" << std::endl;
	else
	{
		SQLGetDiagRec(SQL_HANDLE_DBC, hdbc, ++rec, state, &native, message, sizeof(message), &length);
		printf("%s : %ld : %ld : %s\n", state, rec, native, message);
	}
}

void ODBC::RetrieveResult()
{
	short Item_id = ' ';
	char Item_name[16] = " ";
	float Item_cal = 0.f;
	SQLLEN Iid, Ina, Ial;

	SQLBindCol(hstmt, 1, SQL_C_SHORT, &Item_id, sizeof(Item_id), &Iid);
	SQLBindCol(hstmt, 2, SQL_C_CHAR, &Item_id, sizeof(Item_name), &Ina);
	SQLBindCol(hstmt, 3, SQL_C_FLOAT, &Item_id, sizeof(Item_cal), &Ial);

	printf("id\tname\t\tcal\t\tstars");

	do
	{
		retcode = SQLFetch(hstmt); // 쿼리 결과값을 읽어오는 함수 // 마지막 로우까지 읽은 상태에서 한번 더 호출하면 NODATA 반환

		std::cout << Item_id << Item_name << Item_cal;
	} while (retcode != SQL_NO_DATA);

	SQLFreeStmt(hstmt, SQL_UNBIND);		// 명령문 관련 정보를 해제하는 함수

}

void ODBC::DisconnectDataSource()
{
	if (hstmt)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt);

		hstmt = NULL;
	}

	SQLDisconnect(hdbc);

	if (hdbc)
	{
		SQLFreeHandle(SQL_HANDLE_DBC, hdbc);

		hdbc = NULL;
	}

	if (henv)
	{
		SQLFreeHandle(SQL_HANDLE_ENV, henv);
		henv = NULL;
	}
}
