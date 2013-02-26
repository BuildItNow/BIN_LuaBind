exporterManager.exportModule("logger")

dofile("./script/log/initialize.lua")
dofile("./script/gui/initialize.lua")

logger.info("Script done")

logger.debug("Debug Message %s", "Debug")

logger.info("Info Message %d", 100)

logger.warning("Warning Message")

logger.error("Error Message")

logger.critical("Critical Message")

logger.fatal("Fatal Message")

dofile("./script/core/dialogTest.lua")
