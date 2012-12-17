/*
 * NetConnection.cpp
 *
 *  Created on: 2012-12-17
 *      Author: king
 */

#include "NetConnection.h"
#include "NetWork.h"
#include "Packet.h"
#include "Packet/Internal_Packet.h"
#include "NetServer.h"
#include <WinSock2.h>
#include <Windows.h>
#include <MMSystem.h>

#pragma comment(lib,"winmm.lib")

NetConnection::ConIDGenerator::ConIDGenerator()
{
	m_seed = INVALID_CONNECTIONID;
}

ConectionID NetConnection::ConIDGenerator::GenID()
{
	return 	InterlockedIncrement(&m_seed);
}


NetConnection::ConIDGenerator NetConnection::s_IDGenerator;

NetConnection::NetConnection(NetWork& _netWork,DisConnected_Handler& _handler)
:m_netWork(_netWork)
,m_bufPacket(_netWork._getPakcetFactory())
,m_bufSetup(Internal_PacketFactory::GetInstance())
,m_socket(_netWork.getService())
,m_DisConnectdHandler(_handler)
{
	m_state = State_None;
	m_bIsPendingSend = false;
	m_checkSum = 0;

	m_sendedByte = 0;
	m_sendedPacket = 0;
	m_receivedByte = 0;
	m_receivedPacket = 0;
}
NetConnection::~NetConnection()
{


}

bool NetConnection::_appendreceive()
{
NET_TRY
	if (m_state != State_Connected)
	{
		return false;
	}


	mutable_buffers_1& buff =  m_bufPacket.GetReceiveBuff();
	m_socket.async_read_some(buff
		,boost::bind(&NetConnection::_receive_handler,(this->shared_from_this()),_1,_2));
	return true;
NET_CATCH
	return false;
}

void NetConnection::_receive_handler( error_code _error,std::size_t transferred )
{
NET_TRY

	if (_error)
	{
		if (NetError_EOF != _error.value())
			NET_ERROR("[%d]½ÓÊÕÊý¾ÝÊ§°Ü,´íÎó´úÂë:[%d-%s]",m_id,_error.value(),_error.message().c_str());

		if (_error.value() == NetError_ConnReset)
		{
			m_state = State_Disconnecting;
			m_disconnectingTimer.restart();
			m_DisConnectdHandler(m_id,true);
		}
		else
		{
			m_state = State_Stopped;
			m_socket.close();
			m_DisConnectdHandler(m_id,false);
		}
	}
	else
	{
		bool bOK = m_bufPacket.OnReceived(transferred);
		if (!bOK)
		{
			Disconnect();
		}
		_appendreceive();
	}
NET_CATCH
}


bool NetConnection::SendPack(Packet* pPacket)
{
NET_TRY
	if (m_state != State_Connected && m_state != State_Disconnecting)
	{
		return false;
	}

	m_bufPacket.PushSendingPacket(pPacket);
	if (m_state == State_Connected)
	{
		Auto_locker lock(m_CriticalSendOpt);
		_appendsend();
	}
	return true;
NET_CATCH
	return false;
}

void NetConnection::_send_handler( error_code _error,std::size_t transferred )
{
NET_TRY

	if (_error)
	{
		{
			Auto_locker lock(m_CriticalSendOpt);
			m_bIsPendingSend = false;
		}

		NET_ERROR("[%d]·¢ËÍÊý¾ÝÊ§°Ü,´íÎó´úÂë:[%d-%s]",m_id,_error.value(),_error.message().c_str());

		if (_error.value() == NetError_ConnReset)
		{
			m_state = State_Disconnecting;
			m_disconnectingTimer.restart();
			m_DisConnectdHandler(m_id,true);
		}
		else
		{
			m_socket.shutdown(socket_base::shutdown_receive);
			m_state = State_Stopped;
		}

	}
	else
	{
		Auto_locker lock(m_CriticalSendOpt);
		m_bIsPendingSend = false;
		m_bufPacket.OnSended(transferred);
 		_appendsend();
	}
NET_CATCH
}

