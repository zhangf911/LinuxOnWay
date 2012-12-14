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
		/** IP��ַ **/
		string m_ip;
		/** �˿� **/
		UInt16 m_port;
		/** �������� **/
		UInt32 m_maxListenCount;
		/** ��������� **/
		UInt32 m_maxClientCount;
		/** ����ص������� **/
		UInt32 m_maxOverlappedCount;
		/** ��Ϣ����� **/
		MsgNodeBufferMgr* m_msgNodeBufferMgr;
		/** ���з��� **/
		QueueService* m_pQueueService;

	public:
		/**
		* @brief ���캯��
		**/
		ConnectServer(UInt16 INport, UInt32 INmaxListenCount, UInt32 INmaxClientCount, UInt32 INbufferCount);
		
		/**
		* @brief ��������
		**/
		~ConnectServer();

		void OnNewConnection(Server_Con pCon,ConectionID id);
		void OnDisConnect(ConectionID id);

		void RecvAllMsg();
		void AddMsgToQuenue(ConectionID id,const char* pBuf,int nsize);
		void DisConnect(UInt32 INclientID);
	public:
						
		/**
		* @brief ������Ϣ�����
		**/
		void SetMsgNodeBufferMgr(MsgNodeBufferMgr* INmsgNodeBufferMgr);
								
		/**
		* @brief ���ö��з���
		**/
		void SetQueueService(QueueService* INpQueueService);

		/**
		* @brief �������ӷ�����
		**/
		bool Start();

		/**
		* @brief ֹͣ���ӷ�����
		**/
		bool Stop();

		/**
		* @brief ��������
		**/
		void SendData(UInt32 INclientID, const char* INdata, UInt32 INdataSize);

		/**
		* @brief ��ʾ�����߳����м���
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