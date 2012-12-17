/*
 * NetWork.cpp
 *
 *  Created on: 2012-12-17
 *      Author: king
 */

#include "NetWork.h"
#include <process.h>
#include "NetServer.h"
#include "NetConnection.h"

NetWork::NetWork(PacketFactory* _factory)
{
	m_state = State_None;
	m_pWork = NULL;
	m_packetFactory = _factory;
}

NetWork::~NetWork()
{
	if (m_state == State_Noraml)
	{
		Stop();
	}
	//todo clear
	if (m_pWork)
	{
		SAFE_DELETE(m_pWork);
	}
	map<ServerID,NetServer*>::const_iterator _iter = m_mapServer.begin();
	for (; _iter != m_mapServer.end(); ++_iter)
	{
		delete _iter->second;
	}
	m_mapServer.clear();

	m_mapCon.clear();

}


void NetWork::Start()
{
NET_TRY
	NET_LOG("NetWork³õÊ¼»¯¿ªÊ¼");
	MY_ASSERT(m_state == State_None,"",return;);

	m_state = State_Noraml;
	m_pWork = new asio::io_service::work(m_service);

	int nThreadCount = DEFAULT_RUN_THREAD;

	SYSTEM_INFO info;
	GetSystemInfo(&info);
	nThreadCount = info.dwNumberOfProcessors * 2 + 1;

	if (nThreadCount > MAX_RUN_THREAD)
		nThreadCount = MAX_RUN_THREAD;

	NET_LOG("Ìí¼Ó%d¸öÍøÂç¹¤×÷Ïß³Ì",nThreadCount);

	for (int i = 0; i < nThreadCount; ++i)
	{
		m_workThreads.add_thread(new boost::thread(boost::bind(&io_service::run,&m_service)));
	}

	m_maintainThread = boost::thread(boost::bind(&NetWork::_Maintain_Work,this));

	NET_LOG("NetWork³õÊ¼»¯Íê³É");
NET_CATCH
}

void NetWork::Stop()
{
NET_TRY
	NET_LOG("ÕýÔÚÍ£Ö¹NetWork....");

	m_state = State_Stopping;

	SAFE_DELETE(m_pWork);
	m_service.stop();

	m_workThreads.join_all();
	m_maintainThread.timed_join(boost::posix_time::microseconds(2000));

	m_state = State_Stopped;

	NET_LOG("NetWorkÕý³£Í£Ö¹¹¤×÷");
NET_CATCH
}

bool NetWork::AddServer( ServerID id,const char* pIP,int nPort ,Accepted_Handler _handler,DisConnected_Handler _dishandler)
{
NET_TRY
	if (m_state != State_Noraml)
	{
		return false;
	}
	NET_LOG("Ìí¼Ó·þÎñÆ÷,ID:[%d]",id);

	MY_ASSERT(m_mapServer.find(id) == m_mapServer.end(),"",return false;);

	NetServer* pNewServer = new NetServer(id,*this,pIP,nPort,_handler,_dishandler);
	if (!pNewServer->Start())
	{
		NET_ERROR("Ìí¼Ó·þÎñÆ÷Ê§°Ü,ID[%d]",id);

		SAFE_DELETE(pNewServer);
		return false;
	}

	{
		Auto_locker lock(m_serverCritical);
		m_mapServer[id] = pNewServer;
	}

	return true;
NET_CATCH
	return false;
}


Client_Con NetWork::AddClient( DisConnected_Handler _disConHandler,Connected_Handler _conHandler )
{
	Auto_locker lock(m_connectionCritical);

	Client_Con pCon(new C_NetConnection(*this,_conHandler,_disConHandler));
	m_vecConnecting.push_back(pCon);
	return pCon;
}

bool NetWork::Asyn_Connect(const char* pIP,int nPort,DisConnected_Handler _disConHandler,Connected_Handler _connectedHandler )
{
	if (m_state != State_Noraml)
	{
		return false;
	}
	Auto_locker lock(m_connectionCritical);

	Client_Con pCon(new C_NetConnection(*this,_connectedHandler,_disConHandler));
	m_vecConnecting.push_back(pCon);

	pCon->Asyn_Connect(pIP,nPort);
	return true;
}

bool NetWork::ReConnect(ConectionID id)
{
	Client_Con pCon = _getConnection(id);
	if (pCon)
	{
		return pCon->ReConnect();
	}
	return false;
}

void NetWork::DisConnect( ConectionID id )
{
	Client_Con pCon = _getConnection(id);
	if (pCon)
	{
		pCon->Disconnect();
	}
}

