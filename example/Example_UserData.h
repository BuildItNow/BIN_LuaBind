#pragma once

#include "Example.h"

class CExample_UserData : public CExample
{
public:
	virtual std::string GetName() const
	{
		return "userData";
	}

	virtual void Do();
};