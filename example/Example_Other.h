#pragma once

#include "Example.h"

class CExample_Other : public CExample
{
public:
	virtual std::string GetName() const
	{
		return "other";
	}

	virtual void Do();
};