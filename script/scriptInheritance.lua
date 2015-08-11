--[[
BEGIN_SCRIPT_CLASS(super, CSuper)
		DEFINE_CLASS_FUNCTION(getMsg, std::string, ())
		{
			if(!obj)
			{
				return 0;
			}

			r = obj->m_strSupMsg;
			std::cout<< "super::getMsg\n";

			return 1;
		}

		DEFINE_CLASS_FUNCTION(superFunc, int, ())
		{
			if(!obj)
			{
				return 0;
			}

			std::cout<< "super::superFunc\n";

			return 1;
		}
	END_SCRIPT_CLASS()

	BEGIN_SCRIPT_CLASS(sub, CSub)
		SUPER_CLASS(super, CSuper)
		DEFINE_CLASS_FUNCTION(getMsg, std::string, ())
		{
			if(!obj)
			{
				return 0;
			}

			r = obj->m_strSubMsg;
			std::cout<< "sub::getMsg\n";

			return 1;
		}
		
		DEFINE_CLASS_FUNCTION(subFunc, int, ())
		{
			if(!obj)
			{
				return 0;
			}

			std::cout<< "sub::subFunc\n";

			return 1;
		}
	END_SCRIPT_CLASS()

	BEGIN_SCRIPT_CLASS(subsub, CSubSub)
		SUPER_CLASS(sub, CSub)
		DEFINE_CLASS_FUNCTION(getMsg, std::string, ())
		{
			if(!obj)
			{
				return 0;
			}

			r = obj->m_strSubSubMsg;
			std::cout<< "subsub::getMsg\n";

			return 1;
		}

		DEFINE_CLASS_FUNCTION(subsubFunc, int, ())
		{
			if(!obj)
			{
				return 0;
			}

			r = 0;
			std::cout<< "subsub::subsubFunc\n";

			return 1;
		}
	END_SCRIPT_CLASS()
	
	ASSERT0(ScriptExporterManager().ExportClass("super", scriptHandle));
	ASSERT0(ScriptExporterManager().ExportClass("sub", scriptHandle));
	ASSERT0(ScriptExporterManager().ExportClass("subsub", scriptHandle));
]]

local type_super = bin_types.super
local type_sub   = bin_types.sub
local type_subsub = bin_types.subsub

local function newType(name, super)
	local type_new = {}
	type_new.__index = type_new		-- support inherited by others
	type_new.super = super			-- support inherited by others
	
	type_new.type = "class"
	type_new.name = name
	
	setmetatable(type_new, super)
	
	return type_new
end


local type_scriptSub = newType("type_scriptSub", type_super)

function type_scriptSub:getScriptMessage()
	return "type_scriptSub"
end

function type_scriptSub:getScriptSubMessage()
	return "type_scriptSub"
end

local type_scriptSubSub = newType("type_scriptSub", type_scriptSub)

function type_scriptSubSub:getScriptMessage()
	return "type_scriptSubSub"
end

function core.newScriptSub()
	local obj = core.newSuper()
	if obj then
		setmetatable(obj.__bin_objtable, type_scriptSub)
	end
		
	return obj
end

function core.newScriptSubSub()
	local obj = core.newScriptSub()
	if obj then
		setmetatable(obj.__bin_objtable, type_scriptSubSub)
	end
	
	return obj
end

local type_scriptSubSub_subsub = newType("type_scriptSubSub_subs", type_subsub)

function type_scriptSubSub_subsub:getMsg()
	return "type_scriptSubSub_subsub"
end

function core.newScriptSubSub_subsub()
	local obj = core.newSubSub()
	if obj then
		setmetatable(obj.__bin_objtable, type_scriptSubSub_subsub)
	end
	
	return obj
end


