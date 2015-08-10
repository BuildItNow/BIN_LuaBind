#pragma once

#include "Example.h"

class CExample_Table : public CExample
{
public:
	virtual std::string GetName() const
	{
		return "table";
	}

	virtual void Do();
};