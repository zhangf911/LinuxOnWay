#ifndef LIBRARY_THREAD_TIMER_H
#define LIBRARY_THREAD_TIMER_H

#include "BaseType.h"

namespace ZGF
{
	class Timer;

	class TimerCallBack
	{
	public:
		virtual void OnTimer(Timer* INtimer);
	};

	class Timer
	{
	public:
		enum TimerType
		{
			/// 有限循环
			ETimerType_limitedCycle,
			/// 无限循环
			ETimerType_InfiniteCycle,
		};

		enum TimerState
		{
			/// 运行
			ETimerState_Run,
			/// 暂停
			ETimerState_Pause,
			/// 停止
			ETimerState_Stop,
		};
	private:
		/** 开始时间 **/
		UInt32 m_startTime;
		/** 循环类型 **/
		UInt32 m_timerType;
		/** 间隔时间 **/
		UInt32 m_intervalTime;
		/** 循环次数 **/
		UInt32 m_cycleCount;
		/** 回调接口 **/
		TimerCallBack* m_pCallBack;
	public:
		/**
		* @brief 默认构造
		**/
		Timer(TimerCallBack* INpCallBack, UInt32 INtimerType = ETimerType_limitedCycle, UInt32 INintervalTime = 0, UInt32 INcycleCount = 0);

		/**
		* @brief 析构函数
		**/
		~Timer();

		/**
		* @brief 暂停
		* @exception
		* @note 提供给外部用于控制定时器的运行
		**/
		void Pause();

		/**
		* @brief 停止
		* @exception
		* @note 提供给外部用于控制定时器的生命周期
		**/
		void Kill();

		/**
		* @brief 重置
		**/
		void Reset();
	};
}


#endif