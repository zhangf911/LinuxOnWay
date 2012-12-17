/*
 * NetServer.cpp
 *
 *  Created on: 2012-12-17
 *      Author: king
 */

#include "NetServer.h"
#include "NetWork.h"
#include "NetConnection.h"

NetServer::NetServer(ServerID id, NetWork& _netWork,const char* pIP,int nPort,Accepted_Handler& _handler,DisConnected_Handler _dishandler )
:m_netWork(_netWork)
,m_listener(_netWork.getService())
,m_AcceptHandler(_handler)
,m_DisConnectedHandler(_dishandler)
{
	m_listener.open(tcp::v4());
	if (pIP && pIP[0])
	{
		ip::address_v4 _address = ip::address_v4::from_string(pIP);
		tcp::endpoint _endpoint(_address,nPort);
		m_listener.bind(_endpoint);
	}
	else
	{
		m_listener.bind(tcp::endpoint(tcp::v4(),nPort));
	}
	m_listener.listen();
	m_id = id;
}

NetServer::~NetServer()
{
	//todo clear
	m_mapCon.clear();
}

bool NetServer::Start()
{
	if (!m_listener.is_open())
	{
		return false;
	}
	for (int i = 0; i < MAX_ACCPET_NUM; ++i)
	{
		NewAccept();
	}
	NET_LOG("Æô¶¯[%d]¸öAccpet¼àÌý",MAX_ACCPET_NUM);
	return true;
}

void NetServer::NewAccept()
{
	Auto_locker lock(m_conSection);
	Server_Con pCon(new S_NetConnection(m_netWork,*this,m_AcceptHandler,m_DisConnectedHandler));
	MY_ASSERT(m_mapCon.find(pCon->GetID()) == m_mapCon.end(),"",return;);

	m_mapCon[pCon->GetID()] = pCon;
	pCon->Accept(m_listener);
}

Server_Con NetServer::GetConnection( ConectionID _id )
{
	Auto_locker lock(m_conSection);

	map<ConectionID,Server_Con>::const_iterator _iter = m_mapCon.find(_id);
	if (_iter == m_mapCon.end())
	{
		return Server_Con();
	}
	return _iter->second;
}


void NetServer::OnReConnectOK( ConectionID _old,ConectionID _new )
{
	Server_Con pOld = GetConnection(_old);
	Server_Con pNew = GetConnection(_new);
	if (pOld && pNew)
	{
		//ÐÂµÄÁ¬½Ó´úÌæÔ­À´µÄÁ¬½Ó
		m_mapCon.erase(_new);

		pNew->ResetConnection(pOld);

		m_mapCon[pNew->GetID()] = pNew;
	}
}

void NetServer::Maintain()
{
	Auto_locker lock(m_conSection);

	map<ConectionID,Server_Con>::const_iterator _iter = m_mapCon.begin();
	for (;_iter != m_mapCon.end();)
	{
		Server_Con pCon = _iter->second;
		if (pCon)
		{
			pCon->Maintain();
			if (pCon->IsStopped())
			{
				_iter = m_mapCon.erase(_iter);
			}
			else
			{
				 ++_iter;
			}
		}
	}
}


