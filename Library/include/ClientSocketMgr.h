#ifndef LIBRARY_TCPSOCKET_CLIENTSOCKETMGR_H
#define LIBRARY_TCPSOCKET_CLIENTSOCKETMGR_H

#include <hash_map>
#include <list>
using stdext::hash_map;
using std::list;

#include "BaseType.h"
#include "Lock.h"

namespace ZGF
{
	class ClientSocket;

	enum {EMaxClientSocketCount = 5000,};

	class ClientSocketMgr
	{
		typedef list<ClientSocket*> ClientSocketList;
		typedef ClientSocketList::iterator ClientSocketListIter;
		typedef hash_map<UInt32, ClientSocket*> ClientSocketMap;
		typedef ClientSocketMap::iterator ClientSocketMapIter;
	private:
		/** 客户端连接对象列表 **/
		ClientSocketList m_clientSocketList;
		/** 客户端连接对象映射 **/
		ClientSocketMap m_clientSocketMap;
		/** 连接对象锁 **/
		CriticalSection m_criticalSection;
		/** 客户端连接对象池 **/
		char* m_buffer;
	public:
		/**
		* @brief 默认构造
		**/
		ClientSocketMgr();

		/**
		* @brief 析构函数
		**/
		~ClientSocketMgr();
	public:
		/**
		* @brief 初始化对象池
		**/
		bool Initial(UInt32 INmaxClientSocket);

		/**
		* @brief 获取一个新的客户端连接对象
		**/
		ClientSocket* GetNewClientSocket();

		/**
		* @brief 查找一个新的客户端连接对象
		**/
		ClientSocket* FindClientSocket(UInt32 INclientID);

		/**
		* @brief 释放一个客户端连接对象
		**/
		void FreeClientSocket(ClientSocket* INclientSocket);

		/**
		* @brief 销毁
		**/
		void Destroy();

		/**
		* @brief 初始化对象池
		**/
		ClientSocket* CreateClientSocket();
	};
}


#endif