void NetWork::DisConnect( ServerID _sid,ConectionID _cid )
{
	NetServer* pServer = _getServer(_sid);
	if (pServer)
	{
		Server_Con pCon = pServer->GetConnection(_cid);
		if (pCon)
		{
			 pCon->Disconnect();
		}
	}
}


Packet* NetWork::PopPacket( ConectionID id )
{
	Client_Con& pCon = _getConnection(id);
	if (pCon)
	{
		return pCon->PopPacket();
	}
	else
		return NULL;

}

Packet* NetWork::PopPacket( ServerID _sid,ConectionID _cid )
{
	NetServer* pServer = _getServer(_sid);
	if (pServer)
	{
		Server_Con pCon = pServer->GetConnection(_cid);
		if (pCon)
		{
			return pCon->PopPacket();
		}
	}
	return NULL;

}

bool NetWork::SendPacket( ConectionID cid,Packet* packet )
{
	Client_Con pCon = _getConnection(cid);
	if (pCon)
	{
		return pCon->SendPack(packet);
	}
	return false;
}

bool NetWork::SendPacket( ServerID _sid,ConectionID _cid,Packet* packet )
{
	NetServer* pServer = _getServer(_sid);
	if (pServer)
	{
		Server_Con pCon = pServer->GetConnection(_cid);
		if (pCon)
		{
			return pCon->SendPack(packet);
		}
	}
	return false;
}

Client_Con& NetWork::_getConnection(ConectionID id)
{
 	Auto_locker lock(m_connectionCritical);

	map<ConectionID,Client_Con>::iterator _iter = m_mapCon.find(id);
	if (_iter == m_mapCon.end())
	{
		static Client_Con s_ClientCon;
		return s_ClientCon;
	}
	return _iter->second;
}

NetServer* NetWork::_getServer( ServerID id )
{
	Auto_locker lock(m_serverCritical);
	map<ServerID,NetServer*>::const_iterator _iter = m_mapServer.find(id);
	if (_iter == m_mapServer.end())
	{
		return NULL;
	}
	return _iter->second;
}

void NetWork::_setupConnection( ConectionID id,Client_Con pCon )
{
	Auto_locker lock(m_connectionCritical);
	if (_getConnection(id) == NULL)
	{
		m_mapCon[id] = pCon;
	}
	else
	{
		MY_ASSERT(0,"",;);
	}
}

void NetWork::_Maintain_Work()
{
	while(1)
	{
		if (m_state == State_Stopping || m_state == State_Stopped)
		{
			return;
		}
		//´¦Àí¹ýÆÚµÄÁ¬½Ó
		{
			Auto_locker lock(m_connectionCritical);
			vector<Client_Con>::iterator _iter = m_vecConnecting.begin();
			for (; _iter != m_vecConnecting.end(); )
			{
				Client_Con pCon = (*_iter);

				if (pCon == NULL)
				{
					_iter = m_vecConnecting.erase(_iter);
				}
				else
				{
					pCon->Maintain();
					if (pCon->IsStopped())
					{
						_iter = m_vecConnecting.erase(_iter);
					}
					else
					{
						++_iter;
					}
				}
			}

			map<ConectionID,Client_Con>::iterator _iter2 = m_mapCon.begin();
			for (; _iter2 != m_mapCon.end(); )
			{
				Client_Con pCon = _iter2->second;
				if (pCon)
				{
					pCon->Maintain();
					if (pCon->IsStopped())
					{
						m_mapCon.erase(_iter2++);
					}
					else
					{
						_iter2++;
					}
				}
				else
				{
					m_mapCon.erase(_iter2++);
				}
			}
		}
		{
			Auto_locker lock(m_serverCritical);
			map<ServerID,NetServer*>::const_iterator _iter = m_mapServer.begin();
			for (; _iter != m_mapServer.end() ; ++_iter)
			{
				NetServer* pServer = _iter->second;
				if (pServer)
				{
					pServer->Maintain();
				}
			}
		}

		boost::this_thread::sleep(boost::posix_time::millisec(1000));
	}
}

void NetWork::LogDebugInfo()
{
	NET_LOG("==========ÍøÂçÔËÐÐ×´Ì¬==========");
	{
		NET_LOG("µ±Ç°ServerConÊýÁ¿:[%d]",S_NetConnection::s_count);
		NET_LOG("µ±Ç°ClientConÊýÁ¿:[%d]",C_NetConnection::s_count);

	}
	NET_LOG("================================");
}



