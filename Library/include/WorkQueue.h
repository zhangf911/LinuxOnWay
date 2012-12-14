#ifndef _WORKQUEUE_H
#define _WORKQUEUE_H
#include "boost/thread.hpp"
#include "boost/interprocess/sync/interprocess_semaphore.hpp"

#include <deque>
typedef boost::recursive_mutex My_CriticalSection;
typedef boost::recursive_mutex::scoped_lock Auto_locker;
using namespace boost::interprocess;

class WorkItem
{
public:
	virtual void Run() = 0;
	virtual ~WorkItem();
};

class WorkQueue
{
	enum
	{
		Max_WorkThread = 2,
	};
	enum 
 	{
		State_None,
		State_Normal,
		State_Stop,
	};
public:
	WorkQueue();
	void Start(int nThreadCount);
	void Stop();
	bool PushWorkItem(WorkItem* _item);	
	void WorkRoutine();
private:
	boost::thread_group				   m_workThreads;
	int								   m_nThreadCount;

	My_CriticalSection                 m_workCritical;
	std::deque<WorkItem*>              m_workItems;
	interprocess_semaphore             m_semaphore;
	volatile	int					   m_state;
};


#endif