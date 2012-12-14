#include "AtomicBoolean.h"
#include <Windows.h>

namespace ZGF
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