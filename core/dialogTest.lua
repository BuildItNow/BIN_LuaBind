
local creator = gui.requireCreator("type0")

print(creator)

local newDialog = creator("type0dialog.xml")

print(newDialog, "id = "..newDialog:getID())

creator = gui.requireCreator("type1")

print(creator)

local newDialog = creator("teyp1dialog.xml")

print(newDialog, "id = "..newDialog:getID())

newDialog = creator("teyp1dialog.xml")

print(newDialog, "id = "..newDialog:getID())
