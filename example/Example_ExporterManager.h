#pragma once

#include "Example.h"

class CExample_ExporterManager : public CExample
{
public:
	virtual std::string GetName() const
	{
		return "exporterManager";
	}

	virtual void Do();
};