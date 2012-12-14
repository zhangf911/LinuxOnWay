#ifndef _NETDEF_H
#define _NETDEF_H

#include <assert.h>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <map>
using std::map;
#include <deque>
using std::deque;

#include "boost/thread.hpp"
#include "boost/bind.hpp"
#include "boost/timer.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "boost/filesystem.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"


typedef boost::recursive_mutex My_CriticalSection;
typedef boost::recursive_mutex::scoped_lock Auto_locker;

#include <functional>
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "Log.h"
#include "SEHTranslator.h"

using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;
using boost::system::error_code;

#include <vector>
#include <map>
#include <deque>
using std::deque;
using std::map;
using std::vector;
typedef long ConectionID;
typedef long ServerID;
class C_NetConnection;
class S_NetConnection;
typedef shared_ptr<C_NetConnection> Client_Con;
typedef shared_ptr<S_NetConnection> Server_Con;

typedef std::tr1::function<void(int)>					   Connected_Handler;
typedef std::tr1::function<void(ConectionID,bool)>		   DisConnected_Handler;
typedef std::tr1::function<void(Server_Con,ConectionID /*oldConnetionid*/)>  Accepted_Handler;

//��Ч������id
#define INVALID_CONNECTIONID 0

//ÿ��Serverͬʱ�ȴ�Accept������
#define MAX_ACCPET_NUM 10

//���Ĳ����߳�
#define MAX_RUN_THREAD 2
#define DEFAULT_RUN_THREAD 2

//ÿ����෢�͵��ֽ���
#define MAX_PER_SEND 4096

//ÿ��������յ��ֽ���
#define MAX_PER_RECIVEE 4096

//�����ʱ�� 10��
#define  MAX_CONNECTING_TIME  10

//���ӶϿ��������ʱ�� 30��
#define  MAX_DISCONNECTING_TIME  30

//#define  ENABLE_INTERNAL_CONNECTION 

#include "NetError.h"


#define NET_TRY try{ 


#define NET_CATCH }\
	catch (boost::system::system_error _error)\
{\
	NET_ERROR("[%s:%d]���������,�������[%s]",__FILE__,__LINE__,_error.what());\
}\
	catch (SEHTranslator& _seh)\
{\
	NET_ERROR("[%s:%d]����㷢���쳣����",__FILE__,__LINE__);\
	_seh.log();\
}

#define NET_LOG(x,...) NOTE_LOG(x,__VA_ARGS__)
#define NET_WARN(x,...)
#define NET_ERROR(x,...) ERROR_LOG(x,__VA_ARGS__)

#define    BIT(x) (1<<x)
#define    MACRO_(x)        #x
#define    SHOWMACOR(mac)    MACRO_(mac)

#define  SAFE_CLOSE(x) if(x) {\
	CloseHandle(x),(x) = NULL;}

#ifndef SAFE_DELETE

#define  SAFE_DELETE(x) if(x) {\
	delete(x),(x) = NULL;}
#endif

#ifndef SAFE_DELETE_ARRAY

#define  SAFE_DELETE_ARRAY if(x) {\
	delete[](x),(x) = NULL;} 

#endif

#define MY_ASSERT(x,msg,action) if(!(x)){\
	MyASSERT(!msg);\
	action;\
}
#endif