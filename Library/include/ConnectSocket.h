#ifndef LIBRARY_TCPSOCKET_CONNECTSOCKET_H
#define LIBRARY_TCPSOCKET_CONNECTSOCKET_H

#include "SocketComDef.h"
#include "BaseType.h"
#include "Lock.h"
#include "PacketEngine.h"
#include "ConnectServer.h"

#include <list>
using std::list;
#include "NetWork.h"
#include "Packet.h"
#include "NetConnection.h"

namespace ZGF
{
	template<class Object> class ObjectPool;
	typedef ObjectPool<MsgNode> MsgNodeBufferMgr;
	class QueueService;

	class ConnectSocket
	{
	private:
		NetWork m_netWork;
		Client_Con m_pCon;
		/** 消息对象池 **/
		MsgNodeBufferMgr* m_msgNodeBufferMgr;
		/** 队列服务 **/
		QueueService* m_pQueueService;
		UInt16 m_port;
	public:
		/**
		* @brief 默认构造
		**/
		ConnectSocket();

		/**
		* @brief 析构函数
		**/
		~ConnectSocket();

	public:
				
		/**
		* @brief 设置消息对象池
		**/
		void SetMsgNodeBufferMgr(MsgNodeBufferMgr* INmsgNodeBufferMgr);
										
		/**
		* @brief 设置队列服务
		**/
		void SetQueueService(QueueService* INpQueueService);

		bool Connect(const char* INip, unsigned short INport);

		bool Send(const char* INdata, unsigned int INsize);

		/**
		* @brief 断开连接
		**/
		void Disconnect(bool INinitiative = false);

		void RecvMsg();

		void AddMsgToQuenue(const char* pBuf,int nsize);
	private:

		void OnConnected(int );
		void OnDisConnect(ConectionID id);
	};
}

class Conecter_Packet_Factory : public PacketFactory
{
public:
	static Conecter_Packet_Factory* GetInstance();
	virtual Packet* MallocPakcet(int nType);
	virtual void    FreePacket(Packet*);
};

class Conecter_Packet : public Common_Packet
{
public:
	Conecter_Packet(const char* _pBuf,int _size);
	Conecter_Packet();
	virtual void process(void*) ;
};

#endif