#include "ODBC.h"

void ODBC::AllocateHandles()
{
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);


	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
	{
		// ODBC ����̹� ���� ���

		retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		{

			// ���� �ڵ鷯 �Ҵ�

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

	// �ؿ� �Լ� ȣ�� ���� ��� �ڵ� �Ҵ�
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
		retcode = SQLFetch(hstmt); // ���� ������� �о���� �Լ� // ������ �ο���� ���� ���¿��� �ѹ� �� ȣ���ϸ� NODATA ��ȯ

		std::cout << Item_id << Item_name << Item_cal;
	} while (retcode != SQL_NO_DATA);

	SQLFreeStmt(hstmt, SQL_UNBIND);		// ��ɹ� ���� ������ �����ϴ� �Լ�

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
