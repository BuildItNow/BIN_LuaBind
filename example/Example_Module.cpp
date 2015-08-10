#include "Example_Module.h"

#include "ExampleManager.h"

#include "Public.hpp"

namespace bin
{
	// Define a lua module
	BEGIN_SCRIPT_MODULE(testModule)
		// Define a function :
		//	ret  : void
		//  arts : void
		DEFINE_MODULE_FUNCTION(func0, void, (void))
		{
			printf("Calling func0\n");
			return 1;
		}
		
		//	ret  : std::string
		//  arts : void
		DEFINE_MODULE_FUNCTION(func1, std::string, (void))
		{
			printf("Calling func1 and return 'stringAsReturn'\n");
			r = "stringAsReturn";

			return 1;
		}

		//	ret  : int
		//  arts : void
		DEFINE_MODULE_FUNCTION(func2, int, (void))
		{
			printf("Calling func2 and return 'intAsReturn'\n");
			r = 100;

			return 1;
		}

		//	ret  : int
		//  arts : int
		DEFINE_MODULE_FUNCTION(func3, void, (int a0))
		{
			printf("Calling func3 with ( %d )\n", a0);
			
			return 1;
		}

		//	ret  : int
		//  arts : double, const char*
		DEFINE_MODULE_FUNCTION(func4, void, (double a0, const char* a1))
		{
			printf("Calling func4 with (%f, %s)\n", a0, a1);
			
			return 1;
		}

		//	ret  : int
		//  arts : string, long long
		DEFINE_MODULE_FUNCTION(func5, void, (std::string a0, long long a1))
		{
			printf("Calling func5 with (%s, %lld)\n", a0.c_str(), a1);
			
			return 1;
		}

	END_SCRIPT_MODULE()
}

void CExample_Module::Do()
{
	// Init a lua handle
	bin::CScriptHandle luaHandle;
	luaHandle.Init();

	// Export test module definition to luaHandle
	bin::ScriptExporterManager().ExportModule("testModule", luaHandle);

	// Call module functions
	luaHandle.ExecString("testModule.func0()");
	luaHandle.ExecString("print(testModule.func1())"); 
	luaHandle.ExecString("print(testModule.func2())");
	luaHandle.ExecString("testModule.func3(10)");
	luaHandle.ExecString("testModule.func4(2.01, 'Hello BIN_LuaBind')");
	luaHandle.ExecString("testModule.func5('Hello BIN_LuaBind', 1000000000000)");
}

REGISTE_EXAMPLE(CExample_Module);