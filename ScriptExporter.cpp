/*
Original code by Yang G (pinner@mail.ustc.edu.cn)

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any
damages arising from the use of this software.

Permission is granted to anyone to use this software for any
purpose, including commercial applications, and to alter it and
redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must
not claim that you wrote the original software. If you use this
software in a product, an acknowledgment in the product documentation
would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and
must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/
//
#include "Public.h"

//
#include "ScriptExporter.h"

//
#include "ScriptBase.h"

//

namespace bin
{
	int CScriptExporterManager::ExportClass(const char* pszName, lua_State* pL, const char* pszNameSpace /*= NULL*/)
	{
		ExporterIterator pos = m_scriptExporters.find(pszName);

		if(pos != m_scriptExporters.end())
		{
			SExporterInfo info = pos->second->GetInfo();
			if(info.eET != SExporterInfo::EET_CLASS)
			{
				return 0;
			}

			CClassExporter* pClsExp = (CClassExporter*)(pos->second);
			return pClsExp->Export(pL, pszNameSpace);
		}

		return 0;
	}

	int CScriptExporterManager::ExportModule(const char* pszName, lua_State* pL)
	{
		ExporterIterator pos = m_scriptExporters.find(pszName);

		if(pos != m_scriptExporters.end())
		{
			SExporterInfo info = pos->second->GetInfo();
			if(info.eET != SExporterInfo::EET_MODULE)
			{
				return 0;
			}

			return pos->second->Export(pL);
		}

		return 0;
	}

	BEGIN_SCRIPT_MODULE(exporterManager)
		DEFINE_MODULE_FUNCTION(exportClass, bool, (const char* pszName))
		{
			r = ScriptExporterManager().ExportClass(pszName, lua) != 0;

			return 1;
		}

		DEFINE_MODULE_FUNCTION(exportClassTo, bool, (const char* pszName, const char* pszNameSpace))
		{
			r = ScriptExporterManager().ExportClass(pszName, lua, pszNameSpace) != 0;

			return 1;
		}

		DEFINE_MODULE_FUNCTION(exportModule, bool, (const char* pszName))
		{
			r = ScriptExporterManager().ExportModule(pszName, lua) != 0;

			return 1;
		}

	END_SCRIPT_MODULE()
};
