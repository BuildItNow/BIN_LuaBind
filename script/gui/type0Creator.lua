print("begin gui/type0Creator")

print("type0Creator")

local guiDialog = bin_types.gui.guiDialog

-- now define the dialog
local type0Dialog = {}

function type0Dialog:onCreate()
	guiDialog.onCreate(self)
	print("type0Dialog::onCreate", self:getID())
	return true
end

-- define the creator
function gui.type0(ui)
	local newDialog = gui.newDialog()
	if newDialog == nil or not newDialog:imported() then
		return nil
	end
	
	local dialogDef = type0Dialog
	
	do
		newDialog.onCreate = dialogDef.onCreate
	end
		
	if gui.loadDialog(newDialog, ui) ~= 1 then
		newDialog = nil
	end
	
	return newDialog
end

print("type1Creator")

-- Inheriget from type0
local type1Dialog = {}

function type1Dialog:onCreate()
	local super = type0Dialog
	if not super.onCreate(self) then
		print("type0Dialog::onCreate false", self:getID())
		return false
	end
	
	print("type1Dialog::onCreate", self:getID())
	
	return true
end

function gui.type1(ui)
	local newDialog = gui.newDialog()
	if newDialog == nil or not newDialog:imported() then
		return nil
	end
	
	local dialogDef = type1Dialog
	do
		newDialog.onCreate = dialogDef.onCreate
	end
	
	if gui.loadDialog(newDialog, ui) ~= 1 then
		newDialog = nil
	end
	
	return newDialog
end

print("end gui/type0Creator")
