#ifndef LIBRARY_TCPSOCKET_PACKETENGINE_H
#define LIBRARY_TCPSOCKET_PACKETENGINE_H

#include "BaseType.h"
#include <string>
using std::string;

namespace ZGF
{
	struct MsgNode
	{
		/** 消息类型 **/
		UInt16 msgType;

		/** 客户端编号 **/
		UInt32 clientID;

		/** 数据包长度 **/
		UInt32 msgLength;

		/** 消息包编号-对于没有包编号的使用默认编号 **/
		UInt32 packetID; // 自动处理

		/** 数据内容-字符串的长度受外部发送包的限制以及模块内部以及事务的限制一般不会操作1000个字节 **/
		string msgContent;

		/** 重发计数器 **/
		UInt32 resendCount; // 自动处理

		/** 入队时间--表示的时间是从1970/1/1到2038/1/1为止,超过该时间需要升级 **/
		time_t inTime; // 自动处理

		/** 超时时间:针对发送--单位是秒 **/
		UInt32 overTime; 

		/** 消息状态 **/
		UInt32 msgState; // 自动处理

		/** 客户端接收端口 **/
		UInt32 ObjectPort; //预留参数,目前无效

		/** 事务编号 **/
		UInt32 transID; // 默认为0,如果是返回包需要将该值赋为请求包的PacketID

		/** 数据包扩展编号 **/
		UInt32 packetOption; // 自动处理,适用与服务端数据库查询

		MsgNode()
		{
			// 默认参数初始化
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
		* @brief 获取结束标识位置
		**/
		static Int32 GetStartTagPos(const char* INbuf, UInt32 INbufSize, char INtagChar);

		/**
		* @brief 获取结束标识位置
		**/
		static Int32 GetEndTagPos(const char* INbuf, UInt32 INbufSize, char INtagChar);
		
		/**
		* @brief 校验包大小
		**/
		static bool CheckPacketSize(const char* INbuf, UInt32 INbufSize, char** OUTpacketContent, UInt32* OUTpacketSize, UInt16* OUTpacketType);
				
		/**
		* @brief 计算校验和
		**/
		static UInt16 CheckSum(const char* INdata, UInt32 INdataSize);
	};
}


#endif