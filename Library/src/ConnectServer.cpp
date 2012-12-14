#include "ConnectServer.h"
#include "ClientSocket.h"
#include "ClientSocketMgr.h"
#include "Overlapped.h"
#include "Thread.h"
#include "QueueService.h"
#include "WinSockExFunction.h"
#include "Log.h"

namespace ZGF
{
	ConnectServer::ConnectServer(UInt16 INport, UInt32 INmaxListenCount, UInt32 INmaxClientCount, UInt32 INbufferCount)
		: m_port(INport), m_maxListenCount(INmaxListenCount), m_maxClientCount(INmaxClientCount), m_maxOverlappedCount(INbufferCount)
		,m_netWork(Common_Factory::GetInstance())
	{

		m_ip = "";

		m_msgNodeBufferMgr = NULL;
		m_pQueueService = NULL;

	}

	ConnectServer::~ConnectServer()
	{
		Stop();
	}

	void ConnectServer::SetMsgNodeBufferMgr(MsgNodeBufferMgr* INmsgNodeBufferMgr)
	{
		MyASSERT(INmsgNodeBufferMgr != NULL);
		m_msgNodeBufferMgr = INmsgNodeBufferMgr;
	}

	void ConnectServer::SetQueueService(QueueService* INpQueueService)
	{
		MyASSERT(INpQueueService != NULL);
		m_pQueueService = INpQueueService;
	}

	bool ConnectServer::Start()
	{
		if(m_msgNodeBufferMgr == NULL || m_pQueueService == NULL)
		{
			Log::Instance()->WriteError("%s, %d, Check Initial Set",
				__FUNCTION__, __LINE__);
			return false;
		}
		m_netWork.Start();
		return m_netWork.AddServer(1,m_ip.c_str(),m_port
			,boost::bind(&ConnectServer::OnNewConnection,this,_1,_2)
			,boost::bind(&ConnectServer::OnDisConnect,this,_1));
	}

	void ConnectServer::SendData( UInt32 INclientID, const char* INdata, UInt32 INdataSize )
	{
		Server_Con pCon;
		{
			Auto_locker lock(m_conCirtical);
			if (m_mapCon.find(INclientID) == m_mapCon.end())
			{
				return;
			}
			pCon = m_mapCon[INclientID];
		}
		Common_Packet* pPacket = new Common_Packet(INdata,INdataSize);
		pCon->SendPack(pPacket);
	}

	bool ConnectServer::Stop()
	{
		m_netWork.Stop();
		return true;
	}


	void ConnectServer::PrintThreadWorkCount()
	{
		m_netWork.LogDebugInfo();
	}

	void ConnectServer::OnNewConnection( Server_Con pCon,ConectionID id )
	{
		Auto_locker lock(m_conCirtical);
		if (id == INVALID_CONNECTIONID)
		{
			MY_ASSERT(m_mapCon.find(pCon->GetID()) == m_mapCon.end(),"",return);
			m_mapCon[pCon->GetID()] = pCon;
		}
		else
		{

		}
	}

	void ConnectServer::OnDisConnect(ConectionID id )
	{
		MsgNode* pMsgNode = m_msgNodeBufferMgr->GetNewObject();
		pMsgNode->clientID = id;
		pMsgNode->msgType = 0;
		pMsgNode->msgLength = 0;
		pMsgNode->msgContent = "";
		pMsgNode->ObjectPort = m_port;
		m_pQueueService->AddToQueue(pMsgNode);

		{
			Auto_locker lock(m_conCirtical);
			map<ConectionID,Server_Con>::iterator _iter = m_mapCon.find(id);
			if (_iter != m_mapCon.end())
			{
				m_mapCon.erase(_iter);
			}
		}
	}

	void ConnectServer::RecvAllMsg()
	{
		recv_data* data = new recv_data;

		Auto_locker lock(m_conCirtical);
		map<ConectionID,Server_Con>::iterator _iter = m_mapCon.begin();
		for (; _iter != m_mapCon.end(); ++_iter)
		{
			Server_Con pCon = _iter->second;
			if (pCon)
			{
				data->id = pCon->GetID();
				data->pServer = this;

				Packet* pPacket = pCon->PopPacket();
				while(pPacket)
				{
					pPacket->process(data);
					SAFE_DELETE(pPacket);
					pPacket = pCon->PopPacket();
				}
			}
		}
		delete data;

	}

	void ConnectServer::AddMsgToQuenue(ConectionID id, const char* pBuf,int nsize)
	{
		ZGF::MsgNode* pNode = m_msgNodeBufferMgr->GetNewObject();
		pNode->clientID = id;
		short type = *(short*)pBuf;
		pBuf += sizeof(type);

		pNode->msgLength = nsize;
		pNode->msgType = type;
		pNode->msgContent = string(pBuf,nsize - sizeof(nsize) - sizeof(type));
		pNode->ObjectPort = m_port;

		m_pQueueService->AddToQueue(pNode);
	}

	void ConnectServer::DisConnect( UInt32 INclientID )
	{
		Auto_locker lock(m_conCirtical);
		if (m_mapCon.find(INclientID) != m_mapCon.end())
		{
			Server_Con pCon = m_mapCon[INclientID];
			pCon->Disconnect();
		}
	}
}

Common_Factory* Common_Factory::GetInstance()
{
	static Common_Factory s_Instance;
	return &s_Instance;
}

Packet* Common_Factory::MallocPakcet( int nType )
{
	return new Common_Packet;
}

void Common_Factory::FreePacket( Packet* _packet)
{
	delete (_packet);
}

int Common_Packet::GetSize()
{
	return m_size;
}

bool Common_Packet::read( SimpleBuf& pBuf )
{
	pBuf.Read(&m_size,sizeof(m_size));
	pBuf.Read(&m_szBuf,m_size - sizeof(m_size));
	return true;
}

bool Common_Packet::write( SimpleBuf& pBuf )
{
	pBuf.Write(&m_szBuf,m_size);
	return true;
}

void Common_Packet::process( void* data)
{
	recv_data* pData = (recv_data*)(data);

	pData->pServer->AddMsgToQuenue(pData->id,m_szBuf,m_size);
}

Common_Packet::Common_Packet()
{

	memset(m_szBuf,0,sizeof(m_szBuf));
	m_size = 0;
}

Common_Packet::Common_Packet( const char* _pBuf,int _size )
{
	MY_ASSERT(_size < sizeof(m_szBuf),"",;);
	memcpy(m_szBuf,_pBuf,_size);
	m_size = _size;
}
