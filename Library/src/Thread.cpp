#include <Windows.h>
#include <process.h>

#include "Thread.h"
#include "Log.h"

namespace ZGF
{
	namespace Threading_Internal
	{
		struct ThreadData
		{
			/** 句柄 **/
			HANDLE handle;
			/** 线程编号 **/
			UInt32 threadID;
			/** 线程启动时间 **/
			UInt32 startTime;
			/** 是否正在运行 **/
			bool run;
			/** 名称 **/
			string threadName;
			
			ThreadData(const string& INname = "") : threadName(INname)
			{
				
				handle = INVALID_HANDLE_VALUE;
				threadID = 0;
				startTime = GetTickCount();
				run = false;
			}
		};
	}

	struct ThreadParam
	{
		bool startSucceed;
		Thread* thread;
		HANDLE startEvent;
	};

	Thread::Thread()
	{
		m_threadData = NULL;
		m_threadState = EThreadState_UnStarted;
		m_workCount = 0;
	}

	Thread::~Thread()
	{
		Stop(200);
		CloseHandle(m_threadData->handle);
		delete m_threadData;
	}

	UInt32 Thread::GetCPUCount()
	{
		SYSTEM_INFO info;
		GetSystemInfo(&info);
		return info.dwNumberOfProcessors;
	}

	void Thread::Sleep(UInt32 INmillisecond)
	{
		::Sleep(INmillisecond);
	}

	bool Thread::Start()
	{
		if(EThreadState_UnStarted == m_threadState && m_threadData == NULL)
		{
			ThreadParam threadParam;
			threadParam.startSucceed = false;
			threadParam.thread = this;
			threadParam.startEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
			m_threadData = new Threading_Internal::ThreadData();
			m_threadData->run = true;
			m_threadData->handle = (HANDLE)_beginthreadex(NULL, 0, &ThreadFunction, &threadParam, CREATE_SUSPENDED, &m_threadData->threadID);
			
			if(m_threadData->handle != INVALID_HANDLE_VALUE)
			{
				if(ResumeThread(m_threadData->handle) != EThreadOptFailed)
				{
					WaitForSingleObject(threadParam.startEvent, INFINITE);
					
					CloseHandle(threadParam.startEvent);
					
					if(!threadParam.startSucceed)
					{
						Stop(200);
						return false;
					}
					m_threadState = EThreadState_Running;
					return true;
				}
			}
		}

		return false;
	}

	bool Thread::Pause()
	{
		if(EThreadState_Running == m_threadState)
		{
			if(SuspendThread(m_threadData->handle) != EThreadOptFailed)
			{
				m_threadState = EThreadState_Pause;
				return true;
			}
		}
		return false;
	}

	bool Thread::Resume()
	{
		if(EThreadState_Pause == m_threadState)
		{
			if(ResumeThread(m_threadData->handle) != EThreadOptFailed)
			{
				m_threadState = EThreadState_Running;
				return true;
			}
		}
		return false;
	}

	bool Thread::Stop(UInt32 INwaitTime)
	{
		// 停止线程时不再考虑其当前状态
		if(m_threadData->handle != INVALID_HANDLE_VALUE)
		{
			m_threadData->run = false;
			ULong ret = WaitForSingleObject(m_threadData->handle, INwaitTime); 
			if(ret == WAIT_TIMEOUT)
			{
				NOTE_LOG("停止线程，等待超时, 返回");
				return false;
			}

			if(m_threadData->handle != INVALID_HANDLE_VALUE)
			{
				CloseHandle(m_threadData->handle);
				m_threadData->handle = INVALID_HANDLE_VALUE;
				m_threadData->threadID = 0;
			}
			m_threadState = EThreadState_Stop;
			return true;
		}
		return false;
	}

	UInt32 Thread::GetThreadID()
	{
		return m_threadData->threadID;
	}

	void Thread::SetCPU(UInt32 INcpuIndex)
	{
		SetThreadAffinityMask(m_threadData->handle, (1<<INcpuIndex));
	}

	bool Thread::IsRunning()
	{
		if(m_threadData && m_threadData->handle != INVALID_HANDLE_VALUE)
		{
			ULong ret = WaitForSingleObject(m_threadData->handle, 0);
			if(ret == WAIT_TIMEOUT)
			{
				return true;
			}
		}
		return false;
	}

	UInt32 __stdcall Thread::ThreadFunction(LPVOID INpThreadData)
	{
		UInt32 exitCode = 0;

		ThreadParam* pThreadParam = (ThreadParam*)INpThreadData;
		Thread* pThread = pThreadParam->thread;
		try
		{
			pThreadParam->startSucceed = pThread->OnThreadStartEvent();
		}
		catch(...)
		{
			pThreadParam->startSucceed = false;
		}

		MyASSERT(pThreadParam->startEvent != INVALID_HANDLE_VALUE);

		SetEvent(pThreadParam->startEvent);

		if(pThreadParam->startSucceed)
		{
			while(pThread->m_threadData->run)
			{
				try
				{
					if(!pThread->Run())
					{
						NOTE_LOG("退出线程 Run 函数");
						break;
					}
				}
				catch(...)
				{
					break;
				}
			}
		}

		try
		{
			pThread->OnThreadStopEvent();
		}
		catch(...)
		{
			// 记录异常
		}

		pThread->m_threadState = EThreadState_Stop;
		_endthreadex(0);

		NOTE_LOG("退出线程主循环函数");
		return exitCode;
	}
}