Packet* NetConnection::PopPacket()
{
NET_TRY
	return m_bufPacket.PopReceivedPacket();
NET_CATCH
    return NULL;
}

void NetConnection::_appendsend()
{
NET_TRY
	if (m_state != State_Connected)
	{
		return ;
	}

	if (!m_bIsPendingSend)
	{
		m_bIsPendingSend = true;
		mutable_buffers_1& buff = m_bufPacket.GetSendBuff();
		if (boost::asio::buffer_size(buff) == 0)
		{
			m_bIsPendingSend = false;
			return ;
		}
		m_socket.async_send(buff
			,boost::bind(&NetConnection::_send_handler,(this->shared_from_this()),_1,_2));
	}
NET_CATCH
}

void NetConnection::Disconnect()
{
NET_TRY
	if (m_state == State_None || m_state == State_Stopped)
	{
		return;
	}

	NET_LOG("[%d]Á¬½Ó¹Ø±Õ",m_id);
	m_socket.shutdown(socket_base::shutdown_send);
	m_state = State_Stopped;
NET_CATCH
}

C_NetConnection::C_NetConnection( NetWork& _netWork,Connected_Handler& _handler,DisConnected_Handler& _dishandler )
: NetConnection(_netWork,_dishandler)
,m_ConnectedHandler(_handler)
{
	m_id = INVALID_CONNECTIONID;
	s_count++;
}
C_NetConnection::~C_NetConnection()
{
	s_count--;
}

bool C_NetConnection::Asyn_Connect( const char* pIP,int nPort )
{
NET_TRY

	MY_ASSERT(pIP,"",return false;)
	MY_ASSERT(m_state == State_None,"",return false;);

	m_state = State_Connecting;
	m_connectingTimer.restart();

	ip::address_v4 _address = ip::address_v4::from_string(pIP);
	m_remoteAddress = tcp::endpoint(_address,nPort);
	m_socket.async_connect(m_remoteAddress
		,boost::bind(&C_NetConnection::_connect_handler,dynamic_pointer_cast<C_NetConnection>(this->shared_from_this()),_1));

	NET_LOG("Ïò[%s:%d]·¢ÆðÁ¬½Ó",_address.to_string().c_str(),nPort);

NET_CATCH
	return true;
}

void C_NetConnection::_connect_handler(error_code _error )
{
NET_TRY
	if (_error)
	{
		NET_ERROR("ÎÞ·¨Á¬½Óµ½·þÎñÆ÷£¬´íÎó´úÂë:[%d-%s]",_error.value(),_error.message().c_str());
		if (m_state != State_Connecting)
		{
			return;
		}
		m_ConnectedHandler(_error.value());

		//×Ô¶¯ÖØÁ¬
		NET_LOG("×Ô¶¯ÖØÐÂÁ¬½Óµ½·þÎñÆ÷",_error.value());

		m_socket.async_connect(m_remoteAddress
			,boost::bind(&C_NetConnection::_connect_handler,dynamic_pointer_cast<C_NetConnection>(this->shared_from_this()),_1));
	}
	else
	{
		NET_LOG("Á¬½Óµ½·þÎñÆ÷£¬ÕýÔÚ½¨Á¢Connection[%s]",m_socket.local_endpoint().address().to_string().c_str());
#ifdef ENABLE_INTERNAL_CONNECTION
		SetupConnection();
#else
		m_state = State_Connected;
		m_ConnectedHandler(0);
		_appendreceive();
#endif // ENABLE_INTERNAL_CONNECTION
	}
NET_CATCH
}
bool C_NetConnection::ReConnect()
{
NET_TRY
	if (m_state == State_Connecting)
	{
		return true;
	}
	if (m_state != State_Disconnecting)
	{
		return false;
	}

	m_state = State_Connecting;
	m_connectingTimer.restart();

	m_socket.async_connect(m_remoteAddress
		,boost::bind(&C_NetConnection::_connect_handler,dynamic_pointer_cast<C_NetConnection>(this->shared_from_this()),_1));

	NET_LOG("Ïò[%s:%d]·¢ÆðÖØÁ¬",m_remoteAddress.address().to_string().c_str(),m_remoteAddress.port());
	return true;
NET_CATCH
	return false;
}


