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
		/** �ͻ������Ӷ����б� **/
		ClientSocketList m_clientSocketList;
		/** �ͻ������Ӷ���ӳ�� **/
		ClientSocketMap m_clientSocketMap;
		/** ���Ӷ����� **/
		CriticalSection m_criticalSection;
		/** �ͻ������Ӷ���� **/
		char* m_buffer;
	public:
		/**
		* @brief Ĭ�Ϲ���
		**/
		ClientSocketMgr();

		/**
		* @brief ��������
		**/
		~ClientSocketMgr();
	public:
		/**
		* @brief ��ʼ�������
		**/
		bool Initial(UInt32 INmaxClientSocket);

		/**
		* @brief ��ȡһ���µĿͻ������Ӷ���
		**/
		ClientSocket* GetNewClientSocket();

		/**
		* @brief ����һ���µĿͻ������Ӷ���
		**/
		ClientSocket* FindClientSocket(UInt32 INclientID);

		/**
		* @brief �ͷ�һ���ͻ������Ӷ���
		**/
		void FreeClientSocket(ClientSocket* INclientSocket);

		/**
		* @brief ����
		**/
		void Destroy();

		/**
		* @brief ��ʼ�������
		**/
		ClientSocket* CreateClientSocket();
	};
}


#endif