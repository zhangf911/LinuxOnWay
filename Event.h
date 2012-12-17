/*
 * Event.h
 *
 *  Created on: 2012-12-17
 *      Author: king
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "Common.h"

namespace LOW
{

	class Task;

	class Event
	{
	public:
		Task* m_task;
		int m_id;

	public:
		virtual void Process() = 0;
	};

	class Worker
	{
	private:
		list<Event*> m_eventList;

	public:
		void AddEvent(Event* INpEvent)
		{
			m_eventList.push_back(INpEvent);
		}

		void Entry()
		{
			//while(!IsStop())
			{
				Event* pEvnet = GetNextEvent(100);
				if(pEvnet != NULL)
				{
					pEvnet->Process();
					delete pEvnet;
				}
			}
		}

	private:
		Event* GetNextEvent(int timeout)
		{
			//Sleep(timeout);
			Event* pEvent = m_eventList.front();
			m_eventList.pop_front();
			return pEvent;
		}
	};
}


#endif /* EVENT_H_ */
