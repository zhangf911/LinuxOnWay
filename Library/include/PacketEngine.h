#ifndef LIBRARY_TCPSOCKET_PACKETENGINE_H
#define LIBRARY_TCPSOCKET_PACKETENGINE_H

#include "BaseType.h"
#include <string>
using std::string;

namespace ZGF
{
	struct MsgNode
	{
		/** ��Ϣ���� **/
		UInt16 msgType;

		/** �ͻ��˱�� **/
		UInt32 clientID;

		/** ���ݰ����� **/
		UInt32 msgLength;

		/** ��Ϣ�����-����û�а���ŵ�ʹ��Ĭ�ϱ�� **/
		UInt32 packetID; // �Զ�����

		/** ��������-�ַ����ĳ������ⲿ���Ͱ��������Լ�ģ���ڲ��Լ����������һ�㲻�����1000���ֽ� **/
		string msgContent;

		/** �ط������� **/
		UInt32 resendCount; // �Զ�����

		/** ���ʱ��--��ʾ��ʱ���Ǵ�1970/1/1��2038/1/1Ϊֹ,������ʱ����Ҫ���� **/
		time_t inTime; // �Զ�����

		/** ��ʱʱ��:��Է���--��λ���� **/
		UInt32 overTime; 

		/** ��Ϣ״̬ **/
		UInt32 msgState; // �Զ�����

		/** �ͻ��˽��ն˿� **/
		UInt32 ObjectPort; //Ԥ������,Ŀǰ��Ч

		/** ������ **/
		UInt32 transID; // Ĭ��Ϊ0,����Ƿ��ذ���Ҫ����ֵ��Ϊ�������PacketID

		/** ���ݰ���չ��� **/
		UInt32 packetOption; // �Զ�����,�������������ݿ��ѯ

		MsgNode()
		{
			// Ĭ�ϲ�����ʼ��
			clientID = 0;
			msgType = 0;
			msgLength = 0;
			packetID = 0;
			msgContent = "";
			resendCount = 0;
			inTime = 0;
			overTime = 0;
			msgState = 0;
			ObjectPort = 0;
			transID = 0;
			packetOption = 0;
		}

	};

	class PacketEngine
	{
	public:
		
		/**
		* @brief ��ȡ������ʶλ��
		**/
		static Int32 GetStartTagPos(const char* INbuf, UInt32 INbufSize, char INtagChar);

		/**
		* @brief ��ȡ������ʶλ��
		**/
		static Int32 GetEndTagPos(const char* INbuf, UInt32 INbufSize, char INtagChar);
		
		/**
		* @brief У�����С
		**/
		static bool CheckPacketSize(const char* INbuf, UInt32 INbufSize, char** OUTpacketContent, UInt32* OUTpacketSize, UInt16* OUTpacketType);
				
		/**
		* @brief ����У���
		**/
		static UInt16 CheckSum(const char* INdata, UInt32 INdataSize);
	};
}


#endif