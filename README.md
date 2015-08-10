# BIN_LuaBind

BIN_LuaBind是一个和luabind、tolua++类似的库，提供了简洁的C/C++到lua的绑定机制，但与之不同的是BIN_LuaBind比他们更安全: lua层不在直接依赖于C/C++层指针，避免野指针引起宕机。除此之外，BIN_LuaBind对Lua提供了对lua_state,user data和table的抽象类，在C++端能方便的操作lua

## 功能
* C/C++ to Lua Bind机制 
* 模块Bind
* 类Bind
* C++继承类Bind
* lua handle封装
* table封装
* userdata封装
* Bind机制支持自定义类型

## 集成
1: 下载源码 <br/>
2: 直接使用bin目录下头文件和库文件,lib目录下包含lua的头文件和库文件 <br/>
3: 或者直接使用自带的VS工程，生成lib文件 <br/>

## 目录结构
* src : BIN_LuaBind源码 
* lib : BIN_LuaBind依赖库
* bin : BIN_LuaBind头文件和库文件
* test : 功能测试源码
* example : 例子源码
* script : 功能测试使用的脚本文件

# 文档

## Bind机制
使用BIN_LuaBind，需要先在C/C++层建立需要导出到脚本的模块或者类定义(注意：不是C++类定义，而是使用)，这个过程通过提供的BEGIN_SCRIPT_MODULE,BEGIN_SCRIPT_CLASS进行定义。然后通过Exporter Manager将需要的模块和类导出到Script Handle或者Script Table里面，这个过程通过ScriptExporterManager().Export和ScriptExporterManager().ExportTo完成。<br/>
采用这种方式，在C/C++层包含了整个定义的结构，可根据需要将不同的模块和类导出到不同的Script Handle和Script Table，避免总是将所有的定义都导出到Lua层。

## Module定义
BEGIN_SCRIPT_MODULE : 开始定义一个Module <br/>
END_SCRIPT_MODULE : 结束定义一个Module <br/>
DEFINE_MODULE_FUNCTION : 定义一个Module Function <br/>
```C++
BEGIN_SCRIPT_MODULE(moduleName)
	DEFINE_MODULE_FUNCTION(moduleFunction,  returnType, (argumentList))
	{
		return 1;
	}
END_SCRIPT_MODULE()
```

## Class定义
DECLARE_SCRIPT_CLASS : 声明一个C++ Class为Script Class <br/>
BEGIN_SCRIPT_CLASS : 开始定义一个Script Class <br/>
END_SCRIPT_CLASS : 结束定义一个Script Class <br/>
DEFINE_CLASS_FUNCTION : 定义一个Class Member Function <br/>
```C++
class CClass
	{
		DECLARE_SCRIPT_CLASS()
	public:
		CClass()
		{
		}

		~CClass()
		{
		}

		void Func()
		{
		}
	};

	BEGIN_SCRIPT_CLASS(className, CClass)
		DEFINE_CLASS_FUNCTION(functionName, returnType, (argumentList))
		{
			return 1;
		}
		DEFINE_CLASS_FUNCTION(func, void, ())
		{	
			if(!obj)
			{
				return 0;
			}

			obj->Func();
			
			return 1;
		}
	END_SCRIPT_CLASS()
```

## Class继承定义

## C++对象销毁处理

## Lua对象回收处理




 