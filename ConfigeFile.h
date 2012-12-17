/*
 * ConfigeFile.h
 *
 *  Created on: 2012-12-15
 *      Author: king
 */

#ifndef CONFIGEFILE_H_
#define CONFIGEFILE_H_

#include "Common.h"

namespace LOW
{
	/**
	* @class Cprofile
	* @brief 配置读写
	*/
	class Cprofile
	{
	private:
		/** 配置文件名 **/
		string fileName;

	public:

		/**
		* @brief 构造函数
		* @param INfileName : 文件名
		* @note
		*/
		Cprofile(const char* INfileName);

		/**
		* @brief 读取bool型配置数据
		* @param const char* INsegName: 配置段名
		* @param const char* INkeyName: 配置键名
		* @param bool* OUTvalue: bool型结果值
		* @return true : 成功 false : 失败
		* @note ¶ÁÈ¡true»òÕßfalse, Èç¹ûÊÇÊý×ÖÊ¹ÓÃÕûÊýÀàÐÍ¶ÁÈ¡,Ö»ÄÜ¶ÁÈ¡È«²¿´óÐ´»òÕßÐ¡Ð´
		*/
		bool ReadBOOL(const char* INsegName, const char* INkeyName, bool* OUTvalue);

		/**
		* @brief ¶ÁÈ¡ÎÞ·ûºÅ×Ö·û¼üÖµ
		* @param const char* INsegName: ¶ÎÃû
		* @param const char* INkeyName: ¼üÖµÃû
		* @param unsigned char * OUTvalue: ÊýÖµ
		* @return ·µ»Øtrue±íÊ¾³É¹¦,·µ»Øfalse±íÊ¾Ê§°Ü
		* @note
		*/
		bool ReadUChar(const char* INsegName, const char* INkeyName, unsigned char* OUTvalue);

		/**
		* @brief ¶ÁÈ¡×Ö·û¼üÖµ
		* @param const char* INsegName: ¶ÎÃû
		* @param const char* INkeyName: ¼üÖµÃû
		* @param char * OUTvalue: ÊýÖµ
		* @return ·µ»Øtrue±íÊ¾³É¹¦,·µ»Øfalse±íÊ¾Ê§°Ü
		* @note
		*/
		bool ReadChar(const char* INsegName, const char* INkeyName, char* OUTvalue);

		/**
		* @brief ¶ÁÈ¡ÎÞ·ûºÅ¶ÌÕûÊý¼üÖµ
		* @param const char* INsegName: ¶ÎÃû
		* @param const char* INkeyName: ¼üÖµÃû
		* @param unsigned short int* OUTvalue: ÊýÖµ
		* @return ·µ»Øtrue±íÊ¾³É¹¦,·µ»Øfalse±íÊ¾Ê§°Ü
		* @note
		*/
		bool ReadUSINT(const char* INsegName, const char* INkeyName, unsigned short int* OUTvalue);

		/**
		* @brief ¶ÁÈ¡¶ÌÕûÊý¼üÖµ
		* @param const char* INsegName: ¶ÎÃû
		* @param const char* INkeyName: ¼üÖµÃû
		* @param short int* OUTvalue: ÊýÖµ
		* @return ·µ»Øtrue±íÊ¾³É¹¦,·µ»Øfalse±íÊ¾Ê§°Ü
		* @note
		*/
		bool ReadSINT(const char* INsegName, const char* INkeyName, short int* OUTvalue);

		/**
		* @brief ¶ÁÈ¡ÎÞ·ûºÅÕûÊý¼üÖµ
		* @param const char* INsegName: ¶ÎÃû
		* @param const char* INkeyName: ¼üÖµÃû
		* @param unsigned int* OUTvalue: ÊýÖµ
		* @return ·µ»Øtrue±íÊ¾³É¹¦,·µ»Øfalse±íÊ¾Ê§°Ü
		* @note
		*/
		bool ReadUINT(const char* INsegName, const char* INkeyName, unsigned int* OUTvalue);

		/**
		* @brief ¶ÁÈ¡ÕûÊý¼üÖµ
		* @param const char* INsegName: ¶ÎÃû
		* @param const char* INkeyName: ¼üÖµÃû
		* @param int* OUTvalue: ÊýÖµ
		* @return ·µ»Øtrue±íÊ¾³É¹¦,·µ»Øfalse±íÊ¾Ê§°Ü
		* @note
		*/
		bool ReadINT(const char* INsegName, const char* INkeyName, int* OUTvalue);

		/**
		* @brief ¶ÁÈ¡ÎÞ·ûºÅ³¤ÕûÊý¼üÖµ
		* @param const char* INsegName: ¶ÎÃû
		* @param const char* INkeyName: ¼üÖµÃû
		* @param unsigned long* OUTvalue: ÊýÖµ
		* @return ·µ»Øtrue±íÊ¾³É¹¦,·µ»Øfalse±íÊ¾Ê§°Ü
		* @note
		*/
		bool ReadULONG(const char* INsegName, const char* INkeyName, unsigned long* OUTvalue);

		/**
		* @brief ¶ÁÈ¡³¤ÕûÊý¼üÖµ
		* @param const char* INsegName: ¶ÎÃû
		* @param const char* INkeyName: ¼üÖµÃû
		* @param long* OUTvalue: ÊýÖµ
		* @return ·µ»Øtrue±íÊ¾³É¹¦,·µ»Øfalse±íÊ¾Ê§°Ü
		* @note
		*/
		bool ReadLONG(const char* INsegName, const char* INkeyName, long* OUTvalue);

		/**
		* @brief ¶ÁÈ¡µ¥¾«¶È¸¡µãÐÍ¼üÖµ
		* @param const char* INsegName: ¶ÎÃû
		* @param const char* INkeyName: ¼üÖµÃû
		* @param float* OUTvalue: ÊýÖµ
		* @return ·µ»Øtrue±íÊ¾³É¹¦,·µ»Øfalse±íÊ¾Ê§°Ü
		* @note
		*/
		bool ReadFloat(const char* INsegName, const char* INkeyName, float* OUTvalue);

		/**
		* @brief ¶ÁÈ¡Ë«¾«¶È¸¡µãÐÍ¼üÖµ
		* @param const char* INsegName: ¶ÎÃû
		* @param const char* INkeyName: ¼üÖµÃû
		* @param double* OUTvalue: ÊýÖµ
		* @return ·µ»Øtrue±íÊ¾³É¹¦,·µ»Øfalse±íÊ¾Ê§°Ü
		* @note
		*/
		bool ReadDouble(const char* INsegName, const char* INkeyName, double* OUTvalue);

		/**
		* @brief ¶ÁÈ¡×Ö·û´®¼üÖµ
		* @param const char* INsegName: ¶ÎÃû
		* @param const char* INkeyName: ¼üÖµÃû
		* @param string* OUTvalue: ·µ»Ø×Ö·û´®
		* @return ·µ»Øtrue±íÊ¾³É¹¦,·µ»Øfalse±íÊ¾Ê§°Ü
		* @note
		*/
		bool ReadString(const char* INsegName, const char* INkeyName, string* OUTvalue);

		/**
		* @brief ¶ÁÈ¡×Ö·û´®¼üÖµ
		* @param const char* INsegName: ¶ÎÃû
		* @param const char* INkeyName: ¼üÖµÃû
		* @param char** OUTvalue: ·µ»Ø×Ö·û´®
		* @param int* OUTstrLen: ·µ»Ø×Ö·û´®³¤¶È
		* @return ·µ»Øtrue±íÊ¾³É¹¦,·µ»Øfalse±íÊ¾Ê§°Ü
		* @note
		*/
		bool ReadString(const char* INsegName, const char* INkeyName, char** OUTvalue, int* OUTstrLen);

		/**
		* @brief Ð´Èë×Ö·û´®ÀàÐÍµÄ¼üÖµ
		* @param const char* INsegName: ¶ÎÃû
		* @param const char* INkeyName: ¼üÖµÃû
		* @param const string& INstr: ÒªÐ´ÈëµÄ×Ö·û´®
		* @return ·µ»Øtrue±íÊ¾³É¹¦,·µ»Øfalse±íÊ¾Ê§°Ü
		* @note
		*/
		bool WriteKeyString(const char* INsegName, const char* INkeyName, const string& INstr);

		/**
		* @brief Ð´Èë×Ö·û´®ÀàÐÍµÄ¼üÖµ
		* @param const char* INsegName: ¶ÎÃû
		* @param const char* INkeyName: ¼üÖµÃû
		* @param const char* INstr: ÒªÐ´ÈëµÄ×Ö·û´®
		* @param int INsize: ×Ö·û´®³¤¶È
		* @return ·µ»Øtrue±íÊ¾³É¹¦,·µ»Øfalse±íÊ¾Ê§°Ü
		* @note
		*/
		bool WriteKeyString(const char* INsegName, const char* INkeyName, const char* INstr, int INsize);

		/**
		* @brief Ð´Èë¼üÖµ
		* @param const char* INsegName: ¶ÎÃû
		* @param const char* INkeyName: ¼üÖµÃû
		* @param T INvalue: Ð´ÈëµÄÊýÖµ
		* @param int INtype: TµÄÀàÐÍ
		* @param int INptrLen = 0: ×Ö·û´®³¤¶È
		* @return ·µ»Øtrue±íÊ¾³É¹¦,·µ»Øfalse±íÊ¾Ê§°Ü
		* @note
		*/
		template<typename T>
		bool WriteKeyValue(const char* INsegName, const char* INkeyName, T INvalue, int INtype, int INptrLen = 0)
		{
			try
			{
#ifdef WIN32
				string strBuffer;
				strBuffer.erase();
				char str[STRING_BUFFER_SIZE];
				switch(INtype)
				{
				case PROFILE_BOOL:
					if(INvalue)
					{
						strBuffer = "TRUE";
					}
					else
					{
						strBuffer = "FALSE";
					}
					break;
				case PROFILE_CHAR:
				case PROFILE_UCHAR:
					strBuffer = INvalue;
					break;
				case PROFILE_INT:
				case PROFILE_UINT:
				case PROFILE_SINT:
				case PROFILE_USINT:
					itoa((int)INvalue, str, RADIX_SIZE);
					strBuffer = str;
					break;
				case PROFILE_LONG:
				case PROFILE_ULONG:
					ltoa((long)INvalue, str, RADIX_SIZE);
					strBuffer = str;
					break;
				case PROFILE_FLOAT:
				case PROFILE_DOUBLE:
					gcvt((double)INvalue, FLOAT_PRECISE, str);
					strBuffer = str;
					break;
				default:
					break;
				}
				if(!WritePrivateProfileString((LPCSTR)INsegName, (LPCSTR)INkeyName, (LPSTR)strBuffer.c_str(), (LPCSTR)fileName.c_str()))
				{
					return false;
				}

#else
#ifdef __GNUC__
				// 尚未实现
#endif
#endif
			}
			catch(...)
			{
				return false;
			}
			return true;
		}
	};
}



#endif /* CONFIGEFILE_H_ */
