#ifndef _NETBUF_H
#define _NETBUF_H
#include "NetDef.h"

//可优化为环状
struct SimpleBuf
{
	enum
	{
		BUFF_SIZE = 81920,
	};

	int     nHead;
	int     nTail;
	char    szBUF[BUFF_SIZE];
	void Tidy();
	int GetSpace()const;
	int GetLength()const;
	char* GetHeadBuf();
	char* GetTailBuf();
	void MoveHead(int nCount);
	void MoveTail(int nCount);
	bool Write(const void* pBuf,int nSize);
	bool Read(void* pBuf,int nSize);
	SimpleBuf();
};

class Packet;
class PacketFactory;
class NetBuffer
{
public:
	NetBuffer(PacketFactory* _packetFactory);
	virtual ~NetBuffer();
	NetBuffer& operator=(NetBuffer& _other);

	mutable_buffers_1& GetReceiveBuff();
	mutable_buffers_1& GetSendBuff();

	bool OnReceived(std::size_t transferred);
	void OnSended(std::size_t transferred);

	void PushSendingPacket(Packet* pPacket);
	Packet* PopReceivedPacket();


	typedef std::deque<Packet*> DEQ_PACKET;
private:
	void _PushReceivedPacket(Packet* pPacket);

	Packet* _PopSendingPacket();

	DEQ_PACKET m_deqSendPacket;
	My_CriticalSection m_packetSendCritical;

	DEQ_PACKET m_deqRecvPacket;
	My_CriticalSection m_packetRecvCritical;

	mutable_buffers_1 m_asioSendBuff;
	mutable_buffers_1 m_asioRecvBuff;

	SimpleBuf         m_simpleSendBuff;
	SimpleBuf         m_simpleRecvBuff;

	PacketFactory*    m_packetFactory;
};

#endif