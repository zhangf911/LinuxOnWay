#include "ClientSocket.h"
#include "ClientSocketMgr.h"
#include "Log.h"

namespace ZGF
{
	ClientSocketMgr::ClientSocketMgr()
	{
		m_buffer = NULL;
		m_clientSocketList.clear();
		m_clientSocketMap.clear();
	}

	ClientSocketMgr::~ClientSocketMgr()
	{
		Destroy();
	}

	bool ClientSocketMgr::Initial(UInt32 INmaxClientSocket)
	{
		if(INmaxClientSocket > EMaxClientSocketCount)
		{
			Log::Instance()->WriteError("%s, %d, param INmaxClientSocket is too big",
				__FUNCTION__, __LINE__);
			return false;
		}

		try
		{
			m_buffer = new char[INmaxClientSocket * sizeof(ClientSocket)];
		}
		catch(...)
		{
			Log::Instance()->WriteException("%s, %d, bad memory! Allocate ClientSocket buffer memory failed!",
				__FUNCTION__, __LINE__);
			return false;
		}

		// ÇÐ·Ö
		for(UInt32 i = 0; i < INmaxClientSocket; ++i)
		{
			ClientSocket* pClientSocket = (ClientSocket*)(m_buffer + i * sizeof(ClientSocket));
			new (pClientSocket) ClientSocket;
			if(!pClientSocket->Initial())
			{
				Destroy();
				return false;
			}
			pClientSocket->SetClientID(i + 1);
			m_clientSocketList.push_back(pClientSocket);
			m_clientSocketMap[i + 1] = pClientSocket;
		}
		return true;
	}

	ClientSocket* ClientSocketMgr::GetNewClientSocket()
	{
		ClientSocket* pClientSocket = NULL;
		Guard<CriticalSection> monitor(&m_criticalSection);
		if(m_clientSocketList.size())
		{
			pClientSocket = m_clientSocketList.front();
			m_clientSocketList.pop_front();
		}
		return pClientSocket;
	}

	ClientSocket* ClientSocketMgr::FindClientSocket(UInt32 INclientID)
	{
		ClientSocket* pClientSocket = NULL;
		ClientSocketMapIter it = m_clientSocketMap.find(INclientID);
		if(it != m_clientSocketMap.end())
		{
			pClientSocket = it->second;
		}
		return pClientSocket;
	}

	void ClientSocketMgr::FreeClientSocket(ClientSocket* INclientSocket)
	{
		Log::Instance()->WriteNote("%s, %d, Free A ClientSocket",
			__FUNCTION__, __LINE__);
		Guard<CriticalSection> monitor(&m_criticalSection);
		m_clientSocketList.push_back(INclientSocket);
	}

	void ClientSocketMgr::Destroy()
	{
		m_clientSocketList.clear();
		m_clientSocketMap.clear();

		delete[] m_buffer;
		m_buffer = NULL;
	}

	ClientSocket* ClientSocketMgr::CreateClientSocket()
	{
		ClientSocket* pClientSocket = NULL;
		try
		{
			pClientSocket = new ClientSocket();
		}
		catch(...)
		{
			return NULL;
		}
		return pClientSocket;
	}
}