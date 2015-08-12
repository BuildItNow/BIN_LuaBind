#include "Example_Handle.h"

#include "ExampleManager.h"

#include "Public.hpp"

class CTestClass
{
	DECLARE_SCRIPT_CLASS();
public:
	std::string Name()
	{
		return "TestClass";
	}
};

namespace bin
{
	BEGIN_SCRIPT_CLASS(HandleTestClass, CTestClass)
		DEFINE_CLASS_FUNCTION(name, std::string, ())
		{
			r = obj->Name();
			return 1;
		}

		DEFINE_STATIC_FUNCTION(newInstance, CTestClass*, ())
		{
			r = new CTestClass;
			r->GetScriptObject().SetDelByScr(true);

			return 1;
		}
	END_SCRIPT_CLASS()
}


void CExample_Handle::Do()
{
	// Init a lua handle
	bin::CScriptHandle luaHandle;
	

	//
	// init
	//	from file, from string, from lua_state
	luaHandle.Init();

	// exec
	//	string, file
	luaHandle.ExecString("print('ExecString')");
	
	// exec with result
	//	string, file
	{
		bin::CScriptTable ret;
		luaHandle.ExecString("return 'value0', {value='value1'}, 2 ", ret);

		std::string v0;
		bin::CScriptTable v1;
		int v2;
		
		ret.Get(1, v0);
		ret.Get(2, v1);	
		ret.Get(3, v2);

		printf("ExecString with result : [%s] [lua_State:0x%x] [%d]\n", v0.c_str(), (int)v1.GetHandle(), v2);
	}
	// get 
	//	bool, int, double, string, const char*
	//  table, userdata, script object
	{
		luaHandle.ExecString("a,b,c,d, e= true, 10, 3.14, 'string : Hello BIN_LuaBind', 'char* : Hello BIN_LuaBind' ");

		bool a;
		int  b;
		double c;
		std::string d;
		const char* e;

		luaHandle.Get("a", a);
		luaHandle.Get("b", b);
		luaHandle.Get("c", c);
		luaHandle.Get("d", d);
		luaHandle.Get("e", e);

		printf("Get a[%s] b[%d] c[%f] d[%s] e[%s]\n", a ? "true" : "false", b, c, d.c_str(), e);

		luaHandle.ExecString("a = {a='table value'}");
		
		bin::ScriptExporterManager().ExportClass("HandleTestClass", luaHandle);
		luaHandle.ExecString("b = bin_types.HandleTestClass.newInstance()");

		bin::CScriptTable		tbl;
		bin::CScriptUserData	ud;
		luaHandle.Get("a", tbl);
		luaHandle.Get("b", ud);

		std::string tblValue;
		std::string udValue;
		tbl.Get("a", tblValue);
		ud.CallMemFunc("name", udValue);

		printf("Get tableValue[%s] userdataValue[%s]\n", tblValue.c_str(), udValue.c_str());
	}
	// set
	//	bool, int, double, string, const char*
	//	table, userdata, script object
	// call function
	// 

	// release
}

REGISTE_EXAMPLE(CExample_Handle);