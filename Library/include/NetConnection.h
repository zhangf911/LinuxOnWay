#ifndef _NETCONNECTION_H
#define _NETCONNECTION_H
#include "NetDef.h"
#include "NetBuf.h"


class NetWork;
class NetServer;
class Packet;
class PacketSetupConnecion;

class NetConnection : public enable_shared_from_this<NetConnection>
{
public:
	//////////////////////////////////////////////////////////////////////////
	//debuginfo
	int m_sendedByte;
	int m_sendedPacket;
	int m_receivedByte;
	int m_receivedPacket;
	//////////////////////////////////////////////////////////////////////////

	NetConnection(NetWork& _netWork,DisConnected_Handler& _handler);

	virtual ~NetConnection();
	enum
	{
		State_None,
		State_Connecting,
		State_Connected,
		State_Disconnecting,
		State_Stopped,
	};
	bool SendPack(Packet* pPacket);
	Packet* PopPacket();
	void Disconnect();

	int GetCheckSum()const{return m_checkSum;}
	ConectionID GetID()const {return m_id;}
	int GetState()const{return m_state;}
	bool IsStopped()const{return m_state == State_Stopped;}
	virtual void Maintain() = 0;
protected:
	class ConIDGenerator
	{
	public:
		ConIDGenerator();
		ConectionID GenID();
	private:
		volatile ConectionID m_seed;	
	};

	static ConIDGenerator s_IDGenerator;

protected:
	virtual void SetupConnection() = 0;
	void _send_handler(error_code _error,std::size_t transferred);
	bool _appendreceive();
	void _appendsend();
	void _receive_handler(error_code _error,std::size_t transferred);

	tcp::socket				m_socket;
	tcp::endpoint			m_remoteAddress;
	volatile int	 		m_state;
	ConectionID				m_id;
	int						m_checkSum;

	NetWork&				m_netWork;
	NetBuffer				m_bufPacket;
	bool					m_bIsPendingSend;
	My_CriticalSection		m_CriticalSendOpt;

	boost::timer			m_disconnectingTimer;
	boost::timer			m_connectingTimer;

	DisConnected_Handler	m_DisConnectdHandler;
	NetBuffer				m_bufSetup;


};
class C_NetConnection : public NetConnection
{
public:
	//debug info
	static int s_count;

	//////////////////////////////////////////////////////////////////////////
	C_NetConnection(NetWork& _netWork,Connected_Handler& _handler,DisConnected_Handler& _dishandler);
	~C_NetConnection();
	bool Asyn_Connect(const char* pIP,int nPort);
	bool ReConnect();  //∂œœﬂ÷ÿ¡¨
	virtual void Maintain();
private:
	virtual void SetupConnection();
	void _connect_handler(error_code _error);
	void _setup_send_handler(error_code _error,std::size_t transferred);
	void _setup_receive_handler(error_code _error,std::size_t transferred);

	Connected_Handler m_ConnectedHandler;
};

class S_NetConnection : public NetConnection
{
public:
	//debug info
	static int s_count;

	//////////////////////////////////////////////////////////////////////////
	S_NetConnection(NetWork& _netWork,NetServer& _netServer,Accepted_Handler& _handler,DisConnected_Handler& _disHandler);
	~S_NetConnection();
	void Accept(tcp::acceptor&);
	virtual void SetupConnection();

	virtual void Maintain();
	void ResetConnection(Server_Con pNew);

private:
	void _accept_handler(ConectionID _id,error_code _error);
	void _setup_send_handler(error_code _error,std::size_t transferred);
	void _setup_receive_handler(error_code _error,std::size_t transferred);

	NetServer& m_netServer;
	Accepted_Handler m_AcceptHandler;

};


#endif