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
	enum DePacketErrorCode
	{
		EDePacketErrorCode_OutOfRange,
	};

	class DePacket
	{
	private:
		/** Êý¾Ý´óÐ¡ **/
		UInt32 m_dataSize;
		/** °üÊý¾Ý **/
		char* m_data;
		/** ÒÑ¶ÁÈ¡´óÐ¡ **/
		UInt32 m_unReadSize;
		/** ¶ÁÈ¡Î»ÖÃ **/
		char* m_readPos;
	public:
		/**
		* @brief ¹¹Ôìº¯Êý
		**/
		DePacket();

		/**
		* @brief Îö¹¹º¯Êý
		**/
		~DePacket();

	public:
		/**
		* @brief ³õÊ¼»¯½â°üÆ÷
		**/
		bool InitialPacket(string& INdata);

		/**
		* @brief ³õÊ¼»¯½â°üÆ÷
		**/
		bool InitialPacket(const char* INdata, UInt32 INdataSize);

		/**
		* @brief ¶ÁÈ¡Ò»¸ö²¼¶ûÖµ
		**/
		bool GetBool();

		/**
		* @brief ¶ÁÈ¡Ò»¸öÓÐ·ûºÅ×Ö·ûÖµ
		**/
		char GetChar();

		/**
		* @brief ¶ÁÈ¡Ò»¸öÎÞ·ûºÅ×Ö·ûÖµ
		**/
		unsigned char GetUChar();

		/**
		* @brief ¶ÁÈ¡Ò»¸öÓÐ·ûºÅ¶ÌÕûÐÍÖµ
		**/
		short GetShort();

		/**
		* @brief ¶ÁÈ¡Ò»¸öÎÞ·ûºÅ¶ÌÕûÐÍÖµ
		**/
		unsigned short GetUShort();

		/**
		* @brief ¶ÁÈ¡Ò»¸öÓÐ·ûºÅÕûÐÍÖµ
		**/
		int GetInt();

		/**
		* @brief ¶ÁÈ¡Ò»¸öÎÞ·ûºÅÕûÐÍÖµ
		**/
		unsigned int GetUInt();

		/**
		* @brief ¶ÁÈ¡Ò»¸öÓÐ·ûºÅ³¤ÕûÐÍÖµ
		**/
		long GetLong();

		/**
		* @brief ¶ÁÈ¡Ò»¸öÎÞ·ûºÅ³¤ÕûÐÍÖµ
		**/
		unsigned long GetULong();
#ifdef WIN32
		/**
		* @brief ¶ÁÈ¡Ò»¸ö64Î»ÓÐ·ûºÅÕûÐÍÖµ
		**/
		__int64 GetInt64();

		/**
		* @brief ¶ÁÈ¡Ò»¸ö64Î»ÎÞ·ûºÅÕûÐÍÖµ
		**/
		unsigned __int64 GetUInt64();
#else
#ifdef __GNUC__

		long long GetInt64();

		unsigned long long GetUInt64();
#endif
#endif
		/**
		* @brief ¶ÁÈ¡Ò»¸öµ¥¾«¶È¸¡µãÖµÖµ
		**/
		float GetFloat();

		/**
		* @brief ¶ÁÈ¡Ò»¸öË«¾«¶È¸¡µãÖµÖµ
		**/
		double GetDouble();

		/**
		* @brief ¶ÁÈ¡Ò»¸ö×Ö·û´®Öµ
		**/
		char* GetString(UInt32 INsize);

		/**
		* @brief ¶ÁÈ¡Ò»¸ö×Ö·û´®Öµ
		**/
		void GetString(string& OUTvalue, UInt32 INsize);
	};
}

#endif /* ENPACKET_H_ */
