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

//无效的链接id
#define INVALID_CONNECTIONID 0

//每个Server同时等待Accept的数量
#define MAX_ACCPET_NUM 10

//最多的并发线程
#define MAX_RUN_THREAD 2
#define DEFAULT_RUN_THREAD 2

//每次最多发送的字节数
#define MAX_PER_SEND 4096

//每次做多接收的字节数
#define MAX_PER_RECIVEE 4096

//最长连接时间 10秒
#define  MAX_CONNECTING_TIME  10

//连接断开，最长保留时间 30秒
#define  MAX_DISCONNECTING_TIME  30

//#define  ENABLE_INTERNAL_CONNECTION 

#include "NetError.h"


#define NET_TRY try{ 


#define NET_CATCH }\
	catch (boost::system::system_error _error)\
{\
	NET_ERROR("[%s:%d]网络错误发生,错误代码[%s]",__FILE__,__LINE__,_error.what());\
}\
	catch (SEHTranslator& _seh)\
{\
	NET_ERROR("[%s:%d]网络层发生异常错误",__FILE__,__LINE__);\
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