#ifndef LIBRARY_UTIL_FILEUTIL_H
#define LIBRARY_UTIL_FILEUTIL_H

#include "BaseType.h"

namespace ZGF
{
	class FileUtil
	{
	public:
		/**
		* @brief ��ȡ�ļ�����
		**/
		static char* GetFileData(const char* INfile, UInt32* OUTfileSize);
	};
}


#endif