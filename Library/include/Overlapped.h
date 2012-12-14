#ifndef LIBRARY_TCPSOCKET_OVERLAPPED_H
#define LIBRARY_TCPSOCKET_OVERLAPPED_H

#include "SocketComDef.h"

namespace ZGF
{
	enum TOverLappedType
	{
		EOverLappedType_Invalid,
		EOverLappedType_Connect,
		EOverLappedType_Accpet,
		EOverLappedType_Send,
		EOverLappedType_Recv,
		EOverLappedType_Disconnect,
		EOverLappedType_Error,
	};

	enum{EOverlappedBufferSize = 8 * 1024,};

	typedef struct OverLapped_Plus
	{
		/** �ص��ṹ **/
		WSAOVERLAPPED wsaOverLapped;
		/** ���ݻ��� **/
		WSABUF wsaBuff;
		/** �������� **/
		TOverLappedType type;
		/** �ͻ��˱�� **/
		UInt32 clientID;
		/** ���������ݻ��� **/
		char buf[EOverlappedBufferSize];

		OverLapped_Plus()
		{
			memset(&wsaOverLapped, 0, sizeof(WSAOVERLAPPED));
			memset(&wsaBuff, 0, sizeof(WSABUF));
			type = EOverLappedType_Invalid;
			clientID = 0;
			memset(buf, 0, EOverlappedBufferSize);
			wsaBuff.buf = buf;
			wsaBuff.len = EOverlappedBufferSize;
		}
	}OverLapped_Plus, OVERLAPPED_PLUS, *OVERLAPPED_PLUS_PTR;
}


#endif