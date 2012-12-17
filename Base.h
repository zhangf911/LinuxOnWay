/*
 * Base.h
 *
 *  Created on: 2012-12-17
 *      Author: king
 */

#ifndef BASE_H_
#define BASE_H_

#include <assert.h>
#include "Log.h"

#define MyASSERT(condition) if(!(condition)) {\
	ERROR_LOG("Assert [%s][%d]",__FILE__,__LINE__) ;\
	int* p = 0;\
	*p = 0;\
	}

LOW::Log g_log;

#define DEBUG_LOG g_log.WriteDebug
#define NOTE_LOG g_log.WriteNote
#define ERROR_LOG g_log.WriteError
#define EXCEPTION_LOG g_log.WriteException

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

#endif /* BASE_H_ */
