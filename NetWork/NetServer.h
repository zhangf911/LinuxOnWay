/*
 * NetServer.h
 *
 *  Created on: 2012-12-17
 *      Author: king
 */

#ifndef NETSERVER_H_
#define NETSERVER_H_

#include "NetDef.h"
#include "NetBuf.h"

class NetWork;
class S_NetConnection;

class NetServer
{
	friend class S_NetConnection;
public:
	NetServer(ServerID id,NetWork& _netWork,const char* pIP,int nPort,Accepted_Handler& _handler,DisConnected_Handler _dishandler);
	~NetServer();
	bool Start();
	Server_Con GetConnection(ConectionID id);
	void OnReConnectOK(ConectionID _old,ConectionID _new);
	void Maintain();
protected:
	void NewAccept();
private:

	tcp::acceptor				m_listener;
	NetWork&					m_netWork;

	My_CriticalSection			m_conSection;
	map<ConectionID,Server_Con> m_mapCon;

	Accepted_Handler			m_AcceptHandler;
	DisConnected_Handler		m_DisConnectedHandler;
	ServerID					m_id;
};

#endif /* NETSERVER_H_ */
