#include "Lock.h"
#include <Windows.h>

namespace ZGF
{
	struct CriticalSectionData
	{
		CRITICAL_SECTION criticalSection;
	};

	CriticalSection::CriticalSection()
	{
		m_sectionData = new CriticalSectionData();
		InitializeCriticalSection(&m_sectionData->criticalSection);
	}

	CriticalSection::~CriticalSection()
	{
		DeleteCriticalSection(&m_sectionData->criticalSection);
		delete m_sectionData;	
	}

	void CriticalSection::TryEnter()
	{
		TryEnterCriticalSection(&m_sectionData->criticalSection);
	}

	void CriticalSection::Enter()
	{
		EnterCriticalSection(&m_sectionData->criticalSection);
	}

	void CriticalSection::Leave()
	{
		LeaveCriticalSection(&m_sectionData->criticalSection);
	}
}