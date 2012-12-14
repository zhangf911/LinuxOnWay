#ifndef LIBRARY_BASE_BASETYPE_H
#define LIBRARY_BASE_BASETYPE_H

namespace ZGF
{
	typedef char Int8;
	typedef unsigned char UInt8;
	typedef short Int16;
	typedef unsigned short UInt16;
	typedef int Int32;
	typedef unsigned int UInt32;
	typedef long Long;
	typedef unsigned long ULong;
	typedef __int64 Int64;
	typedef unsigned __int64 UInt64;
};

#include <assert.h>
#include "Log.h"

#define MyASSERT(condition) if(!(condition)) {\
	ERROR_LOG("Assert·¢ÉúÔÚ[%s][%d]",__FILE__,__LINE__) ;\
	int* p = 0;\
	*p = 0;\
	}

#define DEBUG_LOG ZGF::Log::Instance()->WriteDebug
#define NOTE_LOG ZGF::Log::Instance()->WriteNote
#define ERROR_LOG ZGF::Log::Instance()->WriteError
#define EXCEPTION_LOG ZGF::Log::Instance()->WriteException

#ifndef SAFE_DELETE

#define  SAFE_DELETE(x) if(x) {\
	delete(x),(x) = NULL;}
#endif

#ifndef SAFE_DELETE_ARRAY

#define  SAFE_DELETE_ARRAY if(x) {\
	delete[](x),(x) = NULL;} 

#endif

#define DISABLE_COPY_AND_ASSIGN(ClassName) \
	ClassName(const ClassName& INother); \
	void operator=(const ClassName& INother);

#define LIBRARY_DLL_SPEC

#define SINGLETON_DECLARE(cls) static cls* Instance();
#define SINGLETON_IMPLEMENT(cls) cls* cls::Instance()\
{\
	static cls s_instance;\
	return &s_instance;\
}
#define SINGLETON_GET(cls) cls::Instance()

#endif