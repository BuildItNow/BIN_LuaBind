#include "Example_ExporterManager.h"

#include "ExampleManager.h"

#include "Public.hpp"

namespace bin
{
}

void CExample_ExporterManager::Do()
{
	// Init a lua handle
	bin::CScriptHandle luaHandle;
	luaHandle.Init();

	bin::ScriptExporterManager().ExportModule("test", luaHandle);

	luaHandle.ExecString("print(test.hello())");
}

REGISTE_EXAMPLE(CExample_ExporterManager);