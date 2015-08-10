#include "ExampleManager.h"



#include <cassert>

CExampleManager* CExampleManager::s_pInstance = NULL;

CExampleManager::CExampleManager()
{

}

CExampleManager::~CExampleManager()
{

}

void CExampleManager::AddExample(CExample* pExample)
{
	std::pair<Examples::const_iterator, bool> ret = m_examples.insert(Examples::value_type(pExample->GetName(), pExample));
	if(!ret.second)
	{
		printf("Example[%s] conflict \n", pExample->GetName().c_str());
		assert(false && "Example name conflict");
	}
} 

void CExampleManager::DoExample(const std::string& name)
{
	Examples::const_iterator pos = m_examples.find(name);
	if(pos == m_examples.end())
	{
		printf("Example[%s] not exists \n", name.c_str());
		return ;
	}

	pos->second->Do();
}

CExampleManager* CExampleManager::PInstance()
{
	if(!s_pInstance)
	{
		s_pInstance = new CExampleManager();
	}

	return s_pInstance;
}

CExampleManager& CExampleManager::Instance()
{
	return *PInstance();
}
