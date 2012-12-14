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
		/** 定时器队列 **/
		TimerDeque m_timerDeque;

	public:
		/**
		* @brief 初始化定时器
		* @return true : 成功 false : 失败
		* @exception
		* @note
		**/
		bool Initial();

		/**
		* @brief 创建定时器
		**/
		void CreatTimer(TimerCallBack* INpCallBack, UInt32 INtimerType = Timer::ETimerType_limitedCycle, UInt32 INintervalTime = 0, UInt32 INcycleCount = 0);

		/**
		* @brief 运行定时器
		**/
		void RunTimer();
	};

}

#endif