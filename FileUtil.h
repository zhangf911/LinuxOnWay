/*
 * FileUtil.h
 *
 *  Created on: 2012-12-14
 *      Author: king
 */

#ifndef FILEUTIL_H_
#define FILEUTIL_H_

#include "Common.h"

namespace LOW
{
	class FileUtil
	{
	public:
		static UInt32 GetFileData(const char* INfileName, char** OUTfileData);
	};
}


#endif /* FILEUTIL_H_ */
