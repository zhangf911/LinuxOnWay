#include "PacketEngine.h"
#include "Log.h"

namespace ZGF
{
	Int32 PacketEngine::GetStartTagPos(const char* INbuf, UInt32 INbufSize, char INtagChar)
	{
		Int32 pos = 0;
		bool find = false;
		//MyASSERT(strlen(INbuf) == INbufSize);
		while(pos < INbufSize)
		{
			if(INbuf[pos++] == INtagChar)
			{
				find = true;
				break;
			}
		}
		if(!find)
		{
			pos = -1;
		}
		return pos;
	}

	Int32 PacketEngine::GetEndTagPos(const char* INbuf, UInt32 INbufSize, char INtagChar)
	{
		Int32 pos = 0;
		bool find = false;
		//MyASSERT(strlen(INbuf) == INbufSize);
		while(pos < INbufSize)
		{
			if(INbuf[pos++] == INtagChar)
			{
				find = true;
				break;
			}
		}
		if(!find)
		{
			pos = -1;
		}
		return pos;
	}

	bool PacketEngine::CheckPacketSize(const char* INbuf, UInt32 INbufSize, char** OUTpacketContent, UInt32* OUTpacketSize, UInt16* OUTpacketType)
	{
		UInt16 checkSum = CheckSum(INbuf, INbufSize);
		//// 校验消息包
		//if(checkSum != 0)
		//{
		//	Log::Instance()->WriteNote("%s, %d, checkSum is %d", 
		//		__FUNCTION__, __LINE__, checkSum);
		//	return false;
		//}

		// 读取包体内容大小
		UInt32 packetSize = *(UInt16*)(INbuf + sizeof(char));
		*OUTpacketSize = packetSize;
		packetSize += sizeof(char);
		packetSize += sizeof(UInt32);
		packetSize += sizeof(UInt16);
		packetSize += sizeof(UInt16);
		packetSize += sizeof(char);
		// 校验整个消息包大小
		//if(packetSize != INbufSize)
		//{
		//	return false;
		//}
		*OUTpacketType = *(UInt16*)(INbuf + sizeof(char) + sizeof(UInt32));
		*OUTpacketContent = (char*)(INbuf + sizeof(char) + sizeof(UInt32) + sizeof(UInt16));
		return true;
	}

	UInt16 PacketEngine::CheckSum(const char* INdata, UInt32 INdataSize)
	{
		register Long checkSum = 0;
		while(INdataSize > 1)
		{
			checkSum += (UInt16)(UInt16*)INdata;
			INdataSize -= sizeof(UInt16);
			INdata += sizeof(UInt16);
		}

		if(INdataSize > 0)
		{
			checkSum += (UInt8)(UInt8*)INdata;
		}

		//while (checkSum>>16)
		//	checkSum = (checkSum & 0xffff) + (checkSum >> 16);
		// 将位累加和的高位与低位第一次相加
		checkSum = (checkSum >> 16) + (checkSum & 0xffff);
		// 将上一步可能产生的高位进位再次与低位累加
		checkSum += (checkSum >> 16);
		// 返回位校验和
		return (unsigned short)(~checkSum);
	}
}