#ifndef LIBRARY_TCPSOCKET_WINSOCKEXFUNCTION_H
#define LIBRARY_TCPSOCKET_WINSOCKEXFUNCTION_H

#include "BaseType.h"
#include "SocketComDef.h"
#include "Singleton.h"

namespace ZGF
{
	class WinSockExFunction : public Singleton<WinSockExFunction>
	{
		friend class Singleton<WinSockExFunction>;
	private:
		LPFN_ACCEPTEX m_pfnAcceptEx;
		LPFN_CONNECTEX m_pfnConnectEx;
		LPFN_DISCONNECTEX m_pfnDisconnectEx;
		LPFN_GETACCEPTEXSOCKADDRS m_pfnGetAcceptExSockaddrs;
		LPFN_TRANSMITFILE m_pfnTransmitfile;
		LPFN_TRANSMITPACKETS m_pfnTransmitPackets;
		LPFN_WSARECVMSG m_pfnWSARecvMsg;

	public:
		inline BOOL AcceptEx (
			SOCKET sListenSocket,
			SOCKET sAcceptSocket,
			PVOID lpOutputBuffer,
			DWORD dwReceiveDataLength,
			DWORD dwLocalAddressLength,
			DWORD dwRemoteAddressLength,
			LPDWORD lpdwBytesReceived,
			LPOVERLAPPED lpOverlapped)
		{
			MyASSERT(NULL != m_pfnAcceptEx);
			return m_pfnAcceptEx(sListenSocket,
				sAcceptSocket,lpOutputBuffer,
				dwReceiveDataLength,dwLocalAddressLength,
				dwRemoteAddressLength,lpdwBytesReceived,
				lpOverlapped);
		}

		inline BOOL ConnectEx(
			SOCKET s,const struct sockaddr FAR *name,
			int namelen,PVOID lpSendBuffer,
			DWORD dwSendDataLength,LPDWORD lpdwBytesSent,
			LPOVERLAPPED lpOverlapped)
		{
			MyASSERT(NULL != m_pfnConnectEx);
			return m_pfnConnectEx(
				s,name,namelen,lpSendBuffer,
				dwSendDataLength,lpdwBytesSent,
				lpOverlapped);
		}
		inline BOOL DisconnectEx(
			SOCKET s,LPOVERLAPPED lpOverlapped,
			DWORD  dwFlags,DWORD  dwReserved)
		{
			MyASSERT(NULL != m_pfnDisconnectEx);
			return m_pfnDisconnectEx(s,
				lpOverlapped,dwFlags,dwReserved);
		}

		inline VOID GetAcceptExSockaddrs (
			PVOID lpOutputBuffer,
			DWORD dwReceiveDataLength,
			DWORD dwLocalAddressLength,
			DWORD dwRemoteAddressLength,
			sockaddr **LocalSockaddr,
			LPINT LocalSockaddrLength,
			sockaddr **RemoteSockaddr,
			LPINT RemoteSockaddrLength)
		{
			MyASSERT(NULL != m_pfnGetAcceptExSockaddrs);
			return m_pfnGetAcceptExSockaddrs(
				lpOutputBuffer,dwReceiveDataLength,
				dwLocalAddressLength,dwRemoteAddressLength,
				LocalSockaddr,LocalSockaddrLength,
				RemoteSockaddr,RemoteSockaddrLength);
		}

		inline BOOL TransmitFile(
			SOCKET hSocket,HANDLE hFile,
			DWORD nNumberOfBytesToWrite,
			DWORD nNumberOfBytesPerSend,
			LPOVERLAPPED lpOverlapped,
			LPTRANSMIT_FILE_BUFFERS lpTransmitBuffers,
			DWORD dwReserved)
		{
			MyASSERT(NULL != m_pfnTransmitfile);
			return m_pfnTransmitfile(
				hSocket,hFile,nNumberOfBytesToWrite,
				nNumberOfBytesPerSend,lpOverlapped,
				lpTransmitBuffers,dwReserved);
		}

		inline BOOL TransmitPackets(
			SOCKET hSocket,                             
			LPTRANSMIT_PACKETS_ELEMENT lpPacketArray,                               
			DWORD nElementCount,DWORD nSendSize,                
			LPOVERLAPPED lpOverlapped,DWORD dwFlags)
		{
			MyASSERT(NULL != m_pfnTransmitPackets);
			return m_pfnTransmitPackets(hSocket, lpPacketArray, nElementCount, nSendSize, lpOverlapped,dwFlags);
		}

