/*
 * NetError.h
 *
 *  Created on: 2012-12-17
 *      Author: king
 */

#ifndef NETERROR_H_
#define NETERROR_H_

#ifdef WIN32
#include <Winerror.h>
enum
{
	NetError_Opt_Aborted = WSA_OPERATION_ABORTED,
	NetError_UnReach = WSAENETUNREACH,
	NetError_ConnReset = WSAECONNRESET,
	NetError_EOF = 2,
};
#else
#ifdef __GNUC__

#endif
#endif

#endif /* NETERROR_H_ */
