/*
 * CRC32.h
 *
 *  Created on: 2012-12-15
 *      Author: king
 */

#ifndef CRC32_H_
#define CRC32_H_

#include "Common.h"

namespace LOW
{
	class CRC32
	{
	public:
		/* This computes a 32 bit CRC of the data in the buffer, and returns the
	   CRC.  The polynomial used is 0xedb88320. */
		static unsigned long GetCRC32(const unsigned char* s, unsigned int len);

	};
}

#endif /* CRC32_H_ */
