#pragma once
#include <Windows.h>
#include <sqlext.h>
#include <iostream>
#include <stdio.h>

class ODBC
{
private:
	SQLHENV henv;
	SQLHDBC hdbc;
	SQLHSTMT hstmt;
	SQLRETURN retcode;

	// for specific error
	SQLSMALLINT length;
	SQLINTEGER rec = 0, native;

	SQLWCHAR state[7], message[256];

public:
	void AllocateHandles();				// odbc �ڵ� ���� �ʱ�ȭ ���ִ� �Լ�
	void ConnectDataSource();			// ������ dbms�� �����ϴ� �Լ�
	void ExecuteStatementDirect(SQLWCHAR* sql);	// �������� ���ڷ� �޾� ������ �غ� �������� �����Ű�� �Լ��Դϴ�.
	void PrepareStatement(SQLWCHAR* sql);		// �������� �����Ű�� ���� ���� �غ� ������ ��ġ�� �Լ�, �غ� ������ ��ġ�� �ѹ� �����Ų �������� �ٽ� �����ų �� �ֱ� ������ ������ ����� ����� �غ������ ��ĥ��
	void ExecuteStatement();			// ���� �غ�� �������� �����Ű�� �Լ�
	void RetrieveResult();			// �������� ����� �д� �Լ� 
	void DisconnectDataSource();		// �Ҵ��ߴ� �ڵ��� ��� �����ϴ� �Լ�

};

