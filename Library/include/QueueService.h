#ifndef LIBRARY_TCPSOCKET_QUEUESERVICE_H
#define LIBRARY_TCPSOCKET_QUEUESERVICE_H

#include <list>
using std::list;

#include "Lock.h"
#include <Windows.h>

#include "PacketEngine.h"

namespace ZGF
{
	class QueueServerThread;

	typedef void (*MsgHandler)(MsgNode* INmsgNode);

	class QueueService
	{
		typedef list<MsgNode*> MsgList;
		typedef MsgList::iterator MsgListIter;
	private:
		/** 完成端口 **/
		HANDLE m_completePort;
		/** 队列服务线程 **/
		QueueServerThread* m_queueServerThread;
		/** 数据队列锁 **/
		CriticalSection m_msgListLock;
		/** 数据队列 **/
		MsgList m_msgList;
		/** 消息处理 **/
		MsgHandler m_msgHandler;
	public:
		/**
		* @brief 构造函数
		**/
		QueueService();

		/**
		* @brief 析构函数
		**/
		~QueueService();

	public:

		/**
		* @brief 加入队列
		**/
		void AddToQueue(MsgNode* INmsgNode);

		/**
		* @brief 获取数据
		**/
		MsgNode* GetData();
		
		/**
		* @brief 启动服务
		**/
		bool StartService(MsgHandler INmsgHandler);
		
		/**
		* @brief 停止服务
		**/
		bool StopService();
	};
}

#endif