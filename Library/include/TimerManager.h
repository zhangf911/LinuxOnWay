#ifndef LIBRARY_THREAD_TIMERMANAGER_H
#define LIBRARY_THREAD_TIMERMANAGER_H

#include <deque>
using std::deque;

#include "BaseType.h"
#include "Timer.h"

namespace ZGF
{
	class TimerManager
	{
	public:
		typedef deque<Timer*> TimerDeque;
		TimerDeque::iterator TimerDequeIter;
	private:
		/** ��ʱ������ **/
		TimerDeque m_timerDeque;

	public:
		/**
		* @brief ��ʼ����ʱ��
		* @return true : �ɹ� false : ʧ��
		* @exception
		* @note
		**/
		bool Initial();

		/**
		* @brief ������ʱ��
		**/
		void CreatTimer(TimerCallBack* INpCallBack, UInt32 INtimerType = Timer::ETimerType_limitedCycle, UInt32 INintervalTime = 0, UInt32 INcycleCount = 0);

		/**
		* @brief ���ж�ʱ��
		**/
		void RunTimer();
	};

}

#endif