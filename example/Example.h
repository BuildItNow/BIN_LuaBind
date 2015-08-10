#pragma once

#include <string>

class CExample
{
public:
	CExample()
	{

	}

	virtual ~CExample()
	{
	}

	virtual std::string GetName() const
	{
		return "unknow";
	}

	virtual void Do() = 0;
};