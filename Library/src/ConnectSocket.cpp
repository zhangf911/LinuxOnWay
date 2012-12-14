#include "ConnectSocket.h"
#include "SocketAddr.h"
#include "Overlapped.h"
#include "SocketOpt.h"
#include "PacketEngine.h"
#include "ObjectPool.h"
#include "QueueService.h"
#include "WinSockExFunction.h"
#include "Thread.h"
#include "Lock.h"
#include "Log.h"

namespace ZGF
{
	

	ConnectSocket::ConnectSocket() : m_netWork(Conecter_Packet_Factory::GetInstance())
	{
		m_port = 0;
	}

	ConnectSocket::~ConnectSocket()
	{
		Disconnect();
	}

	void ConnectSocket::SetMsgNodeBufferMgr(MsgNodeBufferMgr* INmsgNodeBufferMgr)
	{
		MyASSERT(INmsgNodeBufferMgr != NULL);
		m_msgNodeBufferMgr = INmsgNodeBufferMgr;
	}

	void ConnectSocket::SetQueueService(QueueService* INpQueueService)
	{
		MyASSERT(INpQueueService != NULL);
		m_pQueueService = INpQueueService;
	}

	bool ConnectSocket::Connect(const char* INip, unsigned short INport)
	{
		m_port = INport;
		if (m_pCon == NULL)
		{
			m_netWork.Start();
			m_pCon = m_netWork.AddClient(boost::bind(&ConnectSocket::OnDisConnect,this,_1)
				,boost::bind(&ConnectSocket::OnConnected,this,_1));
		}
		m_pCon->Asyn_Connect(INip,INport);
		int nCount = 20;
		while (nCount--)
		{
			if (m_pCon->GetState() == NetConnection::State_Connected)
			{
				return true;
			}
			else
			{
				Sleep(200);
				if (m_pCon->GetState() == NetConnection::State_Connected)
				{
					return true;
				}
			}
		}
	
		return false;
	}

	bool ConnectSocket::Send(const char* INdata, unsigned int INsize)
	{
		Conecter_Packet* pPacket = new Conecter_Packet(INdata,INsize);
		m_pCon->SendPack(pPacket);

		return true;
	}

	void ConnectSocket::RecvMsg()
	{
		Packet* pPacket = m_pCon->PopPacket();
		while(pPacket)
		{
			pPacket->process(this);
			SAFE_DELETE(pPacket);
			pPacket = m_pCon->PopPacket();
		}
	}

	void ConnectSocket::Disconnect(bool INinitiative)
	{
		m_pCon->Disconnect();
	}

	void ConnectSocket::OnConnected( int )
	{

	}

	void ConnectSocket::OnDisConnect( ConectionID id )
	{

	}

	void ConnectSocket::AddMsgToQuenue( const char* pBuf,int nsize )
	{
		ZGF::MsgNode* pNode = m_msgNodeBufferMgr->GetNewObject();
		pNode->clientID = 0;
		short type = *(short*)pBuf;
		pBuf += sizeof(type);

		pNode->ObjectPort = m_port;
		pNode->msgLength = nsize;
		pNode->msgType = type;
		pNode->msgContent = string(pBuf,nsize - sizeof(nsize) - sizeof(type));

		m_pQueueService->AddToQueue(pNode);
	}

}

Conecter_Packet_Factory* Conecter_Packet_Factory::GetInstance()
{
	static Conecter_Packet_Factory s_Instance;
	return &s_Instance;
}

Packet* Conecter_Packet_Factory::MallocPakcet( int nType )
{
	return new Conecter_Packet;
}

void Conecter_Packet_Factory::FreePacket( Packet* _packet)
{
	delete (_packet);
}



void Conecter_Packet::process( void* data)
{
	ZGF::ConnectSocket* pConnectSocket = (ZGF::ConnectSocket*)(data);
	pConnectSocket->AddMsgToQuenue(m_szBuf,m_size);
}

Conecter_Packet::Conecter_Packet( const char* _pBuf,int _size ) : Common_Packet(_pBuf,_size)
{

}

Conecter_Packet::Conecter_Packet() : Common_Packet()
{

}
