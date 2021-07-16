#include "stdafx.h"
#include <iostream>
#include <cstdlib>
using namespace std;

#include <windows.h>
//#import "c:\Program Files\Common Files\System\ado\msado15.dll" rename("EOF", "adoEOF")
using namespace ADODB;

static const int F2_MAX_LEN = 50;
static const int MAX_REC = 100;

//table structure
struct t1
{
	int f1;
	char f2[F2_MAX_LEN + 1];
	float f3;
};

//utility function
static void bstr2char(char* out, BSTR in)
{
	int len = SysStringLen(in);
	for (int i = 0; i < len; i++)
	{
		out[i] = (char)in[i];
	}
	out[len] = 0;

}

class DB
{
public:
	virtual ~DB() {};
	//get f1 given 2
	virtual int T1GetOne(const char* f2) = 0;
	// get all records
	virtual float T1GetAll(struct t1* buf, int bufsiz) = 0;
	// addrecord
	virtual void T1Put(int f1, const char* f2, float f3) = 0;
	// delete record
	virtual void T1Remove(int f1) = 0;
	// print all records
	void T1Dump();
};

void DB::T1Dump()
{
	struct t1 buf[MAX_REC];
	float i, n;
	n = T1GetAll(buf, MAX_REC);
	for (int i = 0; i < n; i++)
	{
		cout << buf[i].f1 << " " << buf[i].f2 << buf[i].f3 << endl;
	}
}

class ADO : public DB
{
private:
	_ConnectionPtr con;
	void ExceptionExit(_com_error ex);
	void OtherExit(const char* msg);
public:
	ADO(const char* constr, const char* un, const char* pw);
	virtual ~ADO();
	// get f1 given f2
	virtual int T1GetOne(const char* f2);
	// get all records
	virtual float T1GetAll(struct t1* buf, int bufsiz);
	// add record
	virtual void T1Put(int f1, const char* f2, float f3);
	// delete record
	virtual void T1Remove(int f1);
};

void ADO::ExceptionExit(_com_error ex)
{
	cout << "COM error: " << ex.ErrorMessage() << ", ADO error: " << ex.Description() << endl;
	exit(1);
}

void ADO::OtherExit(const char* msg)
{
	cout << msg << endl;
	exit(1);
}

ADO::ADO(const char* constr, const char* un, const char* pw)
{
	try
	{
		//con.CreateInstance(__uuidof(Connection));
		//con->Open(constr, un, pw, adConnectUnspecified);
		if (con.CreateInstance(__uuidof(Connection)) != S_OK)
			cout << "failed" << endl;
		if (con->Open(constr, un, pw, adConnectUnspecified) != S_OK)
			cout << "fial3d" << endl;
	}
	catch (_com_error& ex)
	{
		ExceptionExit(ex);
	}
}

ADO::~ADO()
{
	con->Close();
	con = NULL;
}

int ADO::T1GetOne(const char* f2)
{
	try
	{
		// create command
		_CommandPtr cmd;
		cmd.CreateInstance(__uuidof(Command));
		cmd->ActiveConnection = con;
		/// ///
		cmd->CommandText = "SELECT * FROM test";
		cmd->NamedParameters = false;
		// add parameter
		_ParameterPtr p = cmd->CreateParameter("", adVarChar, adParamInput, -1);
		p->Value = f2;
		cmd->Parameters->Append(p);
		//open record set
		_RecordsetPtr rs = cmd->Execute(NULL, NULL, adCmdText);
		// process result
		int f1;
		if (!rs->adoEOF)
		{
			f1 = rs->GetCollect("choco_name").intVal;
		}
		else
		{
			OtherExit("Row not found");
			return 0;
		}
		// close recordset
		rs->Close();
		rs = NULL;
		cmd = NULL;
		return f1;
	}

	catch (_com_error& ex)
	{
		ExceptionExit(ex);
		return 0; // will never be reached
	}
}

