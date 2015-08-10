#pragma once

#include "Example.h"

class CExample_Extend : public CExample
{
public:
	virtual std::string GetName() const
	{
		return "extend";
	}

	virtual void Do();
};