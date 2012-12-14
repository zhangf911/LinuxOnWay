#ifndef LIBRARY_UTIL_SYSTEMTIME_H
#define LIBRARY_UTIL_SYSTEMTIME_H

#include "BaseType.h"

namespace ZGF
{
	class SystemTime
	{
	public:
		SystemTime();

		~SystemTime();

	public:
		bool Initial();

		UInt32 GetCurrentTick();

		UInt32 GetLastSavedTick();

		UInt32 GetStartTime();

		UInt32 GetANSITime();

	public:
		void SetCurrentTime();

		UInt32 GetCurrentYear();

		UInt32 GetCurrentMonth();

		UInt32 GetCurrentDay();

		UInt32 GetCurrentHour();

		UInt32 GetCurrentMinute();

		UInt32 GetCurrentSecond();

		UInt32 GetCurrentWeek();

		UInt32 GetTime();

		UInt32 GetCurrentDate();

		UInt32 GetRunTime();

		UInt32 GetRunTick();


	};
}



#endif