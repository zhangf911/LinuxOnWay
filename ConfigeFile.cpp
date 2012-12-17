/*
 * ConfigFile.cpp
 *
 *  Created on: 2012-12-17
 *      Author: king
 */

#include "ConfigeFile.h"

namespace LOW
{

	Cprofile::Cprofile(const char* INfileName)
	{
		fileName = INfileName;
	}

	bool Cprofile::ReadBOOL(const char* INsegName, const char* INkeyName, bool* OUTvalue)
	{
#ifdef WIN32
		char retBuffer[NUM_BUFFER_SIZE];

		DWORD copyCount = GetPrivateProfileString((LPCSTR)INsegName, (LPCSTR)INkeyName, (LPCSTR)ERROR_STRING,
			(LPSTR)retBuffer, NUM_BUFFER_SIZE, (LPCSTR)fileName.c_str());

		if(strcmp(retBuffer, ERROR_STRING) == 0)
		{
			return false;
		}
		else
		{
			if(strcmp(retBuffer, "TRUE") == 0 || strcmp(retBuffer, "true") == 0)
			{
				*OUTvalue = true;
			}
			else if(strcmp(retBuffer, "FALSE") == 0 || strcmp(retBuffer, "false") == 0)
			{
				*OUTvalue = false;
			}
			else
			{
				return false;
			}

			return true;
		}
#else
#ifdef __GNUC__
		//
		return true;
#endif
#endif
	}

	bool Cprofile::ReadUChar(const char* INsegName, const char* INkeyName, unsigned char* OUTvalue)
	{
#ifdef WIN32
		char retBuffer[NUM_BUFFER_SIZE];

		DWORD copyCount = GetPrivateProfileString((LPCSTR)INsegName, (LPCSTR)INkeyName, (LPCSTR)ERROR_STRING,
			(LPSTR)retBuffer, NUM_BUFFER_SIZE, (LPCSTR)fileName.c_str());

		if(strcmp(retBuffer, ERROR_STRING) == 0)
		{
			return false;
		}
		else
		{
			if(copyCount == 1)
			{
				*OUTvalue = (unsigned char)retBuffer[0];
			}
			else
			{
				return false;
			}

			return true;
		}
#else

#ifdef __GNUC__
		//
		return true;
#endif
#endif
	}

	bool Cprofile::ReadChar(const char* INsegName, const char* INkeyName, char* OUTvalue)
	{
#ifdef WIN32
		char retBuffer[NUM_BUFFER_SIZE];

		DWORD copyCount = GetPrivateProfileString((LPCSTR)INsegName, (LPCSTR)INkeyName, (LPCSTR)ERROR_STRING,
			(LPSTR)retBuffer, NUM_BUFFER_SIZE, (LPCSTR)fileName.c_str());

		if(strcmp(retBuffer, ERROR_STRING) == 0)
		{
			return false;
		}
		else
		{
			if(copyCount == 1)
			{
				*OUTvalue = retBuffer[0];
			}
			else
			{
				return false;
			}

			return true;
		}
#else

#ifdef __GNUC__
		return true;
#endif
#endif
	}

	bool Cprofile::ReadUSINT(const char* INsegName, const char* INkeyName, unsigned short int* OUTvalue)
	{
#ifdef WIN32
		char retBuffer[NUM_BUFFER_SIZE];

		DWORD copyCount = GetPrivateProfileString((LPCSTR)INsegName, (LPCSTR)INkeyName, (LPCSTR)ERROR_STRING,
			(LPSTR)retBuffer, NUM_BUFFER_SIZE, (LPCSTR)fileName.c_str());

		if(strcmp(retBuffer, ERROR_STRING) == 0)
		{
			return false;
		}
		else
		{
			unsigned int retValue = (unsigned int)atoi(retBuffer);
			if(retValue > 0x0000ffff)
			{
				return false;
			}
			else
			{
				*OUTvalue = (unsigned short int)retValue;
			}

			return true;
		}
#else
#ifdef __GNUC__
		//
		return false;
#endif

#endif
	}

	bool Cprofile::ReadSINT(const char* INsegName, const char* INkeyName, short int* OUTvalue)
	{
#ifdef WIN32
		char retBuffer[NUM_BUFFER_SIZE];

		DWORD copyCount = GetPrivateProfileString((LPCSTR)INsegName, (LPCSTR)INkeyName, (LPCSTR)ERROR_STRING,
			(LPSTR)retBuffer, NUM_BUFFER_SIZE, (LPCSTR)fileName.c_str());

		if(strcmp(retBuffer, ERROR_STRING) == 0)
		{
			return false;
		}
		else
		{
			unsigned int retValue = (unsigned int)atoi(retBuffer);
			if(retValue > 0x0000ffff)
			{
				return false;
			}
			else
			{
				*OUTvalue = (short int)retValue;
			}

			return true;
		}
#else
#ifdef __GNUC__
		return true;
#endif
#endif
	}


	bool Cprofile::ReadUINT(const char* INsegName, const char* INkeyName, unsigned int* OUTvalue)
	{
#ifdef WIN32
		*OUTvalue = GetPrivateProfileInt((LPCSTR)INsegName, (LPCSTR)INkeyName, MAX_INT, (LPCSTR)fileName.c_str());
		if(*OUTvalue == MAX_INT)
		{
			return false;
		}
		else
		{
			return true;
		}
#else
#ifdef __GNUC__
		return true;
#endif
#endif

	}

	bool Cprofile::ReadINT(const char* INsegName, const char* INkeyName, int* OUTvalue)
	{
#ifdef WIN32
		char retBuffer[NUM_BUFFER_SIZE];

		DWORD copyCount = GetPrivateProfileString((LPCSTR)INsegName, (LPCSTR)INkeyName, (LPCSTR)ERROR_STRING,
			(LPSTR)retBuffer, NUM_BUFFER_SIZE, (LPCSTR)fileName.c_str());

		if(strcmp(retBuffer, ERROR_STRING) == 0)
		{
			return false;
		}
		else
		{
			int retValue = atoi(retBuffer);
			*OUTvalue = retValue;

			return true;
		}
#else
#ifdef __GNUC__
		//
		return true;
#endif
#endif
	}

	bool Cprofile::ReadULONG(const char* INsegName, const char* INkeyName, unsigned long* OUTvalue)
	{
#ifdef WIN32
		char retBuffer[NUM_BUFFER_SIZE];

		DWORD copyCount = GetPrivateProfileString((LPCSTR)INsegName, (LPCSTR)INkeyName, (LPCSTR)ERROR_STRING,
			(LPSTR)retBuffer, NUM_BUFFER_SIZE, (LPCSTR)fileName.c_str());

		if(strcmp(retBuffer, ERROR_STRING) == 0)
		{
			return false;
		}
		else
		{
			unsigned long retValue = (unsigned long)atol(retBuffer);
			*OUTvalue = retValue;

			return true;
		}
#else
#ifdef __GNUC__
		//
		return true;
#endif
#endif
	}

	bool Cprofile::ReadLONG(const char* INsegName, const char* INkeyName, long* OUTvalue)
	{
#ifdef WIN32
		char retBuffer[NUM_BUFFER_SIZE];

		DWORD copyCount = GetPrivateProfileString((LPCSTR)INsegName, (LPCSTR)INkeyName, (LPCSTR)ERROR_STRING,
			(LPSTR)retBuffer, NUM_BUFFER_SIZE, (LPCSTR)fileName.c_str());

		if(strcmp(retBuffer, ERROR_STRING) == 0)
		{
			return false;
		}
		else
		{
			long retValue = atol(retBuffer);
			*OUTvalue = retValue;

			return true;
		}
#else
#ifdef __GNUC__
		//
		return true;
#endif
#endif
	}

	bool Cprofile::ReadFloat(const char* INsegName, const char* INkeyName, float* OUTvalue)
	{
#ifdef WIN32
		char retBuffer[NUM_BUFFER_SIZE];

		DWORD copyCount = GetPrivateProfileString((LPCSTR)INsegName, (LPCSTR)INkeyName, (LPCSTR)ERROR_STRING,
			(LPSTR)retBuffer, NUM_BUFFER_SIZE, (LPCSTR)fileName.c_str());

		if(strcmp(retBuffer, ERROR_STRING) == 0)
		{
			return false;
		}
		else
		{
			float retValue = (float)atof(retBuffer);
			*OUTvalue = retValue;

			return true;
		}
#else
#ifdef __GNUC__
		return true;
#endif
#endif
	}

	bool Cprofile::ReadDouble(const char* INsegName, const char* INkeyName, double* OUTvalue)
	{
#ifdef WIN32
		char retBuffer[NUM_BUFFER_SIZE];

		DWORD copyCount = GetPrivateProfileString((LPCSTR)INsegName, (LPCSTR)INkeyName, (LPCSTR)ERROR_STRING,
			(LPSTR)retBuffer, NUM_BUFFER_SIZE, (LPCSTR)fileName.c_str());

		if(strcmp(retBuffer, ERROR_STRING) == 0)
		{
			return false;
		}
		else
		{
			double retValue = atof(retBuffer);
			*OUTvalue = retValue;

			return true;
		}
#else
#ifdef __GNUC__
		//
		return true;
#endif
#endif
	}

	bool Cprofile::ReadString(const char* INsegName, const char* INkeyName, string* OUTvalue)
	{
#ifdef WIN32
		char retBuffer[STRING_BUFFER_SIZE];

		DWORD copyCount = GetPrivateProfileString((LPCSTR)INsegName, (LPCSTR)INkeyName, (LPCSTR)ERROR_STRING,
			(LPSTR)retBuffer, STRING_BUFFER_SIZE, (LPCSTR)fileName.c_str());

		if(strcmp(retBuffer, ERROR_STRING) == 0)
		{
			return false;
		}
		else
		{
			OUTvalue->erase();
			*OUTvalue = retBuffer;

			return true;
		}
#else
#ifdef __GNUC__
		return true;
#endif
#endif
	}

	bool Cprofile::ReadString(const char* INsegName, const char* INkeyName, char** OUTvalue, int* OUTstrLen)
	{
#ifdef WIN32
		char retBuffer[STRING_BUFFER_SIZE];

		DWORD copyCount = GetPrivateProfileString((LPCSTR)INsegName, (LPCSTR)INkeyName, (LPCSTR)ERROR_STRING,
			(LPSTR)retBuffer, STRING_BUFFER_SIZE, (LPCSTR)fileName.c_str());

		if(strcmp(retBuffer, ERROR_STRING) == 0)
		{
			return false;
		}
		else
		{
			// exist bug
			*OUTvalue = retBuffer;
			*OUTstrLen = copyCount;

			return true;
		}
#else

#ifdef __GNUC__
		return true;
#endif
#endif
	}

	bool Cprofile::WriteKeyString(const char* INsegName, const char* INkeyName, const string& INstr)
	{
#ifdef WIN32
		if(!WritePrivateProfileString((LPCSTR)INsegName, (LPCSTR)INkeyName, (LPSTR)INstr.c_str(), (LPCSTR)fileName.c_str()))
		{
			return false;
		}
#else
#ifdef __GNUC__
		return true;
#endif
#endif
		return true;
	}

	bool Cprofile::WriteKeyString(const char* INsegName, const char* INkeyName, const char* INstr, int INsize)
	{
#ifdef WIN32
		string strBuffer;
		strBuffer.append(INstr, INsize);
		if(!WritePrivateProfileString((LPCSTR)INsegName, (LPCSTR)INkeyName, (LPSTR)strBuffer.c_str(), (LPCSTR)fileName.c_str()))
		{
			return false;
		}
#else
#ifdef __GNUC__
		return true;
#endif
#endif
		return true;
	}
}



