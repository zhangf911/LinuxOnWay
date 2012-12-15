/*
 * Code.h
 *
 *  Created on: 2012-12-15
 *      Author: king
 */

#ifndef CODE_H_
#define CODE_H_

#include "Common.h"

namespace LOW
{
	class Code
	{
	public:
		/**
		* @brief 将ASCII编码格式的字符串转换为UTF8格式的字符串
		* @param const string& INasciiString: ASCII格式字符串
		* @param string& OUTutf8String: UTF8格式字符串
		* @return true: 成功 false: 失败
		**/
		static bool ASCIIToUTF8(const string& INasciiString, string& OUTutf8String);

		/**
		* @brief 将UTF8编码格式的字符串转换为ASCII格式的字符串
		* @param const string& INutf8String: UTF8格式字符串
		* @param string& OUTasciiString: ASCII格式字符串
		* @return true: 成功; false: 失败
		**/
		static bool UTF8ToASCII(const string& INutf8String, string& OUTasciiString);


	};
}



#endif /* CODE_H_ */
