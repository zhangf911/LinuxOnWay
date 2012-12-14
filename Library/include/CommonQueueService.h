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
		/** ��ɶ˿� **/
		HANDLE m_completePort;
		/** ���з����߳� **/
		QueueServerThread* m_queueServerThread;
		/** ���ݶ����� **/
		CriticalSection m_msgListLock;
		/** ���ݶ���ӳ�� */
		EntityMsgListMap m_entityMsgListMap;

	public:
		/**
		* @brief ���캯��
		**/
		CommonQueueServer();

		/**
		* @brief ��������
		**/
		~CommonQueueServer();

	public:

		/**
		* @brief �������
		**/
		void AddToQueue(Owner* INpOwner, MsgNode* INmsgNode);

		/**
		* @brief ��ȡ����
		**/
		MsgNode* GetData(Owner* INpOwner);
		
		/**
		* @brief ��������
		**/
		bool StartService(MsgHandler INmsgHandler);
		
		/**
		* @brief ֹͣ����
		**/
		bool StopService();
	};
}


#endif