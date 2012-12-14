#ifndef LIBRARY_SINGLETON_H
#define LIBRARY_SINGLETON_H

#include "Lock.h"

namespace ZGF
{
	#define NULL 0

	template <class DataType, class LockType = CriticalSection>
	class Singleton
	{
	public:
		static DataType* Instance()
		{
			static DataType* _instance = NULL;
			static LockType _lock;
			if(!_instance)
			{
				Guard<LockType> monitor(&_lock);
				if(!_instance)
				{
					_instance = new DataType;
				}
			}
			return _instance;
		};

		static void DestroyInstance()
		{
			DataType* _instance = Instance();
			if(_instance)
			{
				delete _instance;
				_instance = NULL;
			}
		}

	protected:
		Singleton(){};

		~Singleton(){};
	};
}

#endif