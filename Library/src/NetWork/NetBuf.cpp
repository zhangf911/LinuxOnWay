#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "NetBuf.h"
#include "Packet.h"

void SimpleBuf::Tidy()
{
	assert(nHead <= nTail);

	memmove(szBUF,szBUF+nHead,nTail - nHead);
	nTail = nTail - nHead;
	nHead = 0; 
}

int SimpleBuf::GetSpace() const
{
	assert(nHead <= nTail);

	return BUFF_SIZE - nTail;
}

int SimpleBuf::GetLength() const
{
	assert(nHead <= nTail);

	return nTail - nHead;
}

char* SimpleBuf::GetHeadBuf()
{
	assert(nHead <= nTail);

	return szBUF + nHead;
}

char* SimpleBuf::GetTailBuf()
{
	assert(nHead <= nTail);

	return szBUF + nTail;
}


bool SimpleBuf::Write(const void* pBuf,int nSize )
{
	int nSpace = GetSpace();
	if (nSpace >= nSize)
	{
		memcpy(GetTailBuf(),pBuf,nSize);
		nTail += nSize;
		assert(nHead <= nTail);

		return true;
	}
	else
		return false;
}

bool SimpleBuf::Read( void* pBuf,int nSize )
{
	int nLength = GetLength();
	if (nLength >= nSize)
	{
		memcpy(pBuf,GetHeadBuf(),nSize);
		nHead += nSize;
		assert(nHead <= nTail);
		return true;
	}
	else
		return false;
}

SimpleBuf::SimpleBuf()
{
	nHead = 0;
	nTail = 0;
	memset(szBUF,0,BUFF_SIZE);
}

void SimpleBuf::MoveTail(int nCount)
{
	assert(nTail + nCount <= BUFF_SIZE);
	nTail += nCount;
}

void SimpleBuf::MoveHead( int nCount )
{
	assert(nHead + nCount <= nTail);
	nHead += nCount;

}

void NetBuffer::PushSendingPacket( Packet* pPacket )
{
	Auto_locker lock(m_packetSendCritical);
	m_deqSendPacket.push_back(pPacket);
}

Packet* NetBuffer::PopReceivedPacket()
{
 	Auto_locker lock(m_packetRecvCritical);
	if (m_deqRecvPacket.empty())
	{
		return NULL;
	}
	Packet* pPacket = m_deqRecvPacket.front();
	m_deqRecvPacket.pop_front();
	return pPacket;
}



bool NetBuffer::OnReceived( std::size_t transferred )
{
	m_simpleRecvBuff.MoveTail(transferred);

	int nLenght = m_simpleRecvBuff.GetLength();
	while(nLenght > sizeof(Head))
	{
		Head* pHead = (Head*)m_simpleRecvBuff.GetHeadBuf();
		
// 		if (pHead->nPrefiex != Packet_Prefix)
// 		{
// 			NET_ERROR("收到一个错误的包头");
// 			return false;
// 		}
		if (pHead->nSize > nLenght)
		{
			break;
		}
//		m_simpleRecvBuff.MoveHead(sizeof(Head));
		Packet* pPacket = m_packetFactory->MallocPakcet(0);
		if (pPacket == NULL)
		{
			NET_ERROR("未定义的消息包类型[%d]",0);
			return false;
		}

		pPacket->read(m_simpleRecvBuff);
		_PushReceivedPacket(pPacket);

		nLenght = m_simpleRecvBuff.GetLength();
	}
	m_simpleRecvBuff.Tidy();
	return true;

}

void NetBuffer::OnSended( std::size_t transferred )
{
	m_simpleSendBuff.MoveHead(transferred);
	m_simpleSendBuff.Tidy();
}


