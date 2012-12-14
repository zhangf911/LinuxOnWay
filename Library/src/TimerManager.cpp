#include "TimerManager.h"
#include "Thread.h"

#include "Log.h"

namespace ZGF
{
	bool TimerManager::Initial()
	{
		try
		{
			
		}
		catch(...)
		{
			return false;
		}
		return true;
	}

	void TimerManager::CreatTimer(TimerCallBack* INpCallBack, UInt32 INtimerType /* = Timer::ETimerType_limitedCycle */, UInt32 INintervalTime /* = 0 */, UInt32 INcycleCount /* = 0 */)
	{
		Timer* pTimer = new Timer(INpCallBack, INtimerType, INintervalTime, INcycleCount);

		//m_timerDeque.insert(pTimer,);
	}

	void TimerManager::RunTimer()
	{

	}
}