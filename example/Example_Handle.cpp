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

	{
		luaHandle.Release();
		luaHandle.Init();

		bool a = false;
		int  b = 2015;
		double c = 3.1415926;
		std::string d = "Hello string";
		const char* e = "Hello char*";

		luaHandle.Set("a", a);
		luaHandle.Set("b", b);
		luaHandle.Set("c", c);
		luaHandle.Set("d", d);
		luaHandle.Set("e", e);

		luaHandle.ExecString("print(a, b, c, d, e)");

		bin::CScriptTable tbl;
		luaHandle.NewTable("tbl", tbl);
		tbl.Set("a", a);
		tbl.Set("b", b);
		tbl.Set("c", c);
		tbl.Set("d", d);
		tbl.Set("e", e);
		
		luaHandle.ExecString("print('table value : ', tbl.a, tbl.b, tbl.c, tbl.d, tbl.e)");

		bin::ScriptExporterManager().ExportClass("HandleTestClass", luaHandle);
		CTestClass obj;
		luaHandle.Set("obj", &obj);

		luaHandle.ExecString("print('object : ', obj:name()) obj.v = 'lua string'");

		bin::CScriptUserData ud;
		obj.GetScriptUserData(ud);

		ud.Set("v0", "c++ string");

		luaHandle.Set("obj2", ud);

		luaHandle.ExecString("print('object2 : ', obj2.v, obj2.v0)");
	}

	// call function
	// 
	{
		luaHandle.ExecString("function hello() print('luaFunction : ', 'Hello World') end");
		luaHandle.CallFunc("hello", RET_VOID);

		luaHandle.ExecString("function hello(a, b) print('luaFunction(a, b): ', a, b) end");
		luaHandle.CallFunc<const char*, int>("hello", "Hello", 100, RET_VOID);

		luaHandle.ExecString("function hello(a, b) print('luaFunction(a, b) ret : ', a, b) return 'World' end");
		std::string ret;
		luaHandle.CallFunc<const char*, int>("hello", "Hello", 100, ret);
		printf("Lua Return : %s\n", ret.c_str());
	}

	// release
	{
		luaHandle.Release();
	}
}

REGISTE_EXAMPLE(CExample_Handle);