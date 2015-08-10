#pragma once

#include "Example.h"

class CExample_Inheritance : public CExample
{
public:
	virtual std::string GetName() const
	{
		return "inheritance";
	}

	virtual void Do();
};