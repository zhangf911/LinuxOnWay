#ifndef LIBRARY_THREAD_THREAD_H
#define LIBRARY_THREAD_THREAD_H

#include <string>
using std::string;
#include "BaseType.h"

/**
*@brief �߳�
**/
namespace ZGF
{
	enum {EThreadOptFailed = 0xFFFFFFFF,};

	enum ThreadState
	{
		/// δ����
		EThreadState_UnStarted,
		/// ��������
		EThreadState_Running,
		/// ����
		EThreadState_Pause,
		/// ֹͣ
		EThreadState_Stop,
		/// ��ֹ
	};

	namespace Threading_Internal
	{
		struct ThreadData;
	};

	class Thread
	{
	protected:
		/** �߳��ڲ����� **/
		Threading_Internal::ThreadData* m_threadData;
		/** �߳�״̬ **/
		UInt32 m_threadState;
		/** �߳����м����� **/
		UInt32 m_workCount;
	public:
		/**
		* @brief ���캯��
		**/
		Thread();

		/**
		* @brief ��������
		**/
		virtual ~Thread();

	public:
		/**
		* @brief ����������
		* @note  ��̬����
		**/
		template <class ChildThread>
		ChildThread* CreateAndStart()
		{
			ChildThread* pThread = new ChildThread;
			if(!pThread->Start())
			{
				delete pThread;
				return NULL;
			}
			return pThread;
		};

		/**
		* @brief ��ȡCPU����
		* @note  ��̬����
		**/
		static UInt32 GetCPUCount();

		/**
		* @brief ˯��
		* @note  ��̬����
		**/
		static void Sleep(UInt32 INmillisecond);

		/**
		* @brief ����
		**/
		bool Start();

		/**
		* @brief ����
		**/
		bool Pause();

		/**
		* @brief ����
		**/
		bool Resume();

		/**
		* @brief ֹͣ
		**/
		bool Stop(UInt32 INwaitTime);

		/**
		* @brief �̱߳��
		**/
		UInt32 GetThreadID();

		/**
		* @brief �߳�״̬
		**/
		ThreadState GetThreadState()
		{
			return ThreadState(m_threadState);
		};

		/**
		* @brief ��ȡ�̹߳���������
		**/
		UInt32 GetThreadWorkCount()
		{
			return m_workCount;
		}

		/**
		* @brief �����̵߳�ִ��CPU
		**/
		void SetCPU(UInt32 INcpuIndex);

	private:
		/**
		* @brief �Ƿ���������
		**/
		bool IsRunning();

		/**
		* @brief �߳�����ʱ��ʼ������
		**/
		virtual bool OnThreadStartEvent(){return true;};

		/**
		* @brief �߳�ֹͣʱ������
		**/
		virtual bool OnThreadStopEvent(){return true;};

		/**
		* @brief ����
		**/
		virtual bool Run() = NULL;

		/**
		* @brief �̺߳���
		**/
		static UInt32 __stdcall ThreadFunction(void* INpThreadData);
	};
}



#endif