void C_NetConnection::SetupConnection()
{
NET_TRY
	if (m_state != State_Connecting)
	{
		return;
	}

	PacketSetupConnecion* pPacket = new PacketSetupConnecion(m_id,m_checkSum);
	m_bufSetup.PushSendingPacket(pPacket);

	mutable_buffers_1& buff = m_bufSetup.GetSendBuff();
	m_socket.async_send(buff
		,boost::bind(&C_NetConnection::_setup_send_handler,dynamic_pointer_cast<C_NetConnection>(this->shared_from_this()),_1,_2));


	mutable_buffers_1& buffRecive =  m_bufSetup.GetReceiveBuff();
	m_socket.async_read_some(buffRecive
		,boost::bind(&C_NetConnection::_setup_receive_handler,dynamic_pointer_cast<C_NetConnection>(this->shared_from_this()),_1,_2));
NET_CATCH
}

void C_NetConnection::_setup_receive_handler( error_code _error,std::size_t transferred )
{
NET_TRY
	if (_error)
	{
		NET_ERROR("½¨Á¢Á¬½ÓµÄÊ±ºòÊ§°ÜÁË,½ÓÊÕ½¨Á¢Ð­ÒéÊ§°Ü,´íÎó´úÂë:[%d-%s]",_error.value(),_error.message().c_str());
		m_ConnectedHandler(_error.value());
	}
	else
	{
		if (m_state != State_Connecting)
		{
			return;
		}
		bool bOK = m_bufSetup.OnReceived(transferred);
		if (!bOK)
		{
			Disconnect();
			return;
		}
		PacketSetupConnecion* pPacket = dynamic_cast<PacketSetupConnecion*>(m_bufSetup.PopReceivedPacket());
		if (pPacket)
		{
			if (m_id != pPacket->GetConID())
			{
				m_id = pPacket->GetConID();
				m_checkSum = pPacket->GetCheckSum();
				Client_Con pCon = dynamic_pointer_cast<C_NetConnection>((this->shared_from_this()));
				m_netWork._setupConnection(m_id,pCon);
				m_ConnectedHandler(0);
			}
			m_state = State_Connected;
			NET_LOG("½¨Á¢Á¬½ÓÍê³É,[%d] = [%s:%d]",m_id,m_remoteAddress.address().to_string().c_str(),m_remoteAddress.port());
			_appendreceive();
			m_netWork._getPakcetFactory()->FreePacket(pPacket);

		}
		else
		{
			mutable_buffers_1& buffRecive =  m_bufSetup.GetReceiveBuff();
			m_socket.async_read_some(buffRecive
				,boost::bind(&C_NetConnection::_setup_receive_handler,dynamic_pointer_cast<C_NetConnection>(this->shared_from_this()),_1,_2));
		}
	}
NET_CATCH
}

void C_NetConnection::_setup_send_handler( error_code _error,std::size_t transferred )
{
NET_TRY
	if (_error)
	{
		NET_ERROR("½¨Á¢Á¬½ÓµÄÊ±ºòÊ§°ÜÁË,·¢ËÍ½¨Á¢Ð­ÒéÊ§°Ü,´íÎó´úÂë:[%d-%s]",_error.value(),_error.message().c_str());
		//×Ô¶¯ÖØÁ¬
		m_ConnectedHandler(_error.value());

	}
	else
		m_bufSetup.OnSended(transferred);
NET_CATCH
}

void C_NetConnection::Maintain()
{
NET_TRY
	if (m_state == State_Disconnecting)
	{
		if (m_disconnectingTimer.elapsed() > MAX_DISCONNECTING_TIME)
		{
			m_socket.shutdown(socket_base::shutdown_send);
			m_state = State_Stopped;
			NET_ERROR("[%d]¶ÏÏß±£»î³¬Ê±,¶Ï¿ªÁ¬½Ó",m_id);
		}
	}
	if (m_state == State_Connecting)
	{
		if (m_connectingTimer.elapsed() > MAX_CONNECTING_TIME)
		{
			m_socket.shutdown(socket_base::shutdown_send);
			m_state = State_Stopped;
			NET_ERROR("[%d]½¨Á¢Á¬½Ó³¬Ê±,¶Ï¿ªÁ¬½Ó",m_id);

		}
	}
NET_CATCH
}


