/*
 * Code.cpp
 *
 *  Created on: 2012-12-15
 *      Author: king
 */

#include "Code.h"

#ifdef WIN32
#include <Windows.h>
#else
#ifdef __GNUC__
	// 尚未实现
#endif
#endif

namespace LOW
{

	bool Code::ASCIIToUTF8(const string& INasciiString, string& OUTutf8String)
	{
#ifdef WIN32
		LPWSTR lpWideCharStr = NULL;
		LPSTR lpMultiByteStr = NULL;

		try
		{
			// »ñÈ¡×ª»»ÐèÒªµÄ¿í×Ö·û¸öÊý
			int iWideCharSize = MultiByteToWideChar(CP_ACP, 0, INasciiString.c_str(), INasciiString.size(), lpWideCharStr, 0);

			if(0 == iWideCharSize)
			{
				return false;
			}

			lpWideCharStr = new WCHAR[iWideCharSize];

			// ×ª»»³É¿í×Ö·û
			iWideCharSize = MultiByteToWideChar(CP_ACP, 0, INasciiString.c_str(), INasciiString.size(), lpWideCharStr, iWideCharSize);

			if(0 == iWideCharSize)
			{
				return false;
			}

			// »ñÈ¡×ª»»³ÉUTF8µÄ×Ö·û¸öÊý
			int iMultiByteSize = WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr, iWideCharSize, lpMultiByteStr, 0, NULL, NULL);

			if(0 == iMultiByteSize)
			{
				return false;
			}

			lpMultiByteStr = new char[iMultiByteSize];

			// ×ª»»³ÉUTF8×Ö·û
			iMultiByteSize = WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr, iWideCharSize, lpMultiByteStr, iMultiByteSize, NULL, NULL);

			if(0 == iMultiByteSize)
			{
				return false;
			}

			// ×Ö·û´®Çå¿Õ
			OUTutf8String.erase();
			// ¸³Öµ
			OUTutf8String.append(lpMultiByteStr, iMultiByteSize);

			// ÊÍ·Å¶¯Ì¬ÉêÇëµÄÄÚ´æ¿Õ¼ä
			if(lpWideCharStr != NULL)
			{
				delete [] lpWideCharStr;
				lpWideCharStr = NULL;
			}
			if(lpMultiByteStr != NULL)
			{
				delete [] lpMultiByteStr;
				lpMultiByteStr = NULL;
			}

			return true;
		}
		catch(...)
		{
			if(lpWideCharStr != NULL)
			{
				delete [] lpWideCharStr;
				lpWideCharStr = NULL;
			}

			if(lpMultiByteStr != NULL)
			{
				delete [] lpMultiByteStr;
				lpMultiByteStr = NULL;
			}

			return false;
		}
#else
#ifdef __GNUC__
		// 尚未实现
		return false;
#endif
#endif
	}

	bool Code::UTF8ToASCII(const string& INutf8String, string& OUTasciiString)
	{
#ifdef WIN32
		LPWSTR lpWideCharStr = NULL;
		LPSTR lpMultiByteStr = NULL;

		try
		{
			// »ñÈ¡×ª»»ÐèÒªµÄ¿í×Ö·û¸öÊý
			int iWideCharSize = MultiByteToWideChar(CP_UTF8, 0, INutf8String.c_str(), INutf8String.size(), lpWideCharStr, 0);

			if(0 == iWideCharSize)
			{
				return false;
			}

			lpWideCharStr = new WCHAR[iWideCharSize];

			// ×ª»»³É¿í×Ö·û
			iWideCharSize = MultiByteToWideChar(CP_UTF8, 0, INutf8String.c_str(), INutf8String.size(), lpWideCharStr, iWideCharSize);

			if(0 == iWideCharSize)
			{
				return false;
			}

			// »ñÈ¡×ª»»³ÉASCIIµÄ×Ö·û¸öÊý
			int iMultiByteSize = WideCharToMultiByte(CP_ACP, 0, lpWideCharStr, iWideCharSize, lpMultiByteStr, 0, NULL, NULL);

			if(0 == iMultiByteSize)
			{
				return false;
			}

			lpMultiByteStr = new char[iMultiByteSize];

			// ×ª»»³ÉASCII×Ö·û
			iMultiByteSize = WideCharToMultiByte(CP_ACP, 0, lpWideCharStr, iWideCharSize, lpMultiByteStr, iMultiByteSize, NULL, NULL);

			if(0 == iMultiByteSize)
			{
				return false;
			}

			// ×Ö·û´®Çå¿Õ
			OUTasciiString.erase();

			// ¸³Öµ
			OUTasciiString.append(lpMultiByteStr, iMultiByteSize);

			if(lpWideCharStr != NULL)
			{
				delete [] lpWideCharStr;
				lpWideCharStr = NULL;
			}

			if(lpMultiByteStr != NULL)
			{
				delete [] lpMultiByteStr;
				lpMultiByteStr = NULL;
			}

			return true;
		}
		catch(...)
		{
			if(lpWideCharStr != NULL)
			{
				delete [] lpWideCharStr;
				lpWideCharStr = NULL;
			}

			if(lpMultiByteStr != NULL)
			{
				delete [] lpMultiByteStr;
				lpMultiByteStr = NULL;
			}

			return false;
		}

#else
#ifdef __GNUC__
		// 尚未实现
		return false;
#endif
#endif
	}

}


