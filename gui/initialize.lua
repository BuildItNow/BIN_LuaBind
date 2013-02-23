local type2creator = 
{
	type0 = "gui/type0Creator.lua",
	type1 = "gui/type0Creator.lua"
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
		gui.loadCreator(creatorFile)
	end
	
	creator = gui[dialogType]
	
	return creator
end

print("end gui/initialize")
