/*
 * Lock.cpp
 *
 *  Created on: 2012-12-17
 *      Author: king
 */

#include "Lock.h"
#ifdef WIN32
#include <Windows.h>
#else
#ifdef __GNUC__

#endif
#endif

namespace LOW
{
	struct CriticalSectionData
	{
#ifdef WIN32
		CRITICAL_SECTION criticalSection;
#else
#ifdef __GNUC__

#endif
#endif
	};

	CriticalSection::CriticalSection()
	{
		m_sectionData = new CriticalSectionData();
#ifdef WIN32
		InitializeCriticalSection(&m_sectionData->criticalSection);
#else
#ifdef __GNUC__

#endif
#endif
	}

	CriticalSection::~CriticalSection()
	{
#ifdef WIN32
		DeleteCriticalSection(&m_sectionData->criticalSection);
#else
#ifdef __GNUC__

#endif
#endif
		delete m_sectionData;
	}

	void CriticalSection::TryEnter()
	{
#ifdef WIN32
		TryEnterCriticalSection(&m_sectionData->criticalSection);
#else
#ifdef __GNUC__

#endif
#endif
	}

	void CriticalSection::Enter()
	{
#ifdef WIN32
		EnterCriticalSection(&m_sectionData->criticalSection);
#else

#ifdef __GNUC__

#endif
#endif
	}

	void CriticalSection::Leave()
	{
#ifdef WIN32
		LeaveCriticalSection(&m_sectionData->criticalSection);
#else
#ifdef __GNUC__

#endif
#endif
	}
}


