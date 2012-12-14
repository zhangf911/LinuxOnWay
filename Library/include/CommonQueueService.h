#ifndef LIBRARY_TCPSOCKET_COMMONQUEUESERVICE_H
#define LIBRARY_TCPSOCKET_COMMONQUEUESERVICE_H

#include <list>
using std::list;
#include <hash_map>
using stdext::hash_map;

#include "Lock.h"
#include <Windows.h>

#include "PacketEngine.h"

namespace ZGF
{
	template <typename Owner>
	class CommonQueueServer
	{
	public:
		typedef list<MsgNode*> MsgList;
		typedef MsgList::iterator MsgListIter;
		typedef hash_map<Owner*, MsgList> EntityMsgListMap;
		typedef EntityMsgListMap::iterator EntityMsgListMapIter;
	private:
		/** 完成端口 **/
		HANDLE m_completePort;
		/** 队列服务线程 **/
		QueueServerThread* m_queueServerThread;
		/** 数据队列锁 **/
		CriticalSection m_msgListLock;
		/** 数据队列映射 */
		EntityMsgListMap m_entityMsgListMap;

	public:
		/**
		* @brief 构造函数
		**/
		CommonQueueServer();

		/**
		* @brief 析构函数
		**/
		~CommonQueueServer();

	public:

		/**
		* @brief 加入队列
		**/
		void AddToQueue(Owner* INpOwner, MsgNode* INmsgNode);

		/**
		* @brief 获取数据
		**/
		MsgNode* GetData(Owner* INpOwner);
		
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