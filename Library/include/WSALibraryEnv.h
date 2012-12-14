#ifndef LIBRARY_TCPSOCKET_WSALIBRARYENV_H
#define LIBRARY_TCPSOCKET_WSALIBRARYENV_H

#include "SocketComDef.h"
#include "Singleton.h"
#include "BaseType.h"

namespace ZGF
{
	class WSALibraryEnv : public Singleton<WSALibraryEnv>
	{
		friend class Singleton<WSALibraryEnv>;
	private:
		WSADATA m_wsaData;
		Int32 m_errorCode;

	public:
		Int32 GetErrorCode()
		{
			return m_errorCode;
		}
	private:
		WSALibraryEnv()
		{
			ZeroMemory(&m_wsaData, sizeof(m_wsaData));
			m_errorCode = WSAStartup(MAKEWORD(2,0), &m_wsaData);
		}

		~WSALibraryEnv()
		{
			WSACleanup();
		}

	};
}


#endif