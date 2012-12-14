/*
 * AtomicBoolean.cpp
 *
 *  Created on: 2012-12-14
 *      Author: king
 */

#include "AtomicBoolean.h"

namespace LOW
{
	bool AtomicBoolean::SetVal(bool val)
	{
		unsigned long oldval = 0;

		if(val)
			oldval = Value.SetVal(1);
		else
			oldval = Value.SetVal(0);

		return (oldval & 1);
	}
}



