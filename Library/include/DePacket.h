#ifndef LIBRARY_BASE_DEPACKET_H
#define LIBRARY_BASE_DEPACKET_H

#include "BaseType.h"
#include <string>
using std::string;

namespace ZGF
{
	enum DePacketErrorCode
	{
		EDePacketErrorCode_OutOfRange,
	};

	class DePacket
	{
	private:
		/** ���ݴ�С **/
		UInt32 m_dataSize;
		/** ������ **/
		char* m_data;
		/** �Ѷ�ȡ��С **/
		UInt32 m_unReadSize;
		/** ��ȡλ�� **/
		char* m_readPos;
	public:
		/**
		* @brief ���캯��
		**/
		DePacket();

		/**
		* @brief ��������
		**/
		~DePacket();

	public:
		/**
		* @brief ��ʼ�������
		**/
		bool InitialPacket(string& INdata);
		
		/**
		* @brief ��ʼ�������
		**/
		bool InitialPacket(const char* INdata, UInt32 INdataSize);

		/**
		* @brief ��ȡһ������ֵ
		**/
		bool GetBool();

		/**
		* @brief ��ȡһ���з����ַ�ֵ
		**/
		char GetChar();
		
		/**
		* @brief ��ȡһ���޷����ַ�ֵ
		**/
		unsigned char GetUChar();
		
		/**
		* @brief ��ȡһ���з��Ŷ�����ֵ
		**/
		short GetShort();
		
		/**
		* @brief ��ȡһ���޷��Ŷ�����ֵ
		**/
		unsigned short GetUShort();
		
		/**
		* @brief ��ȡһ���з�������ֵ
		**/
		int GetInt();
		
		/**
		* @brief ��ȡһ���޷�������ֵ
		**/
		unsigned int GetUInt();
		
		/**
		* @brief ��ȡһ���з��ų�����ֵ
		**/
		long GetLong();
		
		/**
		* @brief ��ȡһ���޷��ų�����ֵ
		**/
		unsigned long GetULong();
		
		/**
		* @brief ��ȡһ��64λ�з�������ֵ
		**/
		__int64 GetInt64();
		
		/**
		* @brief ��ȡһ��64λ�޷�������ֵ
		**/
		unsigned __int64 GetUInt64();
				
		/**
		* @brief ��ȡһ�������ȸ���ֵֵ
		**/
		float GetFloat();
				
		/**
		* @brief ��ȡһ��˫���ȸ���ֵֵ
		**/
		double GetDouble();
		
		/**
		* @brief ��ȡһ���ַ���ֵ
		**/
		char* GetString(UInt32 INsize);
		
		/**
		* @brief ��ȡһ���ַ���ֵ
		**/
		void GetString(string& OUTvalue, UInt32 INsize);
	};
}

#endif