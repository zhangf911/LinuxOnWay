#include "DataTime.h"

#include "Log.h"

#include <sstream>
using std::stringstream;

#include <time.h>

#define TIME_FORMAT3 "%Y-%m-%d %H:%M:%S"
#define TIME_FORMAT_LENGTH 40

namespace ZGF
{
	time_t DataTime::ToInt(const string& INdataTimeString)
	{
		if(INdataTimeString.compare("0000-00-00 00:00:00") == 0)
		{
			return 0;
		}

		tm* timetm = NULL;
		string timestr;
		stringstream timess(INdataTimeString);

		char buf[] = "-- :: ";
		UInt32 index = 0;

		Int32 tm_time[6] = {0};
		while(getline(timess, timestr, buf[index]))
		{
			tm_time[index] = atoi(timestr.c_str());
			++index;
		};

		time_t now;
		time( &now );
		timetm = localtime(&now);

		timetm->tm_year = tm_time[0] - 1900;
		timetm->tm_mon = tm_time[1] - 1;
		timetm->tm_mday = tm_time[2];
		timetm->tm_hour = tm_time[3];
		timetm->tm_min = tm_time[4];
		timetm->tm_sec = tm_time[5];

		time_t result = mktime(timetm);

		return result;
	}

	string DataTime::ToString(UInt32 INtime)
	{
		if(INtime == 0)
		{
			return "0000-00-00 0:0:0";
		}

		char buff[TIME_FORMAT_LENGTH];

		time_t now = INtime;
		struct tm * timeinfo = NULL;

		//time( &now );
		timeinfo = localtime( &now );

		if( timeinfo != NULL )
		{
			strftime(buff, TIME_FORMAT_LENGTH, TIME_FORMAT3, timeinfo);
		}
		else
		{
			buff[0] = '\0';
		}

		return string(buff);
	}

	UInt32 DataTime::GetCurDayZeroTime()
	{
		time_t nowtimestamp = 0;			
		// 获取当前时间
		time(&nowtimestamp);					

		struct tm* change = NULL;

		change = localtime(&nowtimestamp);
		
		change->tm_hour = 0;
		change->tm_min = 0;
		change->tm_sec = 0;		
		
		time_t lastnight = mktime(change);

		return lastnight;
	}

	UInt32 DataTime::DayDiff(UInt32 INtime1, UInt32 INtime2)
	{
		time_t time1 = INtime1;
		time_t time2 = INtime2;

		struct tm* tm_time1 = localtime(&time1);
		tm_time1->tm_hour = 0;
		tm_time1->tm_min = 0;
		tm_time1->tm_sec = 0;
		time1 = mktime(tm_time1);

		struct tm* tm_time2 = localtime(&time2);
		tm_time2->tm_hour = 0;
		tm_time2->tm_min = 0;
		tm_time2->tm_sec = 0;
		time2 = mktime(tm_time2);

		string timeString1 = ToString(time1);
		string timeString2 = ToString(time2);
		UInt32 diff = abs(time1 - time2);

		UInt32 daydiff = diff / (86400);

		return daydiff;
	}
}



