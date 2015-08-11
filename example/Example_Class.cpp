#include "Example_Class.h"

#include "ExampleManager.h"

#include "Public.hpp"

class CClass
{
	DECLARE_SCRIPT_CLASS();
public:
	void Hello()
	{

	}

	void Say(const std::string& msg)
	{
		printf(msg.c_str());
	}

	std::string Want()
	{
		return "World";
	}
};

namespace bin
{
	BEGIN_SCRIPT_CLASS(TestClass, CClass)
		DEFINE_CLASS_FUNCTION(hello, void, ())
		{
			obj->Hello();
			return 1;
		}

		DEFINE_CLASS_FUNCTION(say, void, (const std::string& message))
		{
			obj->Say(message);
			return 1;
		}

		DEFINE_CLASS_FUNCTION(want , std::string, ())
		{
			r = obj->Want();
			return 1;
		}

		DEFINE_STATIC_FUNCTION(newInstance, CClass*, ())
		{
			r = new CClass;
			r->GetScriptObject().SetDelByScr(true);

			return 1;
		}
	END_SCRIPT_CLASS()
}

void CExample_Class::Do()
{
	// Init a lua handle
	bin::CScriptHandle luaHandle;
	luaHandle.Init();

	// Export test module definition to luaHandle
	bin::ScriptExporterManager().ExportClass("TestClass", luaHandle);

	// call test.hello();
	luaHandle.ExecString("local obj = bin_types.TestClass.newInstance(); obj:hello(); obj:say('Hello BIN_LuaBind'); print(' Obj wants '..obj:want())");
}

REGISTE_EXAMPLE(CExample_Class);