		inline INT WSARecvMsg(
			SOCKET s,LPWSAMSG lpMsg, 
			LPDWORD lpdwNumberOfBytesRecvd, 
			LPWSAOVERLAPPED lpOverlapped, 
			LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
		{
			MyASSERT(NULL != m_pfnWSARecvMsg);
			return m_pfnWSARecvMsg(
				s,lpMsg,lpdwNumberOfBytesRecvd, 
				lpOverlapped,lpCompletionRoutine);
		}
	public:
		static bool LoadWinSockExFunction(SOCKET& skTemp,GUID&funGuid,void*&pFun)
		{
			DWORD dwBytes = 0;
			Int32 bRet = TRUE;
			pFun = NULL;
			Int32 bCreateSocket = FALSE;
			try
			{
				if(INVALID_SOCKET == skTemp)
				{
					skTemp = ::WSASocket(AF_INET,SOCK_STREAM, 
						IPPROTO_TCP,NULL,0,WSA_FLAG_OVERLAPPED);
					bCreateSocket = (skTemp != INVALID_SOCKET);
				}
				if(INVALID_SOCKET == skTemp)
				{
					throw ((DWORD)WSAGetLastError());
				}
				if(SOCKET_ERROR == ::WSAIoctl(skTemp,
					SIO_GET_EXTENSION_FUNCTION_POINTER, 
					&funGuid,sizeof(funGuid),
					&pFun,sizeof(pFun),&dwBytes,NULL,
					NULL))
				{
					pFun = NULL;
					throw ((DWORD)WSAGetLastError());
				}
			}
			catch(...)
			{
				if(bCreateSocket)
				{
					::closesocket(skTemp);
				}
			}
			return NULL != pFun;
		}
	private:
		WinSockExFunction()
		{
			SOCKET sockTemp = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, NULL, WSA_FLAG_OVERLAPPED);
			LoadAllFun(sockTemp);
			closesocket(sockTemp);
		}
	private:
		BOOL LoadAllFun(SOCKET skTemp)
		{//注意这个地方的调用顺序，是根据服务器的需要，并结合了表达式副作用
			//而特意安排的调用顺序
			return (LoadAcceptExFun(skTemp) &&
				LoadGetAcceptExSockaddrsFun(skTemp) &&
				LoadTransmitFileFun(skTemp) &&
				LoadTransmitPacketsFun(skTemp) &&
				LoadDisconnectExFun(skTemp) &&
				LoadConnectExFun(skTemp) && 
				LoadWSARecvMsgFun(skTemp));
		}
	private:
		BOOL LoadAcceptExFun(SOCKET &skTemp)
		{
			GUID GuidAcceptEx = WSAID_ACCEPTEX;
			return LoadWinSockExFunction(skTemp,GuidAcceptEx,(void*&)m_pfnAcceptEx);
		}

		BOOL LoadConnectExFun(SOCKET &skTemp)
		{
			GUID GuidAcceptEx = WSAID_CONNECTEX;
			return LoadWinSockExFunction(skTemp,GuidAcceptEx,(void*&)m_pfnConnectEx);
		}

		BOOL LoadDisconnectExFun(SOCKET&skTemp)
		{
			GUID GuidDisconnectEx = WSAID_DISCONNECTEX;
			return LoadWinSockExFunction(skTemp,GuidDisconnectEx,(void*&)m_pfnDisconnectEx);
		}

		BOOL LoadGetAcceptExSockaddrsFun(SOCKET &skTemp)
		{
			GUID GuidGetAcceptExSockaddrs = WSAID_GETACCEPTEXSOCKADDRS;
			return LoadWinSockExFunction(skTemp, GuidGetAcceptExSockaddrs, (void*&)m_pfnGetAcceptExSockaddrs);
		}

		BOOL LoadTransmitFileFun(SOCKET&skTemp)
		{
			GUID GuidTransmitFile = WSAID_TRANSMITFILE;
			return LoadWinSockExFunction(skTemp,GuidTransmitFile,(void*&)m_pfnTransmitfile);
		}

		BOOL LoadTransmitPacketsFun(SOCKET&skTemp)
		{
			GUID GuidTransmitPackets = WSAID_TRANSMITPACKETS;
			return LoadWinSockExFunction(skTemp,GuidTransmitPackets,(void*&)m_pfnTransmitPackets);
		}

		BOOL LoadWSARecvMsgFun(SOCKET&skTemp)
		{
			GUID GuidTransmitPackets = WSAID_TRANSMITPACKETS;
			return LoadWinSockExFunction(skTemp,GuidTransmitPackets,(void*&)m_pfnWSARecvMsg);
		}
	};
}



#endif