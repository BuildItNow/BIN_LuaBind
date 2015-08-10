#pragma once

#include "Example.h"

#include <map>
#include <string>

class CExampleManager
{
public:
	CExampleManager();
	~CExampleManager();

	void AddExample(CExample* pExample);
	void DoExample(const std::string& name);

private:
	typedef std::map<std::string, CExample*> Examples;

	Examples m_examples;

private:
	static CExampleManager* s_pInstance;
public:
	static CExampleManager* PInstance();
	static CExampleManager& Instance();
};

template <typename T>
class CExampleRegister
{
public:
	CExampleRegister()
	{
		T* pExample = new T();

		CExampleManager::Instance().AddExample(pExample);
	}
};

#define REGISTE_EXAMPLE(T)\
	namespace \
	{\
		static CExampleRegister<T>	__registExample;\
	};

