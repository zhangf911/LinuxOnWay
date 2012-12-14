#ifndef _NETERROR_H
#define _NETERROR_H

#include <Winerror.h>
enum
{
	NetError_Opt_Aborted = WSA_OPERATION_ABORTED,
	NetError_UnReach = WSAENETUNREACH,
	NetError_ConnReset = WSAECONNRESET,
	NetError_EOF = 2,
};
#endif