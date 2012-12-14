#ifndef LIBRARY_THREAD_LOCK_H
#define LIBRARY_THREAD_LOCK_H


namespace ZGF
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

#endif