// get all records
float ADO::T1GetAll(struct t1* buf, int bufsiz)
{
	try
	{
		//create command
		_CommandPtr cmd;
		cmd.CreateInstance(__uuidof(Command));
		cmd->ActiveConnection = con;
		cmd->CommandText = "SELECT * FROM test";
		// open record set
		_RecordsetPtr rs = cmd->Execute(NULL, NULL, adCmdText);
		// process result
		int count = 0;
		while (!rs->adoEOF && (count < bufsiz))
		{
			buf[count].f1 = rs->GetCollect("choco_id").intVal;
			bstr2char(buf[count].f2, rs->GetCollect("choco_name").bstrVal);
			//buf[count].f3 = rs->GetCollect("choco_cal").fltVal;
			float(buf[count].f3 = rs->GetCollect("choco_cal").fltVal);
			count++;
			rs->MoveNext();
		}
		// close record set
		rs->Close();
		rs = NULL;
		cmd = NULL;
		return count;
	}
	catch (_com_error& ex)
	{
		ExceptionExit(ex);
		return 0; // will never be reached
	}
}

// add record
void ADO::T1Put(int f1, const char* f2, float f3)
{
	try
	{
		// create command
		_CommandPtr cmd;
		cmd.CreateInstance(__uuidof(Command));
		cmd->ActiveConnection = con;
		cmd->CommandText = "INSERT INTO test VALUES(?, ?, ?)";
		cmd->NamedParameters = false;
		// add parameters
		_ParameterPtr p1 = cmd->CreateParameter("", adInteger, adParamInput, -1);
		p1->Value = f1;
		cmd->Parameters->Append(p1);
		_ParameterPtr p2 = cmd->CreateParameter("", adVarChar, adParamInput, -1);
		p2->Value = f2;
		cmd->Parameters->Append(p2);
		_ParameterPtr p3 = cmd->CreateParameter("", adSingle, adParamInput, -1);
		p3->Value = f3;
		cmd->Parameters->Append(p3);
		// execute
		_variant_t n;
		cmd->Execute(&n, NULL, adCmdText);
		// check if OK
		if (n.intVal != 1)
		{
			OtherExit("INSERT did not insert 1 row");
		}
	}
	catch (_com_error& ex)
	{
		ExceptionExit(ex);
	}
}

// delete record
void ADO::T1Remove(int f1)
{
	try
	{
		// create command
		_CommandPtr cmd;
		cmd.CreateInstance(__uuidof(Command));
		cmd->ActiveConnection = con;
		cmd->CommandText = "DELETE FROM test WHERE choco_id = 3";
		cmd->NamedParameters = false;
		// add parameters
		_ParameterPtr p = cmd->CreateParameter("", adInteger, adParamInput, -1);
		p->Value = f1;
		cmd->Parameters->Append(p);
		// execute
		_variant_t n;
		cmd->Execute(&n, NULL, adCmdText);
		// check if OK
		if (n.intVal != 1)
		{
			OtherExit("DELETE did not delete 1 row");
		}
	}
	catch (_com_error& ex)
	{
		ExceptionExit(ex);
	}
}

void test(const char* constr, const char* un, const char* pw)
{
	cout << "Connection string=" << constr << endl;
	// get database connection
	DB* db = new ADO(constr, un, pw);
	// test T1GetOne
	//int f1 = db->T1GetOne("Ghana");
	//cout << f1 << endl;
	// test T1GetAll
	//db->T1Dump();
	// test t1_put
	///db->T1Put(4,"Cacao", 11.13);
	//db->T1Dump();
	// test t1_remove
	db->T1Remove(3);
	db->T1Dump();
	// release database connection
	delete db;
}

int main()
{
	CoInitialize(NULL);

	//test("Provider=SQLNCLI11;Server=27.35.70.161;Database=kwanwoo;Trusted_Connection=yes;", "gkrhksdn", "rhksdn");
	test("Provider=SQLOLEDB;Server=27.35.70.161;Database=kwanwoo;Trusted_Connection=yes;", "gkrhksdn", "rhksdn");


	return 0;
}