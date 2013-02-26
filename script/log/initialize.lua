local logger = _G.logger
local NOLOG 	= 0
local DEBUG 	= 10
local INFO 		= 20
local WARNING 	= 30
local ERROR 	= 40
local CRITICAL 	= 50
local FATAL 	= 60

local logLevel  = NOLOG

local logPrex = {}
logPrex[NOLOG] 		= "[nolg]"
logPrex[DEBUG] 		= "[dbug]"
logPrex[INFO] 		= "[info]"
logPrex[WARNING] 	= "[warn]"
logPrex[ERROR] 		= "[erro]"
logPrex[CRITICAL] 	= "[crit]"
logPrex[FATAL] 		= "[fata]"

local format = string.format

local function logImpl(level, fmt, ...)
	if level < logLevel then
		return 
	end
	
	local msg = format(fmt, ...)
	
	logger.__bin_log(os.date("%Y/%m/%d %H:%M:%S")..logPrex[level]..msg)
end

function logger.debug(fmt, ...)
	logImpl(DEBUG, fmt, ...)
end

function logger.info(fmt, ...)
	logImpl(INFO, fmt, ...)
end

function logger.warning(fmt, ...)
	logImpl(WARNING, fmt, ...)
end

function logger.error(fmt, ...)
	logImpl(ERROR, fmt, ...)
end

function logger.critical(fmt, ...)
	logImpl(CRITICAL, fmt, ...)
end

function logger.fatal(fmt, ...)
	logImpl(FATAL, fmt, ...)
end

logger.info("Logger done")




