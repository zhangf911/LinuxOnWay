#ifndef LIBRARY_UNITTEST_THREADUNITTEST_H
#define LIBRARY_UNITTEST_THREADUNITTEST_H

#include <iostream>

#include "BaseType.h"
#include "Thread.h"

using namespace ZGF;

class MyThread : public Thread
{
public:
	virtual ~MyThread()
	{

	}
private:
	virtual bool OnThreadStartEvent()
	{
		std::cout << "MyThread " << GetThreadID() << " is Starting" << std::endl;
		return true;
	}

	virtual bool Run()
	{
		std::cout << "MyThread " << GetThreadID() << " is Running" << std::endl;
		return true;
	}

	virtual bool OnThreadStopEvent()
	{
		std::cout << "MyThread " << GetThreadID() << " is Stopping" << std::endl;
		return true;
	}
};

void ThreadUintTest()
{
	MyThread* pMyThread = new MyThread();

	MyThread* pSecondThread = new MyThread();

	MyASSERT(pMyThread->Start());

	MyASSERT(pSecondThread->Start());

	MyASSERT(pMyThread->Pause());

	MyASSERT(pMyThread->GetThreadState() == EThreadState_Pause);

	MyASSERT(pMyThread->Resume());

	MyASSERT(pMyThread->GetThreadState() == EThreadState_Running);

	pMyThread->Stop(3000);

	MyASSERT(pMyThread->GetThreadState() == EThreadState_Stop);

	pSecondThread->Stop(3000);

	MyASSERT(pSecondThread->GetThreadState() == EThreadState_Stop);

	delete pMyThread;
	delete pSecondThread;
}

#endif