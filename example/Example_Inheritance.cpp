#include "Example_Inheritance.h"

#include "ExampleManager.h"

#include "Public.hpp"

class CClassA
{
	DECLARE_SCRIPT_CLASS();
public:
	virtual void Say()
	{
		printf("I'm A\n");
	}

	void Func()
	{
		printf("A's Func\n");
	}
};

class CClassB : public CClassA
{
	DECLARE_SCRIPT_SUB_CLASS(CClassA);
public:
	virtual void Say()
	{
		printf("I'm B\n");
	}
};

namespace bin
{
	BEGIN_SCRIPT_CLASS(ClassA, CClassA)
		DEFINE_CLASS_FUNCTION(say, void, ())
		{
			obj->Say();
			return 1;
		}

		DEFINE_CLASS_FUNCTION(func, void, ())
		{
			obj->Func();
			return 1;
		}

		DEFINE_STATIC_FUNCTION(newInstance, CClassA*, ())
		{
			r = new CClassA;
			r->GetScriptObject().SetDelByScr(true);

			return 1;
		}
	END_SCRIPT_CLASS()

	BEGIN_SCRIPT_CLASS(ClassB, CClassB)
		SUPER_CLASS(ClassA, CClassA)
		DEFINE_STATIC_FUNCTION(newInstance, CClassB*, ())
		{
			r = new CClassB;
			r->GetScriptObject().SetDelByScr(true);

			return 1;
		}
	END_SCRIPT_CLASS()
}

void CExample_Inheritance::Do()
{
	// Init a lua handle
	bin::CScriptHandle luaHandle;
	luaHandle.Init();

	// Export test module definition to luaHandle
	bin::ScriptExporterManager().ExportClass("ClassA", luaHandle);
	bin::ScriptExporterManager().ExportClass("ClassB", luaHandle);

	// call test.hello();
	luaHandle.ExecString("local objA = bin_types.ClassA.newInstance(); objA:say(); local objB = bin_types.ClassB.newInstance(); objB:say(); objB:func()");
}

REGISTE_EXAMPLE(CExample_Inheritance);