NetBuffer::NetBuffer(PacketFactory* _packetFactory)
:m_asioSendBuff(NULL,0)
,m_asioRecvBuff(NULL,0)
,m_packetFactory(_packetFactory)
{

}
NetBuffer::~NetBuffer()
{
	DEQ_PACKET::iterator _iter = m_deqSendPacket.begin();
	for (; _iter != m_deqSendPacket.end(); ++_iter)
	{
		if (*_iter)
		{
			delete (*_iter);
		}
	}
	m_deqSendPacket.clear();

	_iter = m_deqRecvPacket.begin();
	for (; _iter != m_deqRecvPacket.end(); ++_iter)
	{
		if (*_iter)
		{
			delete (*_iter);
		}
	}
	m_deqRecvPacket.clear();
}
mutable_buffers_1& NetBuffer::GetReceiveBuff()
{
	m_asioRecvBuff = boost::asio::buffer(m_simpleRecvBuff.GetTailBuf(),m_simpleRecvBuff.GetSpace());
	return m_asioRecvBuff;
}

mutable_buffers_1& NetBuffer::GetSendBuff()
{
	if (m_simpleSendBuff.GetSpace() < SimpleBuf::BUFF_SIZE / 2)
	{
		m_simpleSendBuff.Tidy();
		if (m_simpleSendBuff.GetSpace() < SimpleBuf::BUFF_SIZE / 2)
		{
			int nLen = m_simpleSendBuff.GetLength();

#ifdef MAX_PER_SEND
			nLen = nLen > MAX_PER_SEND ? MAX_PER_SEND : nLen;
#endif // MAX_PER_SEND

			m_asioSendBuff = boost::asio::buffer(m_simpleSendBuff.GetHeadBuf(),nLen);
			return m_asioSendBuff;
		}
	}

	Packet* pPacket = _PopSendingPacket();
	while(pPacket)
	{
		if (pPacket->GetSize() > SimpleBuf::BUFF_SIZE / 2)
		{
			NET_LOG("严重错误,包太大了，包丢失");
			MY_ASSERT(false,"",;);
		}
		
		Head head;
// 		head.nPrefiex = Packet_Prefix;
// 		head.nType = pPacket->GetType();
		head.nSize = pPacket->GetSize();
// 		if (!m_simpleSendBuff.Write(&head,sizeof(Head)))
// 		{
// 			NET_LOG("严重错误,发送缓冲区无法写入，包丢失");
// 			MY_ASSERT(false,"",;);
// 		}
		

		if (!pPacket->write(m_simpleSendBuff))
		{
			m_simpleSendBuff.nTail -= sizeof(Head);
			NET_LOG("严重错误,发送缓冲区无法写入，包丢失");
			MY_ASSERT(false,"",;);
		}

		m_packetFactory->FreePacket(pPacket);

		if (m_simpleSendBuff.GetSpace() < SimpleBuf::BUFF_SIZE / 2)
		{
			m_simpleSendBuff.Tidy();
			if (m_simpleSendBuff.GetSpace() < SimpleBuf::BUFF_SIZE / 2)
			{
				break;
			}
		}
		pPacket = _PopSendingPacket();
	}
	int nLen = m_simpleSendBuff.GetLength();
	
#ifdef MAX_PER_SEND
	nLen = nLen > MAX_PER_SEND ? MAX_PER_SEND : nLen;
#endif // MAX_PER_SEND

	m_asioSendBuff = boost::asio::buffer(m_simpleSendBuff.GetHeadBuf(),nLen);
	return m_asioSendBuff;
}


NetBuffer& NetBuffer::operator=( NetBuffer& _other )
{
	m_deqSendPacket = _other.m_deqSendPacket;
	_other.m_deqSendPacket.clear();

	m_deqRecvPacket = _other.m_deqRecvPacket;
	_other.m_deqRecvPacket.clear();

	m_simpleSendBuff = _other.m_simpleSendBuff;
	m_simpleRecvBuff = _other.m_simpleRecvBuff;

	return *this;
}

void NetBuffer::_PushReceivedPacket( Packet* pPacket )
{
	Auto_locker lock(m_packetRecvCritical);
	m_deqRecvPacket.push_back(pPacket);

}

Packet* NetBuffer::_PopSendingPacket()
{
	Auto_locker lock(m_packetSendCritical);
	if (m_deqSendPacket.empty())
	{
		return NULL;
	}
	Packet* pPacket = m_deqSendPacket.front();
	m_deqSendPacket.pop_front();
	return pPacket;
}


