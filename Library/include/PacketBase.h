#ifndef LIBRARY_TCPSOCKET_PACKETBASE_H
#define LIBRARY_TCPSOCKET_PACKETBASE_H

#include "BaseType.h"
#include <string>
using std::string;

namespace ZGF
{
	struct PacketDef
	{
		/** 起始符 **/
		char startTag;
		/** 包体长度 **/
		UInt16 packetSize;
		/** 包类型 **/
		UInt16 packetType;
		/** 包内容 **/
		string packetContent;
		/** 校验码 **/
		UInt16 checkCode;
		/** 结束符 **/
		char endTag;
	};

	class PacketBase
	{
	public:

	};
}


#endif