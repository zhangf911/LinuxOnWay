#include "Code.h"
#include <Windows.h>

namespace ZGF
{

	bool Code::ASCIIToUTF8(const string& INasciiString, string& OUTutf8String)
	{
		LPWSTR lpWideCharStr = NULL;
		LPSTR lpMultiByteStr = NULL;

		try
		{
			// ��ȡת����Ҫ�Ŀ��ַ�����
			int iWideCharSize = MultiByteToWideChar(CP_ACP, 0, INasciiString.c_str(), INasciiString.size(), lpWideCharStr, 0);

			if(0 == iWideCharSize)
			{
				return false;
			}

			lpWideCharStr = new WCHAR[iWideCharSize];

			// ת���ɿ��ַ�
			iWideCharSize = MultiByteToWideChar(CP_ACP, 0, INasciiString.c_str(), INasciiString.size(), lpWideCharStr, iWideCharSize);

			if(0 == iWideCharSize)
			{
				return false;
			}

			// ��ȡת����UTF8���ַ�����
			int iMultiByteSize = WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr, iWideCharSize, lpMultiByteStr, 0, NULL, NULL);

			if(0 == iMultiByteSize)
			{ 
				return false;
			}

			lpMultiByteStr = new char[iMultiByteSize];

			// ת����UTF8�ַ�
			iMultiByteSize = WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr, iWideCharSize, lpMultiByteStr, iMultiByteSize, NULL, NULL);

			if(0 == iMultiByteSize)
			{ 
				return false;
			}

			// �ַ������
			OUTutf8String.erase();
			// ��ֵ
			OUTutf8String.append(lpMultiByteStr, iMultiByteSize);

			// �ͷŶ�̬������ڴ�ռ�
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
	}

	bool Code::UTF8ToASCII(const string& INutf8String, string& OUTasciiString)
	{
		LPWSTR lpWideCharStr = NULL;
		LPSTR lpMultiByteStr = NULL;

		try
		{
			// ��ȡת����Ҫ�Ŀ��ַ�����
			int iWideCharSize = MultiByteToWideChar(CP_UTF8, 0, INutf8String.c_str(), INutf8String.size(), lpWideCharStr, 0);

			if(0 == iWideCharSize)
			{
				return false;
			}

			lpWideCharStr = new WCHAR[iWideCharSize];

			// ת���ɿ��ַ�
			iWideCharSize = MultiByteToWideChar(CP_UTF8, 0, INutf8String.c_str(), INutf8String.size(), lpWideCharStr, iWideCharSize);

			if(0 == iWideCharSize)
			{
				return false;
			}

			// ��ȡת����ASCII���ַ�����
			int iMultiByteSize = WideCharToMultiByte(CP_ACP, 0, lpWideCharStr, iWideCharSize, lpMultiByteStr, 0, NULL, NULL);

			if(0 == iMultiByteSize)
			{ 
				return false;
			}

			lpMultiByteStr = new char[iMultiByteSize];

			// ת����ASCII�ַ�
			iMultiByteSize = WideCharToMultiByte(CP_ACP, 0, lpWideCharStr, iWideCharSize, lpMultiByteStr, iMultiByteSize, NULL, NULL);

			if(0 == iMultiByteSize)
			{ 
				return false;
			}

			// �ַ������
			OUTasciiString.erase();

			// ��ֵ
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
	}

}
