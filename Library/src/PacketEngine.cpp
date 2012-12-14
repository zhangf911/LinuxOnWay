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
		//// У����Ϣ��
		//if(checkSum != 0)
		//{
		//	Log::Instance()->WriteNote("%s, %d, checkSum is %d", 
		//		__FUNCTION__, __LINE__, checkSum);
		//	return false;
		//}

		// ��ȡ�������ݴ�С
		UInt32 packetSize = *(UInt16*)(INbuf + sizeof(char));
		*OUTpacketSize = packetSize;
		packetSize += sizeof(char);
		packetSize += sizeof(UInt32);
		packetSize += sizeof(UInt16);
		packetSize += sizeof(UInt16);
		packetSize += sizeof(char);
		// У��������Ϣ����С
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
		// ��λ�ۼӺ͵ĸ�λ���λ��һ�����
		checkSum = (checkSum >> 16) + (checkSum & 0xffff);
		// ����һ�����ܲ����ĸ�λ��λ�ٴ����λ�ۼ�
		checkSum += (checkSum >> 16);
		// ����λУ���
		return (unsigned short)(~checkSum);
	}
}