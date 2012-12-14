#ifndef LIBRARY_TCPSOCKET_PACKETBASE_H
#define LIBRARY_TCPSOCKET_PACKETBASE_H

#include "BaseType.h"
#include <string>
using std::string;

namespace ZGF
{
	struct PacketDef
	{
		/** ��ʼ�� **/
		char startTag;
		/** ���峤�� **/
		UInt16 packetSize;
		/** ������ **/
		UInt16 packetType;
		/** ������ **/
		string packetContent;
		/** У���� **/
		UInt16 checkCode;
		/** ������ **/
		char endTag;
	};

	class PacketBase
	{
	public:

	};
}


#endif