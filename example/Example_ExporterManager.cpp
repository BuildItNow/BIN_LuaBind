#include "Example_ExporterManager.h"

#include "ExampleManager.h"

#include "Public.hpp"

class CClassAA
{
	DECLARE_SCRIPT_CLASS();
};

class CClassBB
{
	DECLARE_SCRIPT_CLASS();
};

namespace bin
{
	BEGIN_SCRIPT_MODULE(moduleA)
		DEFINE_MODULE_FUNCTION(hello, void, ())
		{
			printf("moduleA function\n");

			return 1;
		}
	END_SCRIPT_MODULE()

	BEGIN_SCRIPT_CLASS(ClassAA, CClassAA)
	END_SCRIPT_CLASS()

	BEGIN_SCRIPT_CLASS(ClassBB, CClassBB)
	END_SCRIPT_CLASS()
}

void CExample_ExporterManager::Do()
{
	bin::CScriptHandle luaHandle;
	luaHandle.Init();

	// Export module 
	bin::ScriptExporterManager().ExportModule("moduleA", luaHandle);
	luaHandle.ExecString("moduleA.hello()");

	// Export module to another module
	bin::ScriptExporterManager().ExportModuleTo("moduleA", luaHandle, "moduleB");
	luaHandle.ExecString("moduleB.hello()");

	// Export module to a existed module
	luaHandle.ExecString("moduleC = {a=10}");

	bin::ScriptExporterManager().ExportModuleTo("moduleA", luaHandle, "moduleC");
	luaHandle.ExecString("print(moduleC.a) moduleC.hello()");

	// Export module to a table
	bin::CScriptTable tbl;
	bin::ScriptExporterManager().ExportModuleTo("moduleA", luaHandle, tbl);
	tbl.CallFunc("hello", RET_VOID);

	luaHandle.Set("moduleD", tbl);
	luaHandle.ExecString("moduleD.hello()");

	// Export class
	bin::ScriptExporterManager().ExportClass("ClassAA", luaHandle);
	
	// Export class to a namespace
	bin::ScriptExporterManager().ExportClass("ClassAA", luaHandle, "namespace");
	luaHandle.ExecString("print(bin_types.ClassAA, bin_types.namespace.ClassAA)");

	luaHandle.Release();
	luaHandle.Init();

	// Use lua interface
	luaHandle.ExecString("exporterManager.exportModule('moduleA') moduleA.hello()");
	luaHandle.ExecString("moduleB = {} exporterManager.exportModule('moduleA', moduleB) moduleB.hello()");

	luaHandle.ExecString("exporterManager.exportClass('ClassAA') print(bin_types.ClassAA)");
	luaHandle.ExecString("exporterManager.exportClass('ClassAA', 'namespace') print(bin_types.namespace.ClassAA)");
}

REGISTE_EXAMPLE(CExample_ExporterManager);