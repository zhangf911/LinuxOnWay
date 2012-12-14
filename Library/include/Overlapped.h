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
		/** 重叠结构 **/
		WSAOVERLAPPED wsaOverLapped;
		/** 数据缓冲 **/
		WSABUF wsaBuff;
		/** 操作类型 **/
		TOverLappedType type;
		/** 客户端编号 **/
		UInt32 clientID;
		/** 真正的数据缓存 **/
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