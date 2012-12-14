#include "CommonQueueService.h"

#include "Thread.h"
#include "PacketBase.h"
#include "Log.h"


namespace ZGF
{
	template<typename Owner>
	struct QueueServerThreadParam
	{
		/** 完成端口 **/
		HANDLE completePort;
		/** 队列服务对象 **/
		CommonQueueService<Owner>* pQueueService;
		/** 消息处理器 **/
		MsgHandler msgHandler;
	};

	template<typename Owner>
	class QueueServerThread : public Thread
	{
	private:
		/** 完成端口 **/
		HANDLE m_completePort;
		/** 队列服务对象 **/
		CommonQueueServer<Owner>* m_queueService;
		/** 消息处理器 **/
		MsgHandler m_msgHandler;
	public:
		bool Initial(const QueueServerThreadParam<Owner>& INparamData);

	private:
		virtual bool Run();

	};

	template<typename Owner>
	bool QueueServerThread::Initial(const QueueServerThreadParam<Owner>& INparamData)
	{
		m_completePort = INparamData.completePort;
		m_queueService = INparamData.pQueueService;
		m_msgHandler = INparamData.msgHandler;
		return true;
	}

	template<typename Owner>
	bool QueueServerThread::Run()
	{
		ULong transferSize = 0;
		QueueService* pQueueService;
		OVERLAPPED * pOverLapped = NULL;

		if(GetQueuedCompletionStatus(m_completePort, &transferSize, (ULONG_PTR*)&pQueueService, &pOverLapped, INFINITE))
		{
			if(pQueueService == NULL)
			{
				return false;
			}
			MsgNode* pNode = pQueueService->GetData();
			if(pNode != NULL)
			{
				m_msgHandler(pNode);
			}
			else
			{
				Log::Instance()->WriteError("%s, %d, Get NULL MsgNode!",
					__FUNCTION__, __LINE__);
			}
			return true;
		}

		return false;
	}

	template<typename Owner>
	QueueService::QueueService()
	{
		//
		m_completePort = INVALID_HANDLE_VALUE;
		m_msgList.clear();
	}
	
	template<typename Owner>
	QueueService::~QueueService()
	{
		StopService();
	}

	template<typename Owner>
	void QueueService::AddToQueue(MsgNode* INmsgNode)
	{
		Guard<CriticalSection> monitor(&m_msgListLock);
		m_msgList.push_back(INmsgNode);

		PostQueuedCompletionStatus(m_completePort, 0, (ULONG_PTR)this, NULL);

	}

	template<typename Owner>
	MsgNode* QueueService::GetData()
	{
		Guard<CriticalSection> monitor(&m_msgListLock);
		MsgNode* pNode = m_msgList.front();
		m_msgList.pop_front();
		return pNode;
	}

	template<typename Owner>
	bool QueueService::StartService(MsgHandler INmsgHandler)
	{
		m_completePort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, NULL);
		if(m_completePort == NULL)
		{
			int errorCode = GetLastError();
			return false;
		}

		try
		{
			m_queueServerThread = new QueueServerThread();
		}
		catch(...)
		{
			return false;
		}
		QueueServerThreadParam threadParam;
		threadParam.completePort = m_completePort;
		threadParam.pQueueService = this;
		threadParam.msgHandler = INmsgHandler;
		m_queueServerThread->Initial(threadParam);

		if(!m_queueServerThread->Start())
		{
			return false;
		}

		return true;
	}

	template<typename Owner>
	bool QueueService::StopService()
	{
		PostQueuedCompletionStatus(m_completePort, 0, NULL, NULL);
		while(true)
		{
			if(m_queueServerThread->GetThreadState() == EThreadState_Stop)
			{
				break;
			}
		}
		delete m_queueServerThread;
		CloseHandle(m_completePort);
		return true;
	}
}