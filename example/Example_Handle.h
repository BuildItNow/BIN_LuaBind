#pragma once

#include "Example.h"

class CExample_Handle : public CExample
{
public:
	virtual std::string GetName() const
	{
		return "handle";
	}

	virtual void Do();
};