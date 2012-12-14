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
sadfas

typedef boost::recursive_mutex My_CriticalSection;
typedef boost::recursive_mutex::scoped_lock Auto_locker;

#include <functional>
#include "boost/asio.hpp"
#include "boost/bind.hpp"

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

typedef std::tr1::function<void(int)>						Connected_Handler;
typedef std::tr1::function<void(ConectionID)>				DisConnected_Handler;
typedef std::tr1::function<void(Server_Con,ConectionID /*oldConnetionid*/)>  Accepted_Handler;

//��Ч������id
#define INVALID_CONNECTIONID 0

//ÿ��Serverͬʱ�ȴ�Accept������
#define MAX_ACCPET_NUM 10

//���Ĳ����߳�
#define MAX_RUN_THREAD 1
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


#define NET_TRY 


#define NET_CATCH 

#define NET_LOG(x,...)
#define NET_WARN(x,...)
#define NET_ERROR(x,...)

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
	assert(!msg);\
	action;\
}
#endif