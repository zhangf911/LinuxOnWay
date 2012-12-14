#ifndef LIBRARY_THREAD_THREAD_H
#define LIBRARY_THREAD_THREAD_H

#include <string>
using std::string;
#include "BaseType.h"

/**
*@brief 线程
**/
namespace ZGF
{
	enum {EThreadOptFailed = 0xFFFFFFFF,};

	enum ThreadState
	{
		/// 未启动
		EThreadState_UnStarted,
		/// 正常运行
		EThreadState_Running,
		/// 挂起
		EThreadState_Pause,
		/// 停止
		EThreadState_Stop,
		/// 终止
	};

	namespace Threading_Internal
	{
		struct ThreadData;
	};

	class Thread
	{
	protected:
		/** 线程内部数据 **/
		Threading_Internal::ThreadData* m_threadData;
		/** 线程状态 **/
		UInt32 m_threadState;
		/** 线程运行计数器 **/
		UInt32 m_workCount;
	public:
		/**
		* @brief 构造函数
		**/
		Thread();

		/**
		* @brief 析构函数
		**/
		virtual ~Thread();

	public:
		/**
		* @brief 创建并启动
		* @note  静态函数
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
		* @brief 获取CPU个数
		* @note  静态函数
		**/
		static UInt32 GetCPUCount();

		/**
		* @brief 睡眠
		* @note  静态函数
		**/
		static void Sleep(UInt32 INmillisecond);

		/**
		* @brief 启动
		**/
		bool Start();

		/**
		* @brief 挂起
		**/
		bool Pause();

		/**
		* @brief 唤醒
		**/
		bool Resume();

		/**
		* @brief 停止
		**/
		bool Stop(UInt32 INwaitTime);

		/**
		* @brief 线程编号
		**/
		UInt32 GetThreadID();

		/**
		* @brief 线程状态
		**/
		ThreadState GetThreadState()
		{
			return ThreadState(m_threadState);
		};

		/**
		* @brief 获取线程工作计数器
		**/
		UInt32 GetThreadWorkCount()
		{
			return m_workCount;
		}

		/**
		* @brief 设置线程的执行CPU
		**/
		void SetCPU(UInt32 INcpuIndex);

	private:
		/**
		* @brief 是否正在运行
		**/
		bool IsRunning();

		/**
		* @brief 线程启动时初始化处理
		**/
		virtual bool OnThreadStartEvent(){return true;};

		/**
		* @brief 线程停止时清理处理
		**/
		virtual bool OnThreadStopEvent(){return true;};

		/**
		* @brief 运行
		**/
		virtual bool Run() = NULL;

		/**
		* @brief 线程函数
		**/
		static UInt32 __stdcall ThreadFunction(void* INpThreadData);
	};
}



#endif