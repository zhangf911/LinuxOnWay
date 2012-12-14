#include "WorkQueue.h"
#include "BaseType.h"
#include "SEHTranslator.h"

WorkQueue::WorkQueue(): m_semaphore(0)
{
	m_state = State_None;
}
bool WorkQueue::PushWorkItem( WorkItem* _item )
{
	if (m_state != State_Normal)
	{
		return false;
	}
	Auto_locker lock(m_workCritical);
	m_workItems.push_back(_item);
	m_semaphore.post();
	return true;
}

void WorkQueue::WorkRoutine()
{
	while(true)
	{
		try
		{
			if(m_semaphore.try_wait())
			{
				WorkItem* pItem = NULL;
				{
					Auto_locker lock(m_workCritical);
					if (!m_workItems.empty())
					{
						pItem = m_workItems.front();
						m_workItems.pop_front();
					}
				}
				if (pItem)
				{
					pItem->Run();
					SAFE_DELETE(pItem);
				}
				else
				{
					if (m_state == State_Stop)
					{
						return;
					}
				}
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(100));
			}

		}
		catch (SEHTranslator _seh)
		{
			_seh.log();
		}
		catch (...)
		{

		}
	}
}

void WorkQueue::Start(int nThreadCount)
{
	if (m_state == State_Normal)
	{
		return ;
	}
	m_nThreadCount = nThreadCount;
	if (m_nThreadCount > Max_WorkThread)
		m_nThreadCount = Max_WorkThread;
	m_state = State_Normal;

	for (int i = 0; i < m_nThreadCount; ++i)
	{
		m_workThreads.add_thread(new boost::thread(boost::bind(&WorkQueue::WorkRoutine,this)));
	}
}

void WorkQueue::Stop()
{
	if (m_state != State_Normal)
	{
		return;
	}
	m_state = State_Stop;
	for (int i = 0 ; i < m_nThreadCount; ++i)
	{
		m_semaphore.post();
	}
	m_workThreads.join_all();
}


WorkItem::~WorkItem()
{

}
