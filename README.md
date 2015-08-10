# BIN_LuaBind

BIN_LuaBind是一个和luabind、tolua++类似的库，提供了简洁的C/C++到lua的绑定机制，但与之不同的是BIN_LuaBind比他们更安全：lua层不在直接依赖于C/C++层指针，避免野指针引起宕机。除此之外，BIN_LuaBind对Lua提供了对lua_state,user data和table的抽象类，在C++端能方便的操作lua