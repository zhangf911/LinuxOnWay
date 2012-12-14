#ifndef LIBRARY_TCPSOCKET_SOCKETOPT_H
#define LIBRARY_TCPSOCKET_SOCKETOPT_H

#include "SocketComDef.h"
#include "BaseType.h"

namespace ZGF
{

	class SocketOpt
	{
	public:
		/**
		* @brief 设置重用地址
		**/
		static void SetSocketReuseAddr(SOCKET INsocket);

		/**
		* @brief 设置关闭不等待
		**/
		static void SetSocketCloseWithoutWait(SOCKET INsocket);

		/**
		* @brief 设置发送超时
		**/
		static void SetSocketSendTimeout(SOCKET INsocket, UInt32 INmilliSecond);

		/**
		* @brief 设置接收超时
		**/
		static void SetSocketRecvTimeout(SOCKET INsocket, UInt32 INmilliSecond);

		/**
		* @brief 设置发送缓存
		* @note  如果大小为0，则表示不发送不经过系统缓存区
		**/
		static void SetSocketSendBuffer(SOCKET INsocket, UInt32 INbufferSize);

		/**
		* @brief 设置接收缓存
		* @note  如果大小为0，则表示接收不经过系统缓存区
		**/
		static void SetSocketRecvBuffer(SOCKET INsocket, UInt32 INbufferSize);

		/**
		* @brief 设置关闭套接字时等待数据发送时间
		**/
		static void SetSocketCloseWaitIOTime(SOCKET INsocket, UInt32 INsecond);

		/**
		* @brief 设置心跳时间
		**/
		static void SetSocketKeeplive(SOCKET INsocket, UInt32 INlivetime, UInt32 INliveinterval);
	};
};



#endif