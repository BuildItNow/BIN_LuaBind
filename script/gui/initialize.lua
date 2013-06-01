
exporterManager.exportModule("gui")
exporterManager.exportClass("guiDialog", "gui")

local dir = "./script/gui/"

local type2creator = 
{
	type0 = "type0Creator.lua",
	type1 = "type0Creator.lua"
}

function gui.loadCreator(creatorFile)
	dofile(creatorFile)
end

function gui.requireCreator (dialogType)
	local creator = gui[dialogType]
	if creator then
		return creator
	end

	local creatorFile = type2creator[dialogType]
	
	if creatorFile ~= nil then
		gui.loadCreator(dir..creatorFile)
	end
	
	creator = gui[dialogType]
	
	return creator
end

local guiTbl = {}
assert(exporterManager.exportModule("gui", guiTbl))
assert(guiTbl.moduleToTable)
guiTbl.moduleToTable()

local retTbl = guiTbl.returnTable()
assert(retTbl and retTbl.msg == "returnTable")

logger.info("Gui done")
