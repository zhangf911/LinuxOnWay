#ifndef LIBRARY_TCPSOCKET_SOCKETSERVER_H
#define LIBRARY_TCPSOCKET_SOCKETSERVER_H

#include "SocketComDef.h"
#include "BaseType.h"
#include "Lock.h"
#include "PacketEngine.h"
#include <string>
#include <list>
using std::string;
using std::list;
#include "NetWork.h"
#include "Packet.h"
#include "NetConnection.h"

namespace ZGF
{
	template <class Object> class ObjectPool;
	typedef ObjectPool<MsgNode> MsgNodeBufferMgr;
	class QueueService;

	class ConnectServer
	{
	private:
		NetWork m_netWork;
		map<ConectionID,Server_Con>       m_mapCon;
		My_CriticalSection                m_conCirtical;
		/** IP地址 **/
		string m_ip;
		/** 端口 **/
		UInt16 m_port;
		/** 最大监听数 **/
		UInt32 m_maxListenCount;
		/** 最大连接数 **/
		UInt32 m_maxClientCount;
		/** 最大重叠缓存数 **/
		UInt32 m_maxOverlappedCount;
		/** 消息对象池 **/
		MsgNodeBufferMgr* m_msgNodeBufferMgr;
		/** 队列服务 **/
		QueueService* m_pQueueService;

	public:
		/**
		* @brief 构造函数
		**/
		ConnectServer(UInt16 INport, UInt32 INmaxListenCount, UInt32 INmaxClientCount, UInt32 INbufferCount);
		
		/**
		* @brief 析构函数
		**/
		~ConnectServer();

		void OnNewConnection(Server_Con pCon,ConectionID id);
		void OnDisConnect(ConectionID id);

		void RecvAllMsg();
		void AddMsgToQuenue(ConectionID id,const char* pBuf,int nsize);
		void DisConnect(UInt32 INclientID);
	public:
						
		/**
		* @brief 设置消息对象池
		**/
		void SetMsgNodeBufferMgr(MsgNodeBufferMgr* INmsgNodeBufferMgr);
								
		/**
		* @brief 设置队列服务
		**/
		void SetQueueService(QueueService* INpQueueService);

		/**
		* @brief 启动连接服务器
		**/
		bool Start();

		/**
		* @brief 停止连接服务器
		**/
		bool Stop();

		/**
		* @brief 发送数据
		**/
		void SendData(UInt32 INclientID, const char* INdata, UInt32 INdataSize);

		/**
		* @brief 显示工作线程运行计数
		**/
		void PrintThreadWorkCount();
	};
}
struct recv_data
{
	ZGF::ConnectServer* pServer;
	ConectionID id;
};

class Common_Factory : public PacketFactory
{
public:
	static Common_Factory* GetInstance();
	virtual Packet* MallocPakcet(int nType);
	virtual void    FreePacket(Packet*);
};
class Common_Packet : public Packet
{
public:
	Common_Packet(const char* _pBuf,int _size);
	Common_Packet();
	virtual int  GetSize();
	virtual bool write(SimpleBuf& pBuf);
	virtual bool read(SimpleBuf& pBuf);
	virtual void process(void*) ;
protected:
	int m_size;
	char m_szBuf[40960];
};

#endif