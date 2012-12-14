#ifndef LIBRARY_TCPSOCKET_CLIENTSOCKET_H
#define LIBRARY_TCPSOCKET_CLIENTSOCKET_H

#include "SocketComDef.h"
#include "BaseType.h"
#include "ObjectPool.h"
#include "PacketEngine.h"

#include <string>
#include <list>
using std::string;
using std::list;

namespace ZGF
{
	//struct MsgNode;
	class SocketAddr;
	struct OverLapped_Plus;
	typedef OverLapped_Plus OverLappedBuffer;
	template<class Object> class ObjectPool;
	typedef ObjectPool<OverLappedBuffer> OverlappedBufferMgr;
	typedef ObjectPool<MsgNode> MsgNodeBufferMgr;
	class QueueService;

	enum {EMaxRecvBufferSize = 8 * 1024,};

	enum ClientSocketState
	{
		EClientSocketState_Common,
		EClientSocketState_Close,
	};

	class ClientSocket
	{
		friend class IOCompleteThread;
		typedef list<OverLappedBuffer*> OverlappedList;
		typedef OverlappedList::iterator OverlappedListIter;
	private:
		/** ����״̬ **/
		UInt32 m_state;
		/** �ͻ��˱�� **/
		UInt32 m_clientID;
		/** ����ʱ�� **/
		UInt32 m_connectTime;
		/** ���ͼ��� **/
		UInt32 m_sendCount;
		/** ���ռ��� **/
		UInt32 m_recvCount;
		/** �����ջ����С **/
		UInt32 m_maxRecvBufferSize;
		/** ���ô��� **/
		UInt32 m_reusedCount;
		/** �Ƿ������� **/
		bool m_completeConnect;
		/** �Ƿ��ѹ�����ɶ˿� **/
		bool m_associateflage;
		/** ���ص�ַ **/
		SocketAddr* m_localAddr;
		/** �ͻ��˵�ַ **/
		SocketAddr* m_remoteAddr;
		/** δ�������б� **/
		OverlappedList m_sendingList;
		/** �����׽��� **/
		SOCKET m_socket;
		/** �����׽��� **/
		SOCKET m_listenSocket;
		/** ��ɶ˿� **/
		HANDLE m_completePort;
		/** �ص���������� **/
		OverlappedBufferMgr* m_overlappedBufferMgr;
		/** ��Ϣ����� **/
		MsgNodeBufferMgr* m_msgNodeBufferMgr;
		/** ���з��� **/
		QueueService* m_pQueueService;
		/** ���ջ����С **/
		UInt32 m_recvBufferSize;
		/** ���ջ��� **/
		char* m_recvBuffer;
		/** ������ **/
		CriticalSection m_recvLock;
		/** IO�� **/
		CriticalSection m_ioLock;
	public:
		/**
		* @brief Ĭ�Ϲ���
		**/
		ClientSocket();

		/**
		* @brief ��������
		**/
		~ClientSocket();

	public:
		/**
		* @brief ��ȡ�׽���
		**/
		SOCKET GetClientSocket()
		{
			return m_socket;
		}

		/**
		* @brief ���ÿͻ��˱��
		**/
		inline void SetClientID(UInt32 INclientID)
		{
			m_clientID = INclientID;
		}

		/**
		* @brief ��ȡ�ͻ��˱��
		**/
		inline UInt32 GetClientID()
		{
			return m_clientID;
		};

		/**
		* @brief ��ȡ�ͻ���IP��ַ
		**/
		string GetClientIP();

		/**
		* @brief ��ȡ����ʱ��
		**/
		UInt32 GetConnectTime();

		/**
		* @brief ��ȡ���ͼ���
		**/
		inline UInt32 GetSendCount()
		{
			return m_sendCount;
		};
		
		/**
		* @brief ��ȡ���ͼ���
		**/
		inline UInt32 GetRecvCount()
		{
			return m_recvCount;
		};

		/**
		* @brief ��ȡ���ô���
		* @return ���ô���
		* @exception 
		* @note 
		*/
		inline UInt32 GetReusedCount()
		{
			return m_reusedCount;
		}

		/**
		* @brief �������ô���
		* @exception 
		* @note 
		*/
		inline void AddReuseCount()
		{
			++m_reusedCount;
		};

		/**
		* @brief �Ƿ�����Ч�׽���
		**/
		inline bool IsValidSocket()
		{
			return m_socket != INVALID_SOCKET ? true : false;
		};

		/**
		* @brief �Ƿ��������
		**/
		inline bool IsCompleteAccept()
		{
			return m_completeConnect;
		}

		/**
		* @brief ������ɶ˿�
		**/
		void SetCompletePort(HANDLE INcompletePort);

		/**
		* @brief ���ü����׽���
		**/
		void SetListenSocket(SOCKET INlistenSocket);
		
		/**
		* @brief �����ص����������
		**/
		void SetOverlappedBufferMgr(OverlappedBufferMgr* INbufferMgr);
				
		/**
		* @brief ������Ϣ�����
		**/
		void SetMsgNodeBufferMgr(MsgNodeBufferMgr* INmsgNodeBufferMgr);
										
		/**
		* @brief ���ö��з���
		**/
		void SetQueueService(QueueService* INpQueueService);

		/**
		* @brief ��ʼ��
		**/
		bool Initial();

		/**
		* @brief �ͻ��˶Ͽ����Ӵ���
		**/
		void Disconnect();

		/**
		* @brief �����ر����Ӵ���
		**/
		void CloseSocket();

		/**
		* @brief �����׽���
		**/
		void ResetSocket(OverLappedBuffer* INpBuffer);
		
		/**
		* @brief ������Դ
		**/
		void Clear();

		/**
		* @brief ����δ�������б�
		**/
		void ClearSendingList();

		/**
		* @brief Ͷ�ݽ�����������
		* @param INpBuffer : ��������
		* @return ture : Ͷ�ݳɹ� false : Ͷ��ʧ��
		* @note  ����������÷������첽ģʽ�����Ժ�������ʱ�����ܱ�֤�����ѷ��ͣ�ֻ�ǽ�����Ͷ�ݸ��˲���ϵͳ���ɲ���ϵͳ���д���
		**/
		bool PostAccept(OverLappedBuffer* INpBuffer);

		/**
		* @brief Ͷ�ݷ�������
		* @param INpBuffer : ��������
		* @return ture : Ͷ�ݳɹ� false : Ͷ��ʧ��
		* @note  ����������÷������첽ģʽ�����Ժ�������ʱ�����ܱ�֤�����ѷ��ͣ�ֻ�ǽ�����Ͷ�ݸ��˲���ϵͳ���ɲ���ϵͳ���д���
		**/
		bool PostSend(OverLappedBuffer* INpBuffer);

		/**
		* @brief Ͷ�ݽ�������
		* @param INpBuffer : ��������
		* @return true : Ͷ�ݳɹ� false : Ͷ��ʧ��
		* @note  ����������÷������첽ģʽ�����Ժ�������ʱ�����ܱ�֤�����ѽ��գ�ֻ�ǽ�����Ͷ�ݸ��˲���ϵͳ���ɲ���ϵͳ���д���
		**/
		bool PostRecv(OverLappedBuffer* INpBuffer);

		/**
		* @brief Ͷ�ݶϿ���������
		* @param INpBuffer : ��������
		* @return true : Ͷ�ݳɹ� false : Ͷ��ʧ��
		**/
		bool PostDisconnect(OverLappedBuffer* INpBuffer);

	private:
		/**
		* @brief ������ɴ���
		* @param INpBuffer : ��������
		* @return true
		**/
		bool OnAcceptComplete(OverLappedBuffer* INpBuffer, UInt32 INbufferSize);

		/**
		* @brief ������ɴ���
		* @param INpBuffer : ��������
		* @return true : �ɹ� false : ʧ��
		* @note  
		**/
		bool OnSendComplete(OverLappedBuffer* INpBuffer, UInt32 INbufferSize);

		/**
		* @brief ������ɴ���
		* @param INpBuffer : ��������
		* @return true : �ɹ� false : ʧ��
		* @note  
		**/
		bool OnRecvComplete(OverLappedBuffer* INpBuffer, UInt32 INbufferSize);
		
		/**
		* @brief ���ݽ���
		* @param INpBuffer : ��������
		* @return true : �ɹ� false : ʧ��
		* @note  
		**/
		bool ParseData(char* IOrecvBuffer, UInt32* IOrecvBufferSize, OverLappedBuffer* INpolBuffer, UInt32 INolBufferSize);
	};
}

#endif