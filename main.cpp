#include <Windows.h>
#include "Odbc.h"


//// ODBC//////
int main()
{
	ODBC odbc;

	odbc.AllocateHandles();
	odbc.ConnectDataSource();
	odbc.ExecuteStatementDirect((SQLWCHAR*)"SELECT * FROM Item_table");
	odbc.RetrieveResult();
	odbc.DisconnectDataSource();

	return 0;
}



///////////////