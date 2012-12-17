/*
 * Lock.h
 *
 *  Created on: 2012-12-17
 *      Author: king
 */

#ifndef LOCK_H_
#define LOCK_H_

#include "Common.h"

namespace LOW
{
	struct CriticalSectionData;

	class CriticalSection
	{
	private:
		CriticalSectionData* m_sectionData;
	public:
		CriticalSection();

		~CriticalSection();

		void TryEnter();

		void Enter();

		void Leave();
	};

	template <class Lock>
	class Guard
	{
		Lock* m_lock;
	public:
		Guard(Lock* INlock)
			: m_lock(INlock)
		{
			m_lock->Enter();
		}

		~Guard()
		{
			m_lock->Leave();
		}
	};
}

#endif /* LOCK_H_ */
