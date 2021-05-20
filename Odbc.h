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
	void AllocateHandles();				// odbc 핸들 변수 초기화 해주는 함수
	void ConnectDataSource();			// 연결할 dbms에 접속하는 함수
	void ExecuteStatementDirect(SQLWCHAR* sql);	// 쿼리문을 인자로 받아 쿼리문 준비 과정없이 실행시키는 함수입니다.
	void PrepareStatement(SQLWCHAR* sql);		// 쿼리문을 실행시키기 위해 따로 준비 과정을 거치는 함수, 준비 과정을 거치면 한번 실행시킨 쿼리문을 다시 실행시킬 수 있기 때문에 여러번 사용할 경우라면 준비과정을 거칠것
	void ExecuteStatement();			// 실행 준비된 쿼리문을 실행시키는 함수
	void RetrieveResult();			// 쿼리문의 결과를 읽는 함수 
	void DisconnectDataSource();		// 할당했던 핸들을 모두 해제하는 함수

};

