#include "QueueService.h"
#include "Thread.h"
#include "PacketBase.h"
#include "Log.h"

namespace ZGF
{
	struct QueueServerThreadParam
	{
		/** 完成端口 **/
		HANDLE completePort;
		/** 队列服务对象 **/
		QueueService* pQueueService;
		/** 消息处理器 **/
		MsgHandler msgHandler;
	};

	class QueueServerThread : public Thread
	{
	private:
		/** 完成端口 **/
		HANDLE m_completePort;
		/** 队列服务对象 **/
		QueueService* m_queueService;
		/** 消息处理器 **/
		MsgHandler m_msgHandler;
	public:
		bool Initial(const QueueServerThreadParam& INparamData);

	private:
		virtual bool Run();

	};

	bool QueueServerThread::Initial(const QueueServerThreadParam& INparamData)
	{
		m_completePort = INparamData.completePort;
		m_queueService = INparamData.pQueueService;
		m_msgHandler = INparamData.msgHandler;
		return true;
	}

	bool QueueServerThread::Run()
	{
		ULong transferSize = 0;
		QueueService* pQueueService;
		OVERLAPPED * pOverLapped = NULL;

		if(GetQueuedCompletionStatus(m_completePort, &transferSize, (ULONG_PTR*)&pQueueService, &pOverLapped, INFINITE))
		{
			//if(pQueueService == NULL)
			//{
			//	NOTE_LOG("队列线程服务收到退出命令");
			//	return false;
			//}
			//MsgNode* pNode = pQueueService->GetData();
			//if(pNode != NULL)
			//{
			//	m_msgHandler(pNode);
			//}
			//else
			//{
			//	Log::Instance()->WriteError("%s, %d, Get NULL MsgNode!",
			//		__FUNCTION__, __LINE__);
			//}
			return true;
		}

		return false;
	}

	QueueService::QueueService()
	{
		//
		m_completePort = INVALID_HANDLE_VALUE;
		m_msgList.clear();
	}

	QueueService::~QueueService()
	{
		StopService();
	}

	void QueueService::AddToQueue(MsgNode* INmsgNode)
	{
		//Guard<CriticalSection> monitor(&m_msgListLock);
		//m_msgList.push_back(INmsgNode);

		//PostQueuedCompletionStatus(m_completePort, 0, (ULONG_PTR)this, NULL);
		
		if(INmsgNode != NULL)
		{
			m_msgHandler(INmsgNode);
		}
		else
		{
			Log::Instance()->WriteError("%s, %d, Get NULL MsgNode!",
				__FUNCTION__, __LINE__);
		}
	}

	MsgNode* QueueService::GetData()
	{
		Guard<CriticalSection> monitor(&m_msgListLock);
		MsgNode* pNode = m_msgList.front();
		m_msgList.pop_front();
		return pNode;
	}

	bool QueueService::StartService(MsgHandler INmsgHandler)
	{
		m_msgHandler = INmsgHandler;
		//m_completePort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 1);
		//if(m_completePort == NULL)
		//{
		//	int errorCode = GetLastError();
		//	return false;
		//}

		//try
		//{
		//	m_queueServerThread = new QueueServerThread();
		//}
		//catch(...)
		//{
		//	return false;
		//}
		//QueueServerThreadParam threadParam;
		//threadParam.completePort = m_completePort;
		//threadParam.pQueueService = this;
		//threadParam.msgHandler = INmsgHandler;
		//m_queueServerThread->Initial(threadParam);

		//if(!m_queueServerThread->Start())
		//{
		//	return false;
		//}

		return true;
	}

	bool QueueService::StopService()
	{
		//if(m_queueServerThread != NULL)
		//{
		//	PostQueuedCompletionStatus(m_completePort, 0, NULL, NULL);
		//	while(true)
		//	{
		//		if(m_queueServerThread->GetThreadState() == EThreadState_Stop)
		//		{
		//			break;
		//		}
		//		else
		//		{
		//			NOTE_LOG("线程当前状态 : %d, 等待队列服务线程关闭...");
		//			Sleep(50);
		//		}
		//	}
		//	delete m_queueServerThread;
		//	m_queueServerThread = NULL;
		//}

		//CloseHandle(m_completePort);
		return true;
	}
}