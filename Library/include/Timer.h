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
			/// ����ѭ��
			ETimerType_limitedCycle,
			/// ����ѭ��
			ETimerType_InfiniteCycle,
		};

		enum TimerState
		{
			/// ����
			ETimerState_Run,
			/// ��ͣ
			ETimerState_Pause,
			/// ֹͣ
			ETimerState_Stop,
		};
	private:
		/** ��ʼʱ�� **/
		UInt32 m_startTime;
		/** ѭ������ **/
		UInt32 m_timerType;
		/** ���ʱ�� **/
		UInt32 m_intervalTime;
		/** ѭ������ **/
		UInt32 m_cycleCount;
		/** �ص��ӿ� **/
		TimerCallBack* m_pCallBack;
	public:
		/**
		* @brief Ĭ�Ϲ���
		**/
		Timer(TimerCallBack* INpCallBack, UInt32 INtimerType = ETimerType_limitedCycle, UInt32 INintervalTime = 0, UInt32 INcycleCount = 0);

		/**
		* @brief ��������
		**/
		~Timer();

		/**
		* @brief ��ͣ
		* @exception
		* @note �ṩ���ⲿ���ڿ��ƶ�ʱ��������
		**/
		void Pause();

		/**
		* @brief ֹͣ
		* @exception
		* @note �ṩ���ⲿ���ڿ��ƶ�ʱ������������
		**/
		void Kill();

		/**
		* @brief ����
		**/
		void Reset();
	};
}


#endif