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
		* @brief �������õ�ַ
		**/
		static void SetSocketReuseAddr(SOCKET INsocket);

		/**
		* @brief ���ùرղ��ȴ�
		**/
		static void SetSocketCloseWithoutWait(SOCKET INsocket);

		/**
		* @brief ���÷��ͳ�ʱ
		**/
		static void SetSocketSendTimeout(SOCKET INsocket, UInt32 INmilliSecond);

		/**
		* @brief ���ý��ճ�ʱ
		**/
		static void SetSocketRecvTimeout(SOCKET INsocket, UInt32 INmilliSecond);

		/**
		* @brief ���÷��ͻ���
		* @note  �����СΪ0�����ʾ�����Ͳ�����ϵͳ������
		**/
		static void SetSocketSendBuffer(SOCKET INsocket, UInt32 INbufferSize);

		/**
		* @brief ���ý��ջ���
		* @note  �����СΪ0�����ʾ���ղ�����ϵͳ������
		**/
		static void SetSocketRecvBuffer(SOCKET INsocket, UInt32 INbufferSize);

		/**
		* @brief ���ùر��׽���ʱ�ȴ����ݷ���ʱ��
		**/
		static void SetSocketCloseWaitIOTime(SOCKET INsocket, UInt32 INsecond);

		/**
		* @brief ��������ʱ��
		**/
		static void SetSocketKeeplive(SOCKET INsocket, UInt32 INlivetime, UInt32 INliveinterval);
	};
};



#endif