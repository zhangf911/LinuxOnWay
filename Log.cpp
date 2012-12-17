/*
 * Log.cpp
 *
 *  Created on: 2012-12-17
 *      Author: king
 */

#include "Log.h"
#include "Console.h"
#include "Code.h"
#include <cstdio>
#include <cstdarg>
#include <iostream>
#include <time.h>

#ifdef WIN32
#include <Windows.h>
#else
#ifdef __GNUC__

#endif
#endif

namespace LOW
{
	Log::Log()
	{
		m_logPriority = 0;
	}

	Log::~Log()
	{
		if(!m_fileStream.is_open())
		{
			m_fileStream.close();
		}
	}

	void Log::Initial(const char* INfileName, UInt32 INtextCode)
	{
		// ´ò¿ªÎÄ¼þ
		if(!m_fileStream.is_open())
		{
			m_fileCode = INtextCode;

			char timeBuf[40];
			GetTimeString(timeBuf, TIME_FORMAT2);
			string filename = INfileName;
			string temp = filename.substr(0, filename.find_last_of('.'));
			string extensionName = filename.substr(filename.find_last_of('.'));
			temp += timeBuf;
			temp += extensionName;
			m_fileStream.open(temp.c_str());
			if(!m_fileStream)
			{
				std::cerr << "Open File : " << temp << " Failed!" << std::endl;
			}
		}
	}

	void Log::SetLogPriority(UInt32 INpriority)
	{
		m_logPriority = INpriority;
	}

	UInt32 Log::GetLogPriority()
	{
		return m_logPriority;
	}

	void Log::SetLogTextCode(UInt32 INcodeType)
	{
		m_textCode = INcodeType;
	}

	UInt32 Log::GetLogTextCode()
	{
		return m_textCode;
	}

	void Log::SetColor(LogColor INcolor)
	{
		ConsoleInterface::SetConsoleTextColor(true, Color(INcolor));
	}

	void Log::ResetColor()
	{
		ConsoleInterface::ResetConsoleTextColor(true);
	}

	void Log::WriteNote(const char* INline, ...)
	{
		if(((m_logPriority & ELogType_Console_Note) == 0) &&
			((m_logPriority & ELogType_File_Note) == 0))
		{
			return;
		}
		char buf[LogBufSize];
		va_list ap;

		va_start(ap, INline);
		vsnprintf(buf, LogBufSize, INline, ap);
		va_end(ap);

		if(m_logPriority & ELogType_Console_Note)
		{
			//SetColor(ELogColor_DeepYellow);
			// Êä³ö¿ØÖÆÌ¨ÌáÊ¾ÐÅÏ¢
			WriteConsoleLine(buf, ELogType_Console_Note);
		}
		if(m_logPriority & ELogType_File_Note)
		{
			if(!m_fileStream)
			{
				std::cerr << "File have not opened!" << std::endl;
				return;
			}
			// Êä³öÎÄ¼þÌáÊ¾ÐÅÏ¢
			WriteFileLine(buf, ELogType_File_Note);
		}
	}

	void Log::WriteDebug(const char* INline, ...)
	{
		if(((m_logPriority & ELogType_Console_Debug) == 0) &&
			((m_logPriority & ELogType_File_Debug) == 0))
		{
			return;
		}
		char buf[LogBufSize];
		va_list ap;

		va_start(ap, INline);
		vsnprintf(buf, LogBufSize, INline, ap);
		va_end(ap);

		if(m_logPriority & ELogType_Console_Debug)
		{
			//SetColor(ELogColor_DeepGreen);
			// Êä³ö¿ØÖÆÌ¨µ÷ÊÔÐÅÏ¢
			WriteConsoleLine(buf, ELogType_Console_Debug);
		}
		if(m_logPriority & ELogType_File_Debug)
		{
			if(!m_fileStream)
			{
				std::cerr << "File have not opened!" << std::endl;
				return;
			}
			// Êä³öÎÄ¼þµ÷ÊÔÐÅÏ¢
			WriteFileLine(buf, ELogType_File_Debug);
		}
	}

	void Log::WriteError(const char* INline, ...)
	{
		if(((m_logPriority & ELogType_Console_Error) == 0) &&
			((m_logPriority & ELogType_File_Error) == 0))
		{
			return;
		}
		char buf[LogBufSize];
		va_list ap;

		va_start(ap, INline);
		vsnprintf(buf, LogBufSize, INline, ap);
		va_end(ap);

		if(m_logPriority & ELogType_Console_Error)
		{
			//SetColor(ELogColor_DeepRed);
			SetColor(ELogColor_LRed);
			// Êä³ö¿ØÖÆÌ¨´íÎóÐÅÏ¢
			WriteConsoleLine(buf, ELogType_Console_Error);
			//
			//SetColor(ELogColor_White);
			ResetColor();
		}

		if(m_logPriority & ELogType_File_Error)
		{
			if(!m_fileStream)
			{
				std::cerr << "File have not opened!" << std::endl;
				return;
			}
			// Êä³öÎÄ¼þ´íÎóÐÅÏ¢
			WriteFileLine(buf, ELogType_File_Error);
		}
	}

	void Log::WriteException(const char* INline, ...)
	{
		if(((m_logPriority & ELogType_Console_Exception) == 0) &&
			((m_logPriority & ELogType_File_Exception) == 0))
		{
			return;
		}
		char buf[LogBufSize];
		va_list ap;

		va_start(ap, INline);
		vsnprintf(buf, LogBufSize, INline, ap);
		va_end(ap);

		if(m_logPriority & ELogType_Console_Exception)
		{
			SetColor(ELogColor_Magenta);
			// Êä³ö¿ØÖÆÌ¨Òì³£ÐÅÏ¢
			WriteConsoleLine(buf, ELogType_Console_Exception);
			ResetColor();
		}

		if(m_logPriority & ELogType_File_Exception)
		{
			if(!m_fileStream)
			{
				std::cerr << "File have not opened!" << std::endl;
				return;
			}
			// Êä³öÎÄ¼þÒì³£ÐÅÏ¢
			WriteFileLine(buf, ELogType_File_Exception);
		}
	}

	void Log::WriteConsoleLine(const char* INline, UInt32 INtype)
	{
		char strTime[TIME_FORMAT_LENGTH];
		GetTimeString(strTime, TIME_FORMAT);
		string head;
		switch(INtype)
		{
		case ELogType_Console_Note:
		case ELogType_File_Note:
			{
				head = "[Note] ";
				break;
			}
		case ELogType_Console_Debug:
		case ELogType_File_Debug:
			{
				head = "[Debug] ";
				break;
			}
		case ELogType_Console_Error:
		case ELogType_File_Error:
			{
				head = "[Error] ";
				break;
			}
		case ELogType_Console_Exception:
		case ELogType_File_Exception:
			{
				head = "[Exception] ";
				break;
			}
		default:
			{
				head = "";
				break;
			}
		}
		/***
		string lineText = "";
		if(m_fileCode != m_textCode)
		{
			switch(m_textCode)
			{
			case ELogTextCode_ANSI:
				{
					Code::UTF8ToASCII(INline, lineText);
					break;
				}
			case ELogTextCode_UTF8:
				{
					Code::ASCIIToUTF8(INline, lineText);
					break;
				}
			}
		}
		std::cout << strTime << head << lineText.c_str() << std::endl;
		***/
		std::cout << strTime << head << INline << std::endl;
	}

	void Log::WriteFileLine(const char* INline, UInt32 INtype)
	{
		char strTime[TIME_FORMAT_LENGTH];
		GetTimeString(strTime, TIME_FORMAT);
		string head;
		switch(INtype)
		{
		case ELogType_Console_Note:
		case ELogType_File_Note:
			{
				head = "[Note]";
				break;
			}
		case ELogType_Console_Debug:
		case ELogType_File_Debug:
			{
				head = "[Debug]";
				break;
			}
		case ELogType_Console_Error:
		case ELogType_File_Error:
			{
				head = "[Error]";
				break;
			}
		case ELogType_Console_Exception:
		case ELogType_File_Exception:
			{
				head = "[Exception]";
				break;
			}
		default:
			{
				head = "";
				break;
			}
		}
		/***
		string lineText = "";
		if(m_fileCode != m_textCode)
		{
			switch(m_textCode)
			{
			case ELogTextCode_ANSI:
				{
					Code::UTF8ToASCII(INline, lineText);
					break;
				}
			case ELogTextCode_UTF8:
				{
					Code::ASCIIToUTF8(INline, lineText);
					break;
				}
			}
		}
		m_fileStream << strTime << head << lineText.c_str() << std::endl;
		***/
		m_fileStream << strTime << head << INline << std::endl;
	}

	void Log::WriteConsoleLine(const string& INline, UInt32 INtype)
	{

	}

	void Log::WriteFileLine(const string& INline, UInt32 INtype)
	{

	}

	void Log::WriteLine(const char* INline, ...)
	{

	}

	void Log::GetTimeString(char* INbuffer, const char* INtimeFormat)
	{
		time_t now;
		struct tm * timeinfo = NULL;

		time( &now );
		timeinfo = localtime( &now );

		if( timeinfo != NULL )
		{
			strftime(INbuffer,TIME_FORMAT_LENGTH,INtimeFormat,timeinfo);
		}
		else
		{
			INbuffer[0] = '\0';
		}
	}
}


