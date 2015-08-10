#include "ExampleManager.h"

#include <iostream>
#include <string>

// Examples
//		init
//			defination in C++
//			export defination to Lua
//		module
//			module function
//		class
//			memeber function
//		exporterManager
//			export to handle
//			export to table
//		inheritance
//		handle
//			get
//			set
//			call function
//		table
//			get
//			set
//			call function
//		userData
//			get
//			set
//			call function
//			call member function
//		extend
//			get custom type from lua
//			set custom type to lua
//		other
//			check object life in C++/Lua


int main(int argc, const char** argv)
{
	using namespace std;

	cout << "Welcome to BIN_LuaBind";
	
	string command;
	while(true)
	{
		cout << "\nPlease input example name(or 'exit') : ";
		cin  >> command;

		if(command == "exit")
		{
			break;
		}

		CExampleManager::Instance().DoExample(command);
	}

	cout << "Bye!" << endl;
	return 0;
}