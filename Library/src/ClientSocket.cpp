#include "ClientSocket.h"
#include "SocketAddr.h"
#include "ObjectPool.h"
#include "Overlapped.h"
#include "PacketEngine.h"
#include "QueueService.h"
#include "WinSockExFunction.h"
#include "Log.h"
#include <assert.h>

string policy = "<policy-file-request/>";
string policyReturn = "<?xml version=\'1.0\'?><cross-domain-policy><allow-access-from domain=\'*\' to-ports=\'*\'/></cross-domain-policy>";

namespace ZGF
{
	ClientSocket::ClientSocket()
	{
		//
		m_state = EClientSocketState_Common,
		m_socket = INVALID_SOCKET;
		m_listenSocket = INVALID_SOCKET;
		m_completePort = INVALID_HANDLE_VALUE;
		m_clientID = 0;
		m_connectTime = 0;
		m_sendCount = 0;
		m_recvCount = 0;
		m_maxRecvBufferSize = 0;
		m_reusedCount = 0;
		m_completeConnect = false;
		m_associateflage = false;
		m_localAddr = NULL;
		m_remoteAddr = NULL;
		m_recvBuffer = NULL;
		m_recvBufferSize = 0;
		m_overlappedBufferMgr = NULL;
		m_msgNodeBufferMgr = NULL;
		m_pQueueService = NULL;
		m_sendingList.clear();
	}

	ClientSocket::~ClientSocket()
	{
		Clear();
	}

	string ClientSocket::GetClientIP()
	{
		if(m_remoteAddr)
		{
			return m_remoteAddr->GetIP();
		}
		return "";
	}

	UInt32 ClientSocket::GetConnectTime()
	{
		Int32 secs;
		Int32 bytes = sizeof(secs);
		Int32 errorCode = getsockopt(m_socket, SOL_SOCKET, SO_CONNECT_TIME, (char *)&secs, (Int32*)&bytes);
		if(errorCode == SOCKET_ERROR) 
		{
			return -1;
		}
		return secs;
	}

	void ClientSocket::SetCompletePort(HANDLE INcompletePort)
	{
		MyASSERT(INcompletePort != INVALID_HANDLE_VALUE);
		m_completePort = INcompletePort;
	}

	void ClientSocket::SetListenSocket(SOCKET INlistenSocket)
	{
		MyASSERT(INlistenSocket != INVALID_SOCKET);
		m_listenSocket = INlistenSocket;
	}

	void ClientSocket::SetOverlappedBufferMgr(OverlappedBufferMgr* INbufferMgr)
	{
		MyASSERT(INbufferMgr != NULL);
		m_overlappedBufferMgr = INbufferMgr;
	}

	void ClientSocket::SetMsgNodeBufferMgr(MsgNodeBufferMgr* INmsgNodeBufferMgr)
	{
		MyASSERT(INmsgNodeBufferMgr != NULL);
		m_msgNodeBufferMgr = INmsgNodeBufferMgr;
	}

	void ClientSocket::SetQueueService(QueueService* INpQueueService)
	{
		MyASSERT(INpQueueService != NULL);
		m_pQueueService = INpQueueService;
	}

	bool ClientSocket::Initial()
	{
		try
		{
			// 创建接收缓存区
			if(m_recvBuffer == NULL)
			{
				m_recvBuffer = new char[EMaxRecvBufferSize];
			}

			ZeroMemory(m_recvBuffer, EMaxRecvBufferSize);
			
			// 创建套接字
			m_socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, NULL, WSA_FLAG_OVERLAPPED);
			if(m_socket == INVALID_SOCKET)
			{
				return false;
			}

			if(m_localAddr == NULL)
			{
				m_localAddr = new SocketAddr("", 0);
			}
			if(m_remoteAddr == NULL)
			{
				m_remoteAddr = new SocketAddr("", 0);
			}
		}
		catch(...)
		{
			Log::Instance()->WriteException("%s, %d, Initial ClientSocket exception",
				__FUNCTION__, __LINE__);
			return false;
		}


		ULong ret;
		// 设置保持连接检测
		tcp_keepalive alive;
		alive.onoff = 1;
		alive.keepalivetime  = 5000;
		alive.keepaliveinterval = 5000;
		WSAIoctl(m_socket, SIO_KEEPALIVE_VALS, &alive, sizeof(alive), NULL, 0, &ret, NULL, NULL);

		// 设置地址重用
		Int32 val = 1;
		if(setsockopt(m_socket,SOL_SOCKET,SO_REUSEADDR,(const char *)&val,sizeof(Int32)) == SOCKET_ERROR)
		{
			UInt32 errorCode = WSAGetLastError();
			Log::Instance()->WriteError("%s, %d, CreateIoCompletionPort Failed! Error Code is : %d",
				__FUNCTION__, __LINE__, errorCode);
			return false;
		}
		// 设置延迟发送
		val = 1;
		if(setsockopt(m_socket,IPPROTO_TCP,TCP_NODELAY,(const char *)&val,sizeof(Int32)) == SOCKET_ERROR)
		{
			UInt32 errorCode = WSAGetLastError();
			Log::Instance()->WriteError("%s, %d, CreateIoCompletionPort Failed! Error Code is : %d",
				__FUNCTION__, __LINE__, errorCode);
			return false;
		}

		// 设置发送缓存大小

		// 设置接收缓存大小

		m_state = EClientSocketState_Common;

		return true;
	}

	void ClientSocket::Disconnect()
	{
		// 等待未决数据发送
		
	}

	void ClientSocket::CloseSocket()
	{
		Disconnect();
		// 关闭收发送
		if(m_socket != INVALID_SOCKET)
		{
			shutdown(m_socket, SD_BOTH);
			closesocket(m_socket);
			m_socket = INVALID_SOCKET;
		}
	}

	void ClientSocket::ResetSocket(OverLappedBuffer* INpBuffer)
	{
		Guard<CriticalSection> monitor(&m_ioLock);
		if(INpBuffer != NULL)
		{
			if(m_overlappedBufferMgr != NULL)
			{
				m_overlappedBufferMgr->FreeObject(INpBuffer);
			}
		}
		if(m_state == EClientSocketState_Close)
		{
			NOTE_LOG("链接已关闭，无需重置");
			return;
		}
		// 由于CancelIO只对本线程投递的未决IO有作用，而又要重用套接字所以不能用shutdown
		//shutdown(m_socket, SD_BOTH);
		//CloseSocket();
		if(!WinSockExFunction::Instance()->DisconnectEx(m_socket, NULL, TF_REUSE_SOCKET, 0))
		{
			int errorCode = WSAGetLastError();
			Log::Instance()->WriteError("%s, %d, DisconnectEx Failed! The error code is : %d",
				__FUNCTION__, __LINE__, errorCode);
		}

		NOTE_LOG("断开连接， 投递断开消息");

		MsgNode* pMsgNode = m_msgNodeBufferMgr->GetNewObject();
		pMsgNode->ObjectPort = m_localAddr->GetHostPort();
		pMsgNode->clientID = m_clientID;
		pMsgNode->msgType = 0;
		pMsgNode->msgLength = 0;
		pMsgNode->msgContent = "";

		m_pQueueService->AddToQueue(pMsgNode);

		// 清理未决发送
		ClearSendingList();
		
		// 清理接收缓存
		ZeroMemory(m_recvBuffer, EMaxRecvBufferSize);
		m_recvBufferSize = 0;

		m_listenSocket = INVALID_SOCKET;
		m_completePort = INVALID_HANDLE_VALUE;
		//m_overlappedBufferMgr = NULL;
		m_msgNodeBufferMgr = NULL;
		m_pQueueService = NULL;
		m_connectTime = 0;
		m_sendCount = 0;
		m_recvCount = 0;
		m_maxRecvBufferSize = 0;
		m_completeConnect = false;

		sockaddr_in addr;
		addr.sin_addr.s_addr = inet_addr("255.255.255.255");
		addr.sin_port = htons(0);
		*m_localAddr = addr;
		*m_remoteAddr = addr;

		m_state = EClientSocketState_Close;
	}

	void ClientSocket::Clear()
	{
		CloseSocket();

		delete[] m_recvBuffer;
		m_recvBuffer = NULL;
		delete m_localAddr;
		m_localAddr = NULL;
		delete m_remoteAddr;
		m_remoteAddr = NULL;
	}

	void ClientSocket::ClearSendingList()
	{
		// 清理列表
		while(m_sendingList.size())
		{
			OverLappedBuffer* pBuffer = m_sendingList.front();
			m_sendingList.pop_front();
			m_overlappedBufferMgr->FreeObject(pBuffer);
		}		
	}

	bool ClientSocket::PostAccept(OverLappedBuffer* INpBuffer)
	{
		if(m_socket == INVALID_SOCKET || m_completePort == INVALID_HANDLE_VALUE || m_listenSocket == INVALID_SOCKET || 
			m_overlappedBufferMgr == NULL || m_msgNodeBufferMgr == NULL || m_pQueueService == NULL)
		{
			Log::Instance()->WriteError("%s, %d, Check Initial Set!",
				__FUNCTION__, __LINE__);
			return false;
		}

		if(!m_associateflage)
		{
			// 关联完成端口
			if(!CreateIoCompletionPort((HANDLE)m_socket, m_completePort, (ULONG_PTR)this, 0))
			{
				// 
				UInt32 errorCode = WSAGetLastError();
				Log::Instance()->WriteError("%s, %d, CreateIoCompletePort Failed! The Error Code is : %d",
					__FUNCTION__, __LINE__, errorCode);
				return false;
			}
			m_associateflage = true;
		}

		// 清理发送投递列表
		ClearSendingList();

		assert(m_sendingList.size() == 0);

		OverLappedBuffer* pBuffer = INpBuffer;//m_overlappedBufferMgr->GetNewObject();
		assert(pBuffer != NULL);
		
		//pBuffer->wsaBuff.len = EOverlappedBufferSize -1;
		pBuffer->type = EOverLappedType_Accpet;
		pBuffer->clientID = m_clientID;
		// 投递接收
		if (!AcceptEx(m_listenSocket,
			m_socket,
			pBuffer->wsaBuff.buf,
			0/*EMaxRecvBufferSize - (sizeof(sockaddr_in) + 16) * 2 - 1*/,
			sizeof(sockaddr_in) + 16,
			sizeof(sockaddr_in) + 16,
			NULL,// 异步方式下该参数无用
			&pBuffer->wsaOverLapped))
		{
			UInt32 errorCode = WSAGetLastError();
			if (errorCode != ERROR_IO_PENDING)
			{
				Log::Instance()->WriteError("%s, %d, Post AcceptEx Failed! The error code is : %d",
					__FUNCTION__, __LINE__, errorCode);
				// 重置套接字
				pBuffer->type = EOverLappedType_Error;
				PostQueuedCompletionStatus(m_completePort, 0, (ULONG_PTR)this, &pBuffer->wsaOverLapped);
				// 
				Log::Instance()->WriteNote("%s, %d, Post Reset ClientSocket",
					__FUNCTION__, __LINE__);
				return false;
			}
		}

		return true;
	}

	bool ClientSocket::PostSend(OverLappedBuffer* INpBuffer)
	{
		//INpBuffer->type = EOverLappedType_Send;
		//INpBuffer->wsaBuff.len = EOverlappedBufferSize - 1;
		ULong sendSize = 0;
		if(WSASend(m_socket, &INpBuffer->wsaBuff, 1, &sendSize, 0, &INpBuffer->wsaOverLapped, NULL) == SOCKET_ERROR)
		{
			UInt32 errorCode = WSAGetLastError();
			if(WSA_IO_PENDING != errorCode)
			{
				Log::Instance()->WriteError("%s, %d, WSASend Failed! The error code is : %d",
					__FUNCTION__, __LINE__, errorCode);
				// 发生严重错误
				// 重置连接
				INpBuffer->type = EOverLappedType_Error;
				PostQueuedCompletionStatus(m_completePort, 0, (ULONG_PTR)this, &INpBuffer->wsaOverLapped);
				Log::Instance()->WriteNote("%s, %d, Post Reset ClientSocket",
					__FUNCTION__, __LINE__);
			}
			else
			{
				// 投递成功，发送操作正在执行中
			}
		}
		return true;
	}

	bool ClientSocket::PostRecv(OverLappedBuffer* INpBuffer)
	{
		ULong flage = 0;
		ULong recvSize = 0;
		INpBuffer->type = EOverLappedType_Recv;
		INpBuffer->wsaBuff.len = 2*EOverlappedBufferSize - sizeof(OverLappedBuffer);
		if(WSARecv(m_socket, &INpBuffer->wsaBuff, 1, &recvSize, &flage, &INpBuffer->wsaOverLapped, NULL) == SOCKET_ERROR)
		{
			UInt32 errorCode = WSAGetLastError();
			if(WSA_IO_PENDING != errorCode)
			{
				Log::Instance()->WriteError("%s, %d, WSARecv Failed! The error code is : %d",
					__FUNCTION__, __LINE__, errorCode);
				// 发生严重错误
				// 重置连接
				INpBuffer->type = EOverLappedType_Error;
				PostQueuedCompletionStatus(m_completePort, 0, (ULONG_PTR)this, &INpBuffer->wsaOverLapped);
				Log::Instance()->WriteNote("%s, %d, Post Reset ClientSocket",
					__FUNCTION__, __LINE__);
			}
			else
			{
				// 投递成功，接收操作正在执行中
				
			}
		}
		return true;
	}

	bool ClientSocket::PostDisconnect(OverLappedBuffer* INpBuffer)
	{
		INpBuffer->type = EOverLappedType_Disconnect;
		PostQueuedCompletionStatus(m_completePort, 0, (ULONG_PTR)this, &INpBuffer->wsaOverLapped);
		Log::Instance()->WriteNote("%s, %d, Post Disconnect ClientSocket",
			__FUNCTION__, __LINE__);
		return true;
	}

	bool ClientSocket::OnAcceptComplete(OverLappedBuffer* INpBuffer, UInt32 INbufferSize)
	{
		Guard<CriticalSection> monitor(&m_ioLock);
		// 获取去客户端连接地址
		// 更新状态
		setsockopt(m_socket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, (char *)&m_listenSocket, sizeof(m_listenSocket));

		int locallen, remotelen;
		sockaddr_in *plocal = 0, *premote = 0;
		GetAcceptExSockaddrs(INpBuffer->wsaBuff.buf,
			0/*EMaxRecvBufferSize -(sizeof(sockaddr_in) + 16) * 2 - 1*/,
			sizeof(sockaddr_in) + 16,
			sizeof(sockaddr_in) + 16,
			(sockaddr **)&plocal,
			&locallen,
			(sockaddr **)&premote,
			&remotelen);

		*m_localAddr = *plocal;
		*m_remoteAddr = *premote;
		
		// 关联完成端口
		//if(!CreateIoCompletionPort((HANDLE)m_socket, m_completePort, (ULONG_PTR)this, 0))
		//{
		//	// 
		//	UInt32 errorCode = WSAGetLastError();
		//	Log::Instance()->WriteError("%s, %d, Associate Complete Port Failed! The error code is : %d",
		//		__FUNCTION__, __LINE__, errorCode);
		//	return false;
		//}

		m_completeConnect = true;

		static UInt32 connectionCounter = 0;
		++connectionCounter;
		Log::Instance()->WriteNote("%s, %d, 建立连接, 累计连接数 : %d",
			__FUNCTION__, __LINE__, connectionCounter);

		// 完成数据包处理
		ParseData(m_recvBuffer, &m_recvBufferSize, INpBuffer, INbufferSize);

		// 投递接收
		PostRecv(INpBuffer);
		return true;
	}

	bool ClientSocket::OnSendComplete(OverLappedBuffer* INpBuffer, UInt32 INbufferSize)
	{
		Guard<CriticalSection> monitor(&m_ioLock);
		++m_sendCount;
		// 从发送列表中移除
		m_overlappedBufferMgr->FreeObject(INpBuffer);
		return true;
	}

	bool ClientSocket::OnRecvComplete(OverLappedBuffer* INpBuffer, UInt32 INbufferSize)
	{
		//Log::Instance()->WriteDebug("%s, %d, Recv Complete!", 
		//	__FUNCTION__, __LINE__);
		//Log::Instance()->WriteDebug(INpBuffer->buf);
		Guard<CriticalSection> iomonitor(&m_ioLock);
		//Guard<CriticalSection> monitor(&m_recvLock);
		++m_recvCount;
		// 消息包内容解析
		ParseData(m_recvBuffer, &m_recvBufferSize, INpBuffer, INbufferSize);
		
		// 投递接收
		PostRecv(INpBuffer);
		return true;
	}

	bool ClientSocket::ParseData(char* IOrecvBuffer, UInt32* IOrecvBufferSize, OverLappedBuffer* INpolBuffer, UInt32 INolBufferSize)
	{
		Int32 pos = -1;
		char* pStartPos = INpolBuffer->wsaBuff.buf;
		UInt32 curolBufferSize = INolBufferSize;

		// 测试所用
		//char tempbuf[EMaxRecvBufferSize] = "\0";
		//memcpy(tempbuf, pStartPos, INolBufferSize);

		// 策略文件处理
		if(policy.compare(pStartPos) == 0)
		{
			ZeroMemory(INpolBuffer->wsaBuff.buf, EOverlappedBufferSize);
			INpolBuffer->type = EOverLappedType_Send;
			memcpy(INpolBuffer->wsaBuff.buf, policyReturn.c_str(), policyReturn.size());
			INpolBuffer->wsaBuff.len = policyReturn.size();
			ULONG param = 0;

			if(send(m_socket, INpolBuffer->wsaBuff.buf, INpolBuffer->wsaBuff.len, 0))
			{
				UInt32 errorCode = WSAGetLastError();
				Log::Instance()->WriteError("%s, %d, send policyReturn failed! The error code is %d",
					__FUNCTION__, __LINE__, errorCode);
			}

			return true;
		}

		static UInt32 receivePacketCounter = 0;
		++receivePacketCounter;

		NOTE_LOG("处理第 %d 个网络数据", 
			receivePacketCounter);

		// 不完整的缓存包处理
		if(*IOrecvBufferSize > 0)
		{
			DEBUG_LOG("处理不完整包");
			if(*IOrecvBufferSize < sizeof(UInt32))
			{
				if((curolBufferSize >= sizeof(UInt32)) || 
					((*IOrecvBufferSize + curolBufferSize) >= sizeof(UInt32)))
				{
					memcpy(IOrecvBuffer + *IOrecvBufferSize, pStartPos, sizeof(UInt32) - *IOrecvBufferSize);
					pStartPos += sizeof(UInt32) - *IOrecvBufferSize;
					curolBufferSize -= sizeof(UInt32) - *IOrecvBufferSize;
					*IOrecvBufferSize = sizeof(UInt32);
				}
				else
				{
					memcpy(IOrecvBuffer + *IOrecvBufferSize, pStartPos, curolBufferSize);
					pStartPos += curolBufferSize;
					*IOrecvBufferSize += curolBufferSize;
					curolBufferSize = 0;

					DEBUG_LOG("包头不完整，返回");
					return true;
				}
			}

			// 读取大小
			//if(*IOrecvBufferSize >= sizeof(UInt32))
			{
				// 整个包大小, 等于sizeof(UInt32) + sizeof(UInt16) + 包体内容
				UInt32 packetSize = *(UInt32*)&IOrecvBuffer[0];

				DEBUG_LOG("消息包大小: %d",
					packetSize);
				if(packetSize > EMaxRecvBufferSize || packetSize < (sizeof(UInt32) + sizeof(UInt16)))
				{
					// 清空缓存
					ZeroMemory(IOrecvBuffer, EMaxRecvBufferSize);
					*IOrecvBufferSize = 0;

					// 断开连接
					INpolBuffer->type = EOverLappedType_Error;
					PostQueuedCompletionStatus(m_completePort, 0, (ULONG_PTR)this, &INpolBuffer->wsaOverLapped);
					Log::Instance()->WriteNote("%s, %d, Post Reset ClientSocket",
						__FUNCTION__, __LINE__);

					ERROR_LOG("非法消息，消息报大小为: %d 返回",
						packetSize);
					return false;
				}

				if(packetSize > *IOrecvBufferSize + curolBufferSize)
				{
					// 将不完整的数据包先缓存着
					memcpy(IOrecvBuffer + *IOrecvBufferSize, pStartPos, curolBufferSize);

					DEBUG_LOG("包体不完整，缓存，返回");
					return true;
				}
				else
				{
					// 拼接完整包
					memcpy(IOrecvBuffer + *IOrecvBufferSize, pStartPos, packetSize - *IOrecvBufferSize);
					pStartPos += packetSize - *IOrecvBufferSize;
					curolBufferSize -= packetSize - *IOrecvBufferSize;

					// 完整包处理
					MsgNode* pMsgNode = m_msgNodeBufferMgr->GetNewObject();
					pMsgNode->ObjectPort = m_localAddr->GetHostPort();
					pMsgNode->clientID = m_clientID;
					pMsgNode->msgType = *(UInt16*)&IOrecvBuffer[sizeof(UInt32)];
					pMsgNode->msgLength = packetSize - sizeof(UInt32) - sizeof(UInt16);
					pMsgNode->msgContent = string(IOrecvBuffer + sizeof(UInt32) + sizeof(UInt16), packetSize - sizeof(UInt32) - sizeof(UInt16));

					m_pQueueService->AddToQueue(pMsgNode);

					// 清空缓存
					ZeroMemory(IOrecvBuffer, EMaxRecvBufferSize);
					*IOrecvBufferSize = 0;
				}
			}
		}

		while(curolBufferSize > 0)
		{
			MyASSERT(*IOrecvBufferSize == 0);
			if(curolBufferSize >= sizeof(UInt32))
			{
				UInt32 packetSize = *(UInt32*)(&pStartPos[0]);

				DEBUG_LOG("消息包大小: %d",
					packetSize);
				if(packetSize > EMaxRecvBufferSize || packetSize < (sizeof(UInt32) + sizeof(UInt16)))
				{
					// 断开连接
					INpolBuffer->type = EOverLappedType_Error;
					PostQueuedCompletionStatus(m_completePort, 0, (ULONG_PTR)this, &INpolBuffer->wsaOverLapped);
					Log::Instance()->WriteNote("%s, %d, Post Reset ClientSocket",
						__FUNCTION__, __LINE__);

					ERROR_LOG("非法消息，消息报大小为: %d 返回",
						packetSize);
					return false;
				}

				if(packetSize > curolBufferSize)
				{
					// 将不完整的数据包先缓存着
					memcpy(IOrecvBuffer, pStartPos, curolBufferSize);
					*IOrecvBufferSize = curolBufferSize;

					DEBUG_LOG("包体不完整，缓存，返回");
					return true;
				}
				else
				{
					// 完整包处理
					MsgNode* pMsgNode = m_msgNodeBufferMgr->GetNewObject();
					pMsgNode->ObjectPort = m_localAddr->GetHostPort();
					pMsgNode->clientID = m_clientID;
					pMsgNode->msgType = *(UInt16*)(&pStartPos[sizeof(UInt32)]);
					pMsgNode->msgLength = packetSize - sizeof(UInt32) - sizeof(UInt16);
					pMsgNode->msgContent = string(pStartPos + sizeof(UInt32) + sizeof(UInt16), packetSize - sizeof(UInt32) - sizeof(UInt16));

					m_pQueueService->AddToQueue(pMsgNode);

					pStartPos += packetSize;
					curolBufferSize -= packetSize;
				}
			}
			else
			{
				memcpy(IOrecvBuffer + *IOrecvBufferSize, pStartPos, curolBufferSize);
				*IOrecvBufferSize += curolBufferSize;
				pStartPos += curolBufferSize;
				curolBufferSize = 0;

				DEBUG_LOG("包头不完整，返回");
				return true;
			}
		}
		return true;

		//Int32 pos = -1;
		//char* pStartPos = INpolBuffer->wsaBuff.buf;
		//UInt32 curolBufferSize = INolBufferSize;

		//if(policy.compare(pStartPos) == 0)
		//{
		//	ZeroMemory(INpolBuffer->wsaBuff.buf, EOverlappedBufferSize);
		//	INpolBuffer->type = EOverLappedType_Send;
		//	memcpy(INpolBuffer->wsaBuff.buf, policyReturn.c_str(), policyReturn.size());
		//	INpolBuffer->wsaBuff.len = policyReturn.size();
		//	ULONG param = 0;
		//	if(send(m_socket, INpolBuffer->wsaBuff.buf, INpolBuffer->wsaBuff.len, 0))
		//	{
		//		UInt32 errorCode = WSAGetLastError();
		//		Log::Instance()->WriteError("%s, %d, send policyReturn failed! The error code is %d",
		//			__FUNCTION__, __LINE__, errorCode);
		//	}
		//	return true;
		//}
		//// 先处理缓存数据
		//if(*IOrecvBufferSize > 0)
		//{
		//	// 从新接收数据中查找数据块尾部标识		
		//	Int32 endPosIndex = PacketEngine::GetEndTagPos(pStartPos, curolBufferSize, ']');

		//	if(endPosIndex == -1)
		//	{
		//		if(*IOrecvBufferSize + INolBufferSize > EMaxRecvBufferSize)
		//		{
		//			Log::Instance()->WriteNote("%s, %d, Clear Buffer",
		//				__FUNCTION__, __LINE__);
		//			// 丢弃所有缓存数据
		//			ZeroMemory(IOrecvBuffer, EMaxRecvBufferSize);
		//			*IOrecvBufferSize = 0;
		//		}
		//		else
		//		{
		//			MyASSERT(INolBufferSize >= 0);
		//			// 将数据都拷贝到缓存中
		//			memcpy(IOrecvBuffer + *IOrecvBufferSize, pStartPos, INolBufferSize);
		//			*IOrecvBufferSize += INolBufferSize;
		//		}
		//		return true;
		//	}
		//	else
		//	{
		//		MyASSERT(endPosIndex >= 0);
		//		MyASSERT(endPosIndex < curolBufferSize);
		//		// 将数据都拷贝到缓存中
		//		memcpy(IOrecvBuffer + *IOrecvBufferSize, pStartPos, endPosIndex + 1);
		//		*IOrecvBufferSize += endPosIndex + 1;
		//		pStartPos += endPosIndex + 1;
		//		curolBufferSize -= endPosIndex + 1;

		//		char* pContent = NULL;
		//		UInt32 contentSize = 0;
		//		UInt16 packetType = 0;
		//		// 对完整块进行验证
		//		if(PacketEngine::CheckPacketSize(IOrecvBuffer, *IOrecvBufferSize, &pContent, &contentSize, &packetType))
		//		{
		//			MsgNode* pMsgNode = m_msgNodeBufferMgr->GetNewObject();
		//			pMsgNode->ObjectPort = m_localAddr->GetHostPort();
		//			pMsgNode->clientID = m_clientID;
		//			pMsgNode->msgType = packetType;
		//			pMsgNode->msgLength = contentSize;
		//			pMsgNode->msgContent = string(pContent, contentSize);

		//			m_pQueueService->AddToQueue(pMsgNode);
		//		}
		//		ZeroMemory(IOrecvBuffer, EMaxRecvBufferSize);
		//		*IOrecvBufferSize = 0;
		//	}
		//}
		//
		//Int32 startPosIndex = 0;
		//while(curolBufferSize && (startPosIndex = PacketEngine::GetStartTagPos(pStartPos, curolBufferSize, '[')) != -1)
		//{
		//	// 查找数据块尾部标识
		//	Int32 endPosIndex = PacketEngine::GetEndTagPos(pStartPos + startPosIndex, curolBufferSize, ']');
		//	if(endPosIndex == -1)
		//	{
		//		if(curolBufferSize > EMaxRecvBufferSize)
		//		{
		//			// 丢弃所有缓存数据
		//			ZeroMemory(IOrecvBuffer, EMaxRecvBufferSize);
		//			*IOrecvBufferSize = 0;
		//		}
		//		else
		//		{
		//			MyASSERT(curolBufferSize >= 0);
		//			MyASSERT(curolBufferSize <= EMaxRecvBufferSize);
		//			// 将数据都拷贝到缓存中
		//			memcpy(IOrecvBuffer, pStartPos, curolBufferSize);
		//			*IOrecvBufferSize += curolBufferSize;
		//		}
		//		return true;
		//	}
		//	else
		//	{
		//		MyASSERT(endPosIndex >= 0);

		//		char* pContent = NULL;
		//		UInt32 contentSize = 0;
		//		UInt16 packetType = 0;
		//		// 对完整块进行验证
		//		if(PacketEngine::CheckPacketSize(pStartPos, endPosIndex + 1, &pContent, &contentSize, &packetType))
		//		{
		//			MsgNode* pMsgNode = m_msgNodeBufferMgr->GetNewObject();
		//			pMsgNode->ObjectPort = m_localAddr->GetHostPort();
		//			pMsgNode->clientID = m_clientID;
		//			pMsgNode->msgType = packetType;
		//			pMsgNode->msgLength = contentSize;
		//			pMsgNode->msgContent = string(pContent, contentSize);
		//			
		//			m_pQueueService->AddToQueue(pMsgNode);
		//		}

		//		pStartPos += endPosIndex + 1;
		//		curolBufferSize -= endPosIndex + 1;
		//	}
		//}
		//return true;
	}
}