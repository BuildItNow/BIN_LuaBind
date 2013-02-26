
exporterManager.exportModule("gui")
exporterManager.exportClassTo("guiDialog", "gui")

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

logger.info("Gui done")
