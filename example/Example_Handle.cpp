#include "Example_Handle.h"

#include "ExampleManager.h"

#include "Public.hpp"

namespace bin
{
}

void CExample_Handle::Do()
{
	// Init a lua handle
	bin::CScriptHandle luaHandle;
	luaHandle.Init();

	// Export test module definition to luaHandle
	bin::ScriptExporterManager().ExportModule("test", luaHandle);

	// call test.hello();
	luaHandle.ExecString("print(test.hello())");
}

REGISTE_EXAMPLE(CExample_Handle);