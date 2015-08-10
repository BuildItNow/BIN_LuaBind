#pragma once

#include "Example.h"

class CExample_Module : public CExample
{
public:
	virtual std::string GetName() const
	{
		return "module";
	}

	virtual void Do();
};