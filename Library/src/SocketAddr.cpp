#include "SocketAddr.h"

namespace ZGF
{

	SocketAddr::SocketAddr(const char* INip, unsigned short INport)
	{
		// ≥ı ºªØµÿ÷∑
		m_sockaddr.sin_family = AF_INET;
		m_sockaddr.sin_addr.s_addr = inet_addr(INip);
		m_sockaddr.sin_port = htons(INport);
	}

	SocketAddr::SocketAddr(const sockaddr_in &INsockaddr_in)
	{
		m_sockaddr = INsockaddr_in;
	}

	SocketAddr::SocketAddr(const SocketAddr &INinstance)
	{
		m_sockaddr = INinstance.m_sockaddr;
	}

	SocketAddr::~SocketAddr()
	{
		// 
	}

	SocketAddr& SocketAddr::operator =(const SocketAddr &INinstance)
	{
		m_sockaddr = INinstance.m_sockaddr;
		return *this;
	}

	SocketAddr& SocketAddr::operator = (const sockaddr_in& INaddrData)
	{
		m_sockaddr = INaddrData;
		return *this;
	}

	string SocketAddr::GetIP()
	{
		char* pStr = inet_ntoa(m_sockaddr.sin_addr);
		if (pStr == NULL)
		{
			return "";
		}
		return string(pStr);
	}

	unsigned short SocketAddr::GetNetPort()
	{
		return m_sockaddr.sin_port;
	}

	unsigned short SocketAddr::GetHostPort()
	{
		return ntohs(m_sockaddr.sin_port);
	}

	sockaddr SocketAddr::GetSockaddr()
	{
		sockaddr* addr = (sockaddr *)&m_sockaddr;
		return *addr;
	}
}
