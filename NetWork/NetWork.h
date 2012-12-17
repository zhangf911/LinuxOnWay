/*
 * NetWork.h
 *
 *  Created on: 2012-12-17
 *      Author: king
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include "NetDef.h"

class Packet;
class PacketFactory;
class C_NetConnection;
//·ÇÏß³Ì°²È«
class NetWork
{
	friend class NetServer;
	friend class NetConnection;
	friend class C_NetConnection;
	friend class S_NetConnection;

public:
	NetWork(PacketFactory* _factory);
	~NetWork();
	void		 LogDebugInfo();

	void         Start();
	void         Stop();
	//for Server
	bool         AddServer(ServerID id,const char* pIP,int nPort, Accepted_Handler _handler,DisConnected_Handler _dishandler);
	//for Client
	Client_Con   AddClient(DisConnected_Handler _disConHandler,Connected_Handler _conHandler);

protected:
	//ÔÝÊ±²»¿ª·ÅµÄ½Ó¿Ú
	bool         Asyn_Connect(const char* pIP,int nPort,DisConnected_Handler _disConHandler,Connected_Handler _conHandler);
	bool         ReConnect(ConectionID id);
	void		 DisConnect(ConectionID id);
	bool         SendPacket(ConectionID cid,Packet* packet);
	Packet*      PopPacket(ConectionID cid);

	bool         SendPacket(ServerID _sid,ConectionID _cid,Packet* packet);
	Packet*      PopPacket(ServerID _sid,ConectionID _cid);
	void		 DisConnect(ServerID,ConectionID id);

private:
	enum
	{
		State_None,
		State_Noraml,
		State_Stopping,
		State_Stopped,
	};
	asio::io_service& getService(){return m_service;}
	Client_Con&		 _getConnection(ConectionID id);
	NetServer*		 _getServer(ServerID id);
	void			 _setupConnection(ConectionID id,Client_Con pCon);
	PacketFactory*   _getPakcetFactory(){return m_packetFactory;}
private:
	void         _Maintain_Work();
	asio::io_service				  m_service;
	asio::io_service::work*			  m_pWork;
	boost::thread_group				  m_workThreads;
	boost::thread					  m_maintainThread;
	int								  m_state;
	My_CriticalSection				  m_serverCritical;
	map<ServerID,NetServer*>		  m_mapServer;

	My_CriticalSection				  m_connectionCritical;
	map<ConectionID,Client_Con>       m_mapCon;
	vector<Client_Con>		          m_vecConnecting;

	PacketFactory*					  m_packetFactory;
};

#endif /* NETWORK_H_ */
