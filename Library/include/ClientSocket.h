#ifndef LIBRARY_TCPSOCKET_CLIENTSOCKET_H
#define LIBRARY_TCPSOCKET_CLIENTSOCKET_H

#include "SocketComDef.h"
#include "BaseType.h"
#include "ObjectPool.h"
#include "PacketEngine.h"

#include <string>
#include <list>
using std::string;
using std::list;

namespace ZGF
{
	//struct MsgNode;
	class SocketAddr;
	struct OverLapped_Plus;
	typedef OverLapped_Plus OverLappedBuffer;
	template<class Object> class ObjectPool;
	typedef ObjectPool<OverLappedBuffer> OverlappedBufferMgr;
	typedef ObjectPool<MsgNode> MsgNodeBufferMgr;
	class QueueService;

	enum {EMaxRecvBufferSize = 8 * 1024,};

	enum ClientSocketState
	{
		EClientSocketState_Common,
		EClientSocketState_Close,
	};

	class ClientSocket
	{
		friend class IOCompleteThread;
		typedef list<OverLappedBuffer*> OverlappedList;
		typedef OverlappedList::iterator OverlappedListIter;
	private:
		/** 链接状态 **/
		UInt32 m_state;
		/** 客户端编号 **/
		UInt32 m_clientID;
		/** 连接时间 **/
		UInt32 m_connectTime;
		/** 发送计数 **/
		UInt32 m_sendCount;
		/** 接收计数 **/
		UInt32 m_recvCount;
		/** 最大接收缓存大小 **/
		UInt32 m_maxRecvBufferSize;
		/** 复用次数 **/
		UInt32 m_reusedCount;
		/** 是否已连接 **/
		bool m_completeConnect;
		/** 是否已关联完成端口 **/
		bool m_associateflage;
		/** 本地地址 **/
		SocketAddr* m_localAddr;
		/** 客户端地址 **/
		SocketAddr* m_remoteAddr;
		/** 未决发送列表 **/
		OverlappedList m_sendingList;
		/** 连接套接字 **/
		SOCKET m_socket;
		/** 监听套接字 **/
		SOCKET m_listenSocket;
		/** 完成端口 **/
		HANDLE m_completePort;
		/** 重叠缓存管理器 **/
		OverlappedBufferMgr* m_overlappedBufferMgr;
		/** 消息对象池 **/
		MsgNodeBufferMgr* m_msgNodeBufferMgr;
		/** 队列服务 **/
		QueueService* m_pQueueService;
		/** 接收缓存大小 **/
		UInt32 m_recvBufferSize;
		/** 接收缓存 **/
		char* m_recvBuffer;
		/** 接收锁 **/
		CriticalSection m_recvLock;
		/** IO锁 **/
		CriticalSection m_ioLock;
	public:
		/**
		* @brief 默认构造
		**/
		ClientSocket();

		/**
		* @brief 析构函数
		**/
		~ClientSocket();

	public:
		/**
		* @brief 获取套接字
		**/
		SOCKET GetClientSocket()
		{
			return m_socket;
		}

		/**
		* @brief 设置客户端编号
		**/
		inline void SetClientID(UInt32 INclientID)
		{
			m_clientID = INclientID;
		}

		/**
		* @brief 获取客户端编号
		**/
		inline UInt32 GetClientID()
		{
			return m_clientID;
		};

		/**
		* @brief 获取客户端IP地址
		**/
		string GetClientIP();

		/**
		* @brief 获取连接时间
		**/
		UInt32 GetConnectTime();

		/**
		* @brief 获取发送计数
		**/
		inline UInt32 GetSendCount()
		{
			return m_sendCount;
		};
		
		/**
		* @brief 获取发送计数
		**/
		inline UInt32 GetRecvCount()
		{
			return m_recvCount;
		};

		/**
		* @brief 获取重用次数
		* @return 重用次数
		* @exception 
		* @note 
		*/
		inline UInt32 GetReusedCount()
		{
			return m_reusedCount;
		}

		/**
		* @brief 自增复用次数
		* @exception 
		* @note 
		*/
		inline void AddReuseCount()
		{
			++m_reusedCount;
		};

		/**
		* @brief 是否是有效套接字
		**/
		inline bool IsValidSocket()
		{
			return m_socket != INVALID_SOCKET ? true : false;
		};

		/**
		* @brief 是否完成连接
		**/
		inline bool IsCompleteAccept()
		{
			return m_completeConnect;
		}

		/**
		* @brief 设置完成端口
		**/
		void SetCompletePort(HANDLE INcompletePort);

		/**
		* @brief 设置监听套接字
		**/
		void SetListenSocket(SOCKET INlistenSocket);
		
		/**
		* @brief 设置重叠缓存管理器
		**/
		void SetOverlappedBufferMgr(OverlappedBufferMgr* INbufferMgr);
				
		/**
		* @brief 设置消息对象池
		**/
		void SetMsgNodeBufferMgr(MsgNodeBufferMgr* INmsgNodeBufferMgr);
										
		/**
		* @brief 设置队列服务
		**/
		void SetQueueService(QueueService* INpQueueService);

		/**
		* @brief 初始化
		**/
		bool Initial();

		/**
		* @brief 客户端断开连接处理
		**/
		void Disconnect();

		/**
		* @brief 主动关闭连接处理
		**/
		void CloseSocket();

		/**
		* @brief 重置套接字
		**/
		void ResetSocket(OverLappedBuffer* INpBuffer);
		
		/**
		* @brief 清理资源
		**/
		void Clear();

		/**
		* @brief 清理未决发送列表
		**/
		void ClearSendingList();

		/**
		* @brief 投递接受连接请求
		* @param INpBuffer : 数据内容
		* @return ture : 投递成功 false : 投递失败
		* @note  由于这里采用非阻塞异步模式，所以函数返回时并不能保证数据已发送，只是将数据投递给了操作系统，由操作系统进行处理。
		**/
		bool PostAccept(OverLappedBuffer* INpBuffer);

		/**
		* @brief 投递发送请求
		* @param INpBuffer : 数据内容
		* @return ture : 投递成功 false : 投递失败
		* @note  由于这里采用非阻塞异步模式，所以函数返回时并不能保证数据已发送，只是将数据投递给了操作系统，由操作系统进行处理。
		**/
		bool PostSend(OverLappedBuffer* INpBuffer);

		/**
		* @brief 投递接收请求
		* @param INpBuffer : 数据内容
		* @return true : 投递成功 false : 投递失败
		* @note  由于这里采用非阻塞异步模式，所以函数返回时并不能保证数据已接收，只是将请求投递给了操作系统，由操作系统进行处理。
		**/
		bool PostRecv(OverLappedBuffer* INpBuffer);

		/**
		* @brief 投递断开连接请求
		* @param INpBuffer : 数据内容
		* @return true : 投递成功 false : 投递失败
		**/
		bool PostDisconnect(OverLappedBuffer* INpBuffer);

	private:
		/**
		* @brief 接收完成处理
		* @param INpBuffer : 数据内容
		* @return true
		**/
		bool OnAcceptComplete(OverLappedBuffer* INpBuffer, UInt32 INbufferSize);

		/**
		* @brief 发生完成处理
		* @param INpBuffer : 数据内容
		* @return true : 成功 false : 失败
		* @note  
		**/
		bool OnSendComplete(OverLappedBuffer* INpBuffer, UInt32 INbufferSize);

		/**
		* @brief 接收完成处理
		* @param INpBuffer : 数据内容
		* @return true : 成功 false : 失败
		* @note  
		**/
		bool OnRecvComplete(OverLappedBuffer* INpBuffer, UInt32 INbufferSize);
		
		/**
		* @brief 数据解析
		* @param INpBuffer : 数据内容
		* @return true : 成功 false : 失败
		* @note  
		**/
		bool ParseData(char* IOrecvBuffer, UInt32* IOrecvBufferSize, OverLappedBuffer* INpolBuffer, UInt32 INolBufferSize);
	};
}

#endif