/*
 * EnPacket.h
 *
 *  Created on: 2012-12-17
 *      Author: king
 */

#ifndef ENPACKET_H_
#define ENPACKET_H_

#include "Common.h"

namespace LOW
{
	class EnPacket
	{
	private:
		/** ¶þ½øÖÆÊý¾Ý **/
		string m_data;
		/** Ð´ÈëÎ»ÖÃ **/
		UInt32 m_pos;
	public:
		EnPacket();

		EnPacket(const EnPacket& INinstance);

		~EnPacket();

	public:
		EnPacket& operator = (const EnPacket& INinstance);

	public:
		/**
		* @brief Ñ¹ÈëÒ»¸ö²¼¶ûÖµ
		**/
		void PushBool(bool INvalue);

		/**
		* @brief Ñ¹ÈëÒ»¸ö×Ö·ûÖµ
		**/
		void PushChar(char INvalue);

		/**
		* @brief Ñ¹ÈëÒ»¸öÎÞ·ûºÅ×Ö·ûÖµ
		**/
		void PushUChar(unsigned char INvalue);

		/**
		* @brief Ñ¹ÈëÒ»¸ö¶ÌÕûÐÍÖµ
		**/
		void PushShort(short INvalue);

		/**
		* @brief Ñ¹ÈëÒ»¸öÎÞ·ûºÅ¶ÌÕûÐÍÖµ
		**/
		void PushUShort(unsigned short INvalue);

		/**
		* @brief Ñ¹ÈëÒ»¸öÎ»ÕûÐÍÖµ
		**/
		void PushInt(int INvalue);

		/**
		* @brief Ñ¹ÈëÒ»¸öÎÞ·ûºÅÕûÐÍÖµ
		**/
		void PushUInt(unsigned int INvalue);

		/**
		* @brief Ñ¹ÈëÒ»¸ö³¤ÕûÐÍÖµ
		**/
		void PushLong(long INvalue);

		/**
		* @brief Ñ¹ÈëÒ»¸öÎÞ·ûºÅ³¤ÕûÐÍÖµ
		**/
		void PushULong(unsigned long INvalue);

#ifdef WIN32
		/**
		* @brief Ñ¹ÈëÒ»¸ö64Î»ÓÐ·ûºÅÕûÐÍÖµ
		**/
		void PushInt64(__int64 INvalue);

		/**
		* @brief Ñ¹ÈëÒ»¸ö64Î»ÎÞ·ûºÅÕûÐÍÖµ
		**/
		void PushUInt64(unsigned __int64 INvalue);
#else
#ifdef __GNUC__
		void PushInt64(long long INvalue);

		void PushUInt64(unsigned long long INvalue);
#endif
#endif
		/**
		* @brief Ñ¹ÈëÒ»¸öµ¥¾«¶È¸¡µãÖµ
		**/
		void PushFloat(float INvalue);

		/**
		* @brief Ñ¹ÈëÒ»¸öË«¾«¶È¸¡µãÖµ
		**/
		void PushDouble(double INvalue);

		/**
		* @brief Ñ¹ÈëÒ»¸ö×Ö·û´®
		**/
		void PushString(const char* INdata, UInt32 INdataSize);

		/**
		* @brief Ñ¹ÈëÒ»¸ö×Ö·û´®
		**/
		void PushString(const string& INdata);

		/**
		* @brief ¶¨Î»
		* @param INpos : Î»ÖÃ
		* @exception
		* @note INpos³¬¹ýÊý¾Ý´óÐ¡£¬Ôò´¦ÀíÎªÊý¾ÝÎ²¶Ë
		**/
		void Seekg(UInt32 INpos);

		/**
		* @brief »ñÈ¡°üÊý¾Ý
		**/
		const string& GetString()
		{
			return m_data;
		};

		/**
		* @brief »ñÈ¡°ü´óÐ¡
		**/
		inline UInt32 GetLength()
		{
			return m_data.size();
		};

		/**
		* @brief ÇåÀí°üÊý¾Ý
		**/
		void Clear()
		{
			m_data.clear();
			m_pos = 0;
		};

	private:
		template <typename DataType>
		void PushData(DataType* INdata, UInt32 INdataSize = sizeof(DataType));
	};
}



#endif /* ENPACKET_H_ */