int C_NetConnection::s_count;




S_NetConnection::S_NetConnection( NetWork& _netWork,NetServer& _netServer,Accepted_Handler& _handler,DisConnected_Handler& _disHandler )
: NetConnection(_netWork,_disHandler)
,m_netServer(_netServer)
,m_AcceptHandler(_handler)
{
	m_id = s_IDGenerator.GenID();
	s_count++;
	m_state = State_None;

}
S_NetConnection::~S_NetConnection()
{
	s_count--;
}


void S_NetConnection::Accept( tcp::acceptor& _listener)
{
NET_TRY
	_listener.async_accept(m_socket
		,boost::bind(&S_NetConnection::_accept_handler,dynamic_pointer_cast<S_NetConnection>(this->shared_from_this()),m_id,_1));
NET_CATCH
}

void S_NetConnection::_accept_handler( ConectionID _id,error_code _error )
{
NET_TRY
	if (_error)
	{
		NET_ERROR("[%d]AcceptÊ§°Ü,´íÎó´úÂë[%d-%s]",m_id,_error.value(),_error.message().c_str());
		m_socket.close();
		m_state = State_Stopped;
	}
	else
	{
		m_state = State_Connecting;
		m_remoteAddress = m_socket.remote_endpoint();

		NET_LOG("[%d]Accpet³É¹¦£¬ÕýÔÚ½¨Á¢Connection[%s]",_id,m_remoteAddress.address().to_string().c_str());
#ifdef ENABLE_INTERNAL_CONNECTION
		SetupConnection();
#else
		m_state = State_Connected;
		m_AcceptHandler(dynamic_pointer_cast<S_NetConnection>(this->shared_from_this()),INVALID_CONNECTIONID);
		_appendreceive();
#endif // ENABLE_INTERNAL_CONNECTION
	}
	m_netServer.NewAccept();
NET_CATCH
}

void S_NetConnection::SetupConnection()
{
NET_TRY
	mutable_buffers_1& buff =  m_bufSetup.GetReceiveBuff();

	m_socket.async_read_some(buff,boost::bind(&S_NetConnection::_setup_receive_handler,dynamic_pointer_cast<S_NetConnection>(this->shared_from_this()),_1,_2));
NET_CATCH
}

void S_NetConnection::_setup_receive_handler( error_code _error,std::size_t transferred )
{
NET_TRY
	if (_error)
	{
		NET_ERROR("[%d]½¨Á¢Á¬½ÓµÄÊ±ºòÊ§°ÜÁË,½ÓÊÕ½¨Á¢Ð­ÒéÊ§°Ü,´íÎó´úÂë:[%d-%s]",m_id,_error.value(),_error.message().c_str());
		m_socket.close();
		m_state = State_Stopped;
	}
	else
	{
		if (m_state != State_Connecting)
		{
			return;
		}

		bool bOK = m_bufSetup.OnReceived(transferred);
		if (!bOK)
		{
			Disconnect();
			return ;
		}
		PacketSetupConnecion* pPacket = dynamic_cast<PacketSetupConnecion*>(m_bufSetup.PopReceivedPacket());
		if (pPacket)
		{
			ConectionID id = pPacket->GetConID();
			bool bReConnect = (id != INVALID_CONNECTIONID);
			if (bReConnect)
			{
				//todo ´¦ÀíÖØÁ¬µÄÇé¿ö
				Server_Con pCon = m_netServer.GetConnection(id);
				if (pCon == NULL || pCon->GetCheckSum() != pPacket->GetCheckSum())
				{
					m_socket.close();
					m_state = State_Stopped;

					NET_ERROR("[%d]¿Í»§¶Ë³¢ÊÔÖØÁ¬Ê§°Ü",m_id);
				}
				else
				{
					int oldID = m_id;
					m_netServer.OnReConnectOK(id,m_id);

					PacketSetupConnecion* pPacket = new PacketSetupConnecion(m_id,m_checkSum);
					m_bufSetup.PushSendingPacket(pPacket);
					mutable_buffers_1& buff = m_bufSetup.GetSendBuff();
					m_socket.async_send(buff
						,boost::bind(&S_NetConnection::_setup_send_handler,dynamic_pointer_cast<S_NetConnection>(this->shared_from_this()),_1,_2));

					m_state = State_Connected;
					_appendreceive();


					m_AcceptHandler(dynamic_pointer_cast<S_NetConnection>(this->shared_from_this()),oldID);
					NET_LOG("½¨Á¢ÖØÁ¬Á¬½ÓÍê³É [%d] = [%s:%d]",m_id,m_remoteAddress.address().to_string().c_str(),m_remoteAddress.port());
				}
			}
			else
			{
				m_checkSum = id << 16 | timeGetTime();

				PacketSetupConnecion* pPacket = new PacketSetupConnecion(m_id,m_checkSum);
				m_bufSetup.PushSendingPacket(pPacket);

				mutable_buffers_1& buff = m_bufSetup.GetSendBuff();
				m_socket.async_send(buff
					,boost::bind(&S_NetConnection::_setup_send_handler,dynamic_pointer_cast<S_NetConnection>(this->shared_from_this()),_1,_2));

				m_state = State_Connected;
				_appendreceive();

				m_AcceptHandler(dynamic_pointer_cast<S_NetConnection>(this->shared_from_this()),INVALID_CONNECTIONID);
				m_remoteAddress = m_socket.remote_endpoint();
				NET_LOG("½¨Á¢Á¬½ÓÍê³É [%d] = [%s:%d]",m_id,m_remoteAddress.address().to_string().c_str(),m_remoteAddress.port());
			}
			m_netWork._getPakcetFactory()->FreePacket(pPacket);

		}
		else
		{
			SetupConnection();
		}
	}
NET_CATCH
}
void S_NetConnection::_setup_send_handler( error_code _error,std::size_t transferred )
{
NET_TRY
	if (_error)
	{
		NET_ERROR("[%d]½¨Á¢Á¬½ÓµÄÊ±ºòÊ§°ÜÁË,·¢ËÍ½¨Á¢Ð­ÒéÊ§°Ü,´íÎó´úÂë:[%d-%s]",m_id,_error.value(),_error.message().c_str());
		m_socket.close();
		m_state = State_Stopped;
	}
	else
	{
		m_bufSetup.OnSended(transferred);
		if (m_state == State_Connected)
		{
			Auto_locker lock(m_CriticalSendOpt);
			_appendsend();
		}
	}
NET_CATCH
}

void S_NetConnection::ResetConnection( Server_Con pNew )
{
NET_TRY
	MY_ASSERT(pNew,"",return;);

	m_remoteAddress = pNew->m_remoteAddress;
	m_state = pNew->m_state;

	std::swap(m_id,pNew->m_id);

	m_bufPacket = pNew->m_bufPacket;
	m_bIsPendingSend = pNew->m_bIsPendingSend;
	m_checkSum = pNew->m_checkSum;
	m_DisConnectdHandler = pNew->m_DisConnectdHandler;
NET_CATCH
}

void S_NetConnection::Maintain()
{
NET_TRY
	if (m_state == State_Disconnecting)
	{
		if (m_disconnectingTimer.elapsed() > MAX_DISCONNECTING_TIME)
		{
			m_state = State_Stopped;
			m_socket.shutdown(socket_base::shutdown_send);
			NET_ERROR("[%d]¶ÏÏß±£»î³¬Ê±,¶Ï¿ªÁ¬½Ó",m_id);
		}
	}
	if (m_state == State_Connecting)
	{
		if (m_connectingTimer.elapsed() > MAX_CONNECTING_TIME)
		{

			m_state = State_Stopped;
			m_socket.shutdown(socket_base::shutdown_send);
			NET_ERROR("[%d]½¨Á¢Á¬½Ó³¬Ê±,¶Ï¿ªÁ¬½Ó",m_id);
		}

	}
NET_CATCH
}

int S_NetConnection::s_count;


