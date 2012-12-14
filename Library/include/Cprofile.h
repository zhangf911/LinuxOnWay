#ifndef LIBRARY_UTIL_CPROFILE_H
#define LIBRARY_UTIL_CPROFILE_H

#include <windows.h>
#include <string>
using namespace std;

/** 最大数值 **/
#define MAX_INT 0xffffffff
/** 错误信息 **/
#define ERROR_STRING "Read string error!"
/** 数值类缓冲区大小 **/
#define NUM_BUFFER_SIZE 32
/** 字符串缓冲区大小 **/
#define STRING_BUFFER_SIZE 256
/** 浮点数精度 **/
#define FLOAT_PRECISE 10
/** 读写的进制数 **/
#define RADIX_SIZE 10

/** INTPYE的取值 **/
#define PROFILE_CHAR 0
#define PROFILE_UCHAR 1
#define PROFILE_SINT 2
#define PROFILE_USINT 3
#define PROFILE_INT 4
#define PROFILE_UINT 5
#define PROFILE_LONG 6
#define PROFILE_ULONG 7
#define PROFILE_FLOAT 8
#define PROFILE_DOUBLE 9
#define PROFILE_BOOL 10
#define PROFILE_STRING 11
#define PROFILE_CHARPTR 12

namespace ZGF
{
	/**
	* @class Cprofile
	* @brief 配置文件的读写
	*/
	class Cprofile
	{
	private:
		/** 配置文件名称 **/
		string fileName;

	public:

		/**
		* @brief 默认初始化
		* @param INfileName : 配置文件名称
		* @note 
		*/
		Cprofile(const char* INfileName);

		/**
		* @brief 读取无符号整数键值
		* @param const char* INsegName: 段名
		* @param const char* INkeyName: 键值名
		* @param bool* OUTvalue: 数值
		* @return 返回true表示成功,返回false表示失败
		* @note 读取true或者false, 如果是数字使用整数类型读取,只能读取全部大写或者小写
		*/
		bool ReadBOOL(const char* INsegName, const char* INkeyName, bool* OUTvalue);

		/**
		* @brief 读取无符号字符键值
		* @param const char* INsegName: 段名
		* @param const char* INkeyName: 键值名
		* @param unsigned char * OUTvalue: 数值
		* @return 返回true表示成功,返回false表示失败
		* @note 
		*/
		bool ReadUChar(const char* INsegName, const char* INkeyName, unsigned char* OUTvalue);

		/**
		* @brief 读取字符键值
		* @param const char* INsegName: 段名
		* @param const char* INkeyName: 键值名
		* @param char * OUTvalue: 数值
		* @return 返回true表示成功,返回false表示失败
		* @note 
		*/
		bool ReadChar(const char* INsegName, const char* INkeyName, char* OUTvalue);
		
		/**
		* @brief 读取无符号短整数键值
		* @param const char* INsegName: 段名
		* @param const char* INkeyName: 键值名
		* @param unsigned short int* OUTvalue: 数值
		* @return 返回true表示成功,返回false表示失败
		* @note 
		*/
		bool ReadUSINT(const char* INsegName, const char* INkeyName, unsigned short int* OUTvalue);
	
		/**
		* @brief 读取短整数键值
		* @param const char* INsegName: 段名
		* @param const char* INkeyName: 键值名
		* @param short int* OUTvalue: 数值
		* @return 返回true表示成功,返回false表示失败
		* @note 
		*/
		bool ReadSINT(const char* INsegName, const char* INkeyName, short int* OUTvalue);

		/**
		* @brief 读取无符号整数键值
		* @param const char* INsegName: 段名
		* @param const char* INkeyName: 键值名
		* @param unsigned int* OUTvalue: 数值
		* @return 返回true表示成功,返回false表示失败
		* @note 
		*/
		bool ReadUINT(const char* INsegName, const char* INkeyName, unsigned int* OUTvalue);

		/**
		* @brief 读取整数键值
		* @param const char* INsegName: 段名
		* @param const char* INkeyName: 键值名
		* @param int* OUTvalue: 数值
		* @return 返回true表示成功,返回false表示失败
		* @note 
		*/
		bool ReadINT(const char* INsegName, const char* INkeyName, int* OUTvalue);

		/**
		* @brief 读取无符号长整数键值
		* @param const char* INsegName: 段名
		* @param const char* INkeyName: 键值名
		* @param unsigned long* OUTvalue: 数值
		* @return 返回true表示成功,返回false表示失败
		* @note 
		*/
		bool ReadULONG(const char* INsegName, const char* INkeyName, unsigned long* OUTvalue);

		/**
		* @brief 读取长整数键值
		* @param const char* INsegName: 段名
		* @param const char* INkeyName: 键值名
		* @param long* OUTvalue: 数值
		* @return 返回true表示成功,返回false表示失败
		* @note 
		*/
		bool ReadLONG(const char* INsegName, const char* INkeyName, long* OUTvalue);

		/**
		* @brief 读取单精度浮点型键值
		* @param const char* INsegName: 段名
		* @param const char* INkeyName: 键值名
		* @param float* OUTvalue: 数值
		* @return 返回true表示成功,返回false表示失败
		* @note 
		*/
		bool ReadFloat(const char* INsegName, const char* INkeyName, float* OUTvalue);

		/**
		* @brief 读取双精度浮点型键值
		* @param const char* INsegName: 段名
		* @param const char* INkeyName: 键值名
		* @param double* OUTvalue: 数值
		* @return 返回true表示成功,返回false表示失败
		* @note 
		*/
		bool ReadDouble(const char* INsegName, const char* INkeyName, double* OUTvalue);

		/**
		* @brief 读取字符串键值
		* @param const char* INsegName: 段名
		* @param const char* INkeyName: 键值名
		* @param string* OUTvalue: 返回字符串
		* @return 返回true表示成功,返回false表示失败
		* @note 
		*/
		bool ReadString(const char* INsegName, const char* INkeyName, string* OUTvalue);
		
		/**
		* @brief 读取字符串键值
		* @param const char* INsegName: 段名
		* @param const char* INkeyName: 键值名
		* @param char** OUTvalue: 返回字符串
		* @param int* OUTstrLen: 返回字符串长度
		* @return 返回true表示成功,返回false表示失败
		* @note 
		*/
		bool ReadString(const char* INsegName, const char* INkeyName, char** OUTvalue, int* OUTstrLen);

		/**
		* @brief 写入字符串类型的键值
		* @param const char* INsegName: 段名
		* @param const char* INkeyName: 键值名
		* @param const string& INstr: 要写入的字符串
		* @return 返回true表示成功,返回false表示失败
		* @note 
		*/
		bool WriteKeyString(const char* INsegName, const char* INkeyName, const string& INstr);

		/**
		* @brief 写入字符串类型的键值
		* @param const char* INsegName: 段名
		* @param const char* INkeyName: 键值名
		* @param const char* INstr: 要写入的字符串
		* @param int INsize: 字符串长度
		* @return 返回true表示成功,返回false表示失败
		* @note 
		*/
		bool WriteKeyString(const char* INsegName, const char* INkeyName, const char* INstr, int INsize);

		/**
		* @brief 写入键值
		* @param const char* INsegName: 段名
		* @param const char* INkeyName: 键值名
		* @param T INvalue: 写入的数值
		* @param int INtype: T的类型
		* @param int INptrLen = 0: 字符串长度
		* @return 返回true表示成功,返回false表示失败
		* @note 
		*/
		template<typename T>
		bool WriteKeyValue(const char* INsegName, const char* INkeyName, T INvalue, int INtype, int INptrLen = 0)
		{
			try
			{
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
			}
			catch(...)
			{
				return false;
			}
			return true;
		}
	};
}


#endif