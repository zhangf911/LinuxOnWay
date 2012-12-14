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
		/** ��ɶ˿� **/
		HANDLE m_completePort;
		/** ���з����߳� **/
		QueueServerThread* m_queueServerThread;
		/** ���ݶ����� **/
		CriticalSection m_msgListLock;
		/** ���ݶ��� **/
		MsgList m_msgList;
		/** ��Ϣ���� **/
		MsgHandler m_msgHandler;
	public:
		/**
		* @brief ���캯��
		**/
		QueueService();

		/**
		* @brief ��������
		**/
		~QueueService();

	public:

		/**
		* @brief �������
		**/
		void AddToQueue(MsgNode* INmsgNode);

		/**
		* @brief ��ȡ����
		**/
		MsgNode* GetData();
		
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