/*
 * Log.h
 *
 *  Created on: 2012-12-17
 *      Author: king
 */

#ifndef LOG_H_
#define LOG_H_


#include <string>
#include <fstream>
using std::ofstream;
using std::string;

#include "Common.h"

namespace LOW
{
	#define LogBufSize 32768
	#define TIME_FORMAT "[%Y-%m-%d %H:%M:%S] "
	#define TIME_FORMAT2 "[%Y-%m-%d %H-%M-%S]"
	#define TIME_FORMAT_LENGTH 40
	#define HEAD_LENGTH 20

	enum LogType
	{
		/// ¿ØÖÆÌ¨ÌáÊ¾ÐÅÏ¢
		ELogType_Console_Note = 0x0001,
		/// ¿ØÖÆÌ¨µ÷ÊÔÐÅÏ¢
		ELogType_Console_Debug = 0x0002,
		/// ¿ØÖÆÌ¨´íÎóÐÅÏ¢
		ELogType_Console_Error = 0x0004,
		/// ¿ØÖÆÌ¨Òì³£ÐÅÏ¢
		ELogType_Console_Exception = 0x0008,
		/// ¿ØÖÆÌ¨¸÷ÀàÐÅÏ¢
		ELogType_Console_All = ELogType_Console_Note | ELogType_Console_Debug | ELogType_Console_Error | ELogType_Console_Exception,
		/// ÎÄ¼þÌáÊ¾ÐÅÏ¢
		ELogType_File_Note = 0x0010,
		/// ÎÄ¼þµ÷ÊÔÐÅÏ¢
		ELogType_File_Debug = 0x0020,
		/// ÎÄ¼þ´íÎóÐÅÏ¢
		ELogType_File_Error = 0x0040,
		/// ÎÄ¼þÒì³£ÐÅÏ¢
		ELogType_File_Exception = 0x0080,
		/// ÎÄ¼þ¸÷ÀàÐÅÏ¢
		ELogType_File_All = ELogType_File_Note | ELogType_File_Debug | ELogType_File_Error | ELogType_File_Exception,
		/// ËùÓÐÐÅÏ¢
		ELogType_All = ELogType_Console_All | ELogType_File_All,
	};

	enum LogColor
	{
		ELogColor_Black,
		ELogColor_Red,
		ELogColor_Green,
		ELogColor_Brown,
		ELogColor_Blue,
		ELogColor_Magenta,
		ELogColor_Cyan,
		ELogColor_Grey,
		ELogColor_Yellow,
		ELogColor_LRed,
		ELogColor_LGreen,
		ELogColor_LBlue,
		ELogColor_LMagenta,
		ELogColor_LCyan,
		ELogColor_White,
	};

	enum ELogTextCode
	{
		ELogTextCode_ANSI,
		ELogTextCode_UTF8,
	};

	class Log
	{
	private:
		/** Êä³öÈÕÖ¾ÅäÖÃ **/
		UInt32 m_logPriority;
		/** ÈÕÖ¾ÎÄ¼þ **/
		ofstream m_fileStream;
		/** ÎÄ¼þ±àÂë¸ñÊ½ **/
		UInt32 m_fileCode;
		/** µ±Ç°ÎÄ±¾±àÂë¸ñÊ½ **/
		UInt32 m_textCode;
	public:
		Log();

		~Log();

	public:

		/**
		* @brief ³õÊ¼»¯
		**/
		void Initial(const char* INfileName, UInt32 INtextCode = ELogTextCode_ANSI);

		/**
		* @brief ÉèÖÃÈÕÖ¾µÈ¼¶
		**/
		void SetLogPriority(UInt32 INpriority);

		/**
		* @brief »ñÈ¡ÈÕÖ¾µÈ¼¶
		**/
		UInt32 GetLogPriority();

		/**
		* @brief ÉèÖÃÈÕÖ¾ÎÄ±¾±àÂë
		* @param INcodeType : ±àÂëÀàÐÍ
		* @exception
		* @note
		**/
		void SetLogTextCode(UInt32 INcodeType);

		/**
		* @brief »ñÈ¡ÈÕÖ¾ÎÄ±¾±àÂë
		* @return ÈÕÖ¾ÎÄ±¾±àÂë
		* @exception
		* @note
		**/
		UInt32 GetLogTextCode();

		/**
		* @brief ÉèÖÃÈÕÖ¾ÑÕÉ«
		**/
		void SetColor(LogColor INcolor);

		/**
		* @brief »Ö¸´Ä¬ÈÏÈÕÖ¾ÑÕÉ«
		**/
		void ResetColor();

		/**
		* @brief Êä³öÌáÊ¾ÐÅÏ¢
		**/
		void WriteNote(const char* INline, ...);

		/**
		* @brief Êä³öµ÷ÊÔÐÅÏ¢
		**/
		void WriteDebug(const char* INline, ...);

		/**
		* @brief Êä³ö´íÎóÐÅÏ¢
		**/
		void WriteError(const char* INline, ...);

		/**
		* @brief Êä³öÒì³£ÐÅÏ¢
		**/
		void WriteException(const char* INline, ...);

		/**
		* @brief Êä³öÒ»ÐÐ¿ØÖÆÌ¨ÈÕÖ¾
		**/
		void WriteConsoleLine(const char* INline, UInt32 INtype);

		/**
		* @brief Êä³öÒ»ÐÐÎÄ¼þÈÕÖ¾
		**/
		void WriteFileLine(const char* INline, UInt32 INtype);

		/**
		* @brief Êä³öÒ»ÐÐ¿ØÖÆÌ¨ÈÕÖ¾
		**/
		void WriteConsoleLine(const string& INline, UInt32 INtype);

		/**
		* @brief Êä³öÒ»ÐÐÎÄ¼þÈÕÖ¾
		**/
		void WriteFileLine(const string& INline, UInt32 INtype);

		/**
		* @brief Êä³öÒ»ÐÐ
		**/
		void WriteLine(const char* INline, ...);

		/**
		* @brief ¸ñÊ½»¯Ê±¼ä×Ö·û´®
		**/
		static void GetTimeString(char* INbuffer, const char* INtimeFormat);
	};
}

#endif /* LOG_H_ */
