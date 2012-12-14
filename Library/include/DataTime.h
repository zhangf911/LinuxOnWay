#ifndef LIBRARY_UTIL_DATATIME_H
#define LIBRARY_UTIL_DATATIME_H

#include "BaseType.h"

#include <string>
using std::string;

namespace ZGF
{
	/**
	* @class DataTime
	* @note 非线程安全，不能保证多线程下数据正确性
	**/
	class DataTime
	{
	public:
		/**
		* @brief 将字符串形式的时间转换为整型值
		* @note  字符串格式 xxxx-xx-xx xx:xx:xx
		**/
		static time_t ToInt(const string& INdataTimeString);

		/**
		* @brief 将整型时间转换为字符串形式
		* @note  格式为 xxxx-xx-xx xx:xx:xx
		**/
		static string ToString(UInt32 INtime);

		/**
		* @brief 获取当日凌晨时间
		**/
		static UInt32 GetCurDayZeroTime();

		/**
		* @brief 日期差
		**/
		static UInt32 DayDiff(UInt32 INtime1, UInt32 INtime2);
	};
};



#endif