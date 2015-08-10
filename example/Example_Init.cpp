#include "Example_Init.h"

#include "ExampleManager.h"

#include "Public.hpp"

namespace bin
{
	// Define a lua module
	BEGIN_SCRIPT_MODULE(test)
		// Define a function for module
		DEFINE_MODULE_FUNCTION(hello, std::string, (void))
		{
			// Return a string to lua
			r = "Hello BIN_LuaBind";								
			return 1;
		}
	END_SCRIPT_MODULE()
}

void CExample_Init::Do()
{
	// Init a lua handle
	bin::CScriptHandle luaHandle;
	luaHandle.Init();

	// Export test module definition to luaHandle
	bin::ScriptExporterManager().ExportModule("test", luaHandle);

	// call test.hello();
	luaHandle.ExecString("print(test.hello())");
}

REGISTE_EXAMPLE(CExample_Init);