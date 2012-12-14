/*
 * DataTime.h
 *
 *  Created on: 2012-12-11
 *      Author: king
 */

#ifndef DATATIME_H_
#define DATATIME_H_

#include "Common.h"

namespace LOW
{
	class DataTime
	{
	public:
		DataTime();

		~DataTime();

	public:
		static time_t CurrentTime();

		static time_t ToInt(const string& INdataTimeString);

		static string ToString(time_t INtime);

		static unsigned int DayDiff(time_t INtime1, time_t INtime2);
	};
}


#endif /* DATATIME_H_ */
