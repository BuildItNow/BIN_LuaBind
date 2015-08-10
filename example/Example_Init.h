#pragma once

#include "Example.h"

class CExample_Init : public CExample
{
public:
	virtual std::string GetName() const
	{
		return "init";
	}

	virtual void Do();
};