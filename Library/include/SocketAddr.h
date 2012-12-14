#ifndef LIBRARY_TCPSOCKET_SOCKETADDR_H
#define LIBRARY_TCPSOCKET_SOCKETADDR_H

#include "SocketComDef.h"

#include <string>
using std::string;

namespace ZGF
{
	struct AddrData;

	class SocketAddr
	{
	private:
		sockaddr_in m_sockaddr;
	public:
		SocketAddr(const char* INip, unsigned short INport);

		SocketAddr(const sockaddr_in& INaddrData);

		SocketAddr(const SocketAddr& INinstance);

		~SocketAddr();

	public:
		SocketAddr& operator = (const SocketAddr& INinstance);

		SocketAddr& operator = (const sockaddr_in& INaddrDatae);

		string GetIP();

		unsigned short GetNetPort();

		unsigned short GetHostPort();

		sockaddr GetSockaddr();

	};
}

#endif