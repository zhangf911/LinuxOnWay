#ifndef LIBRARY_UTIL_DATATIME_H
#define LIBRARY_UTIL_DATATIME_H

#include "BaseType.h"

#include <string>
using std::string;

namespace ZGF
{
	/**
	* @class DataTime
	* @note ���̰߳�ȫ�����ܱ�֤���߳���������ȷ��
	**/
	class DataTime
	{
	public:
		/**
		* @brief ���ַ�����ʽ��ʱ��ת��Ϊ����ֵ
		* @note  �ַ�����ʽ xxxx-xx-xx xx:xx:xx
		**/
		static time_t ToInt(const string& INdataTimeString);

		/**
		* @brief ������ʱ��ת��Ϊ�ַ�����ʽ
		* @note  ��ʽΪ xxxx-xx-xx xx:xx:xx
		**/
		static string ToString(UInt32 INtime);

		/**
		* @brief ��ȡ�����賿ʱ��
		**/
		static UInt32 GetCurDayZeroTime();

		/**
		* @brief ���ڲ�
		**/
		static UInt32 DayDiff(UInt32 INtime1, UInt32 INtime2);
	};
};



#endif