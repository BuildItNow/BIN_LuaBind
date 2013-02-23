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
#include "ScriptProxy.h"

//
#include "ScriptBase.h"
#include "ScriptExporter.h"

//

namespace bin
{

    void SScriptObjectRef::Unlink()
    {
        if(pObject)
        {
            pObject->SideUnlink();
        }

        SideUnlink();
    }

	void SScriptObjectRef::SideUnlink()
	{
		// Remove the object from objects table
		if(pLua && nRef!=LUA_NOREF)
		{
			CHECK_LUA_STACK(pLua);

			ScriptExporterManager().CheckObjectsTable(pLua);
			luaL_unref(pLua, -1, nRef);
		}

		pObject = NULL;
		pLua    = NULL;
		nRef    = LUA_NOREF;
	}

	// Push userdata on top in pL's stack, nil if not exported
	int SScriptObject::GetUserData(lua_State* pL) 
	{
		if(!IsExported() || m_pObjRef->pLua != pL)
		{
			lua_pushnil(pL);

			return 1;
		}

		ScriptExporterManager().CheckObjectsTable(pL);
		lua_rawgeti(pL, -1, m_pObjRef->nRef);
		lua_replace(pL, -2);
		return 1;
	}

	int SScriptObject::GetUserData(CScriptUserData& scriptUserData)
	{
		scriptUserData.UnRef();

		if(m_scriptHandle.IsNull())
		{
			return 0;
		}

		lua_State* pLua = m_pObjRef->pLua;
		CHECK_LUA_STACK(pLua);

		ScriptExporterManager().CheckObjectsTable(pLua);
		lua_rawgeti(pLua, -1, m_pObjRef->nRef);

		const char* TEMP_REF = "__bin_temp";
		lua_setglobal(pLua, TEMP_REF);

		m_scriptHandle.Get(TEMP_REF, scriptUserData);
		lua_pushnil(pLua);
		lua_setglobal(pLua, TEMP_REF);
		
		return 1;
	}

	int  SScriptObject::InitScript()
	{
		ReleaseScript();

		lua_State* pLua = m_pObjRef->pLua;
		if(!m_scriptHandle.Init(pLua))
		{
			return 0;
		}

		return 1;
	}

	void SScriptObject::ReleaseScript()
	{
		m_scriptHandle.Release();